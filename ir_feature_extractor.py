import re
import sys
import os
import subprocess
import tempfile
from collections import deque

class IRFeatureExtractor:
    """
    Extracts high-level features from a given Intermediate Representation (IR) code.
    
    This version implements full dataflow analysis for Liveness and Available Expressions
    to correctly calculate Dead Code and Global Common Subexpressions.
    """
    
    def __init__(self, ir_content):
        """
        Initializes the extractor with the IR content.
        
        Args:
            ir_content (str): A string containing the entire IR code.
        """
        self.ir_content = ir_content
        self.lines = [line.strip() for line in ir_content.split('\n') if line.strip()]
        
        # --- Regex for General Features ---
        self.variable_regex = re.compile(r'\b(t[0-9]+|[a-zA-Z_][a-zA-Z0-9_]*)\b')
        self.keywords = {
            'alloc', 'LABEL', 'if', 'NOT', 'GOTO', 'JUMP', 'to', 'else'
        }

        # --- Regex for Constant Folding Features ---
        self.constant_regex = re.compile(r'^-?\d+$') 
        self.simple_assignment_regex = re.compile(r'^\s*([a-zA-Z_t][a-zA-Z0-9_]*)\s*=\s*(-?\d+)\s*$')
        self.copy_assignment_regex = re.compile(r'^\s*([a-zA-Z_t][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_t][a-zA-Z0-9_]*)\s*$')
        self.expr_assignment_regex = re.compile(r'^\s*([a-zA-Z_t][a-zA-Z0-9_]*)\s*=\s*(.+)\s*([+\-*/<>=!])\s*(.+)$')
        self.expression_regex = re.compile(r'=\s*(.+)$') 
        self.operand_regex = re.compile(r'\b(t[0-9]+|[a-zA-Z_][a-zA-Z0-9_]*|-?\d+)\b')

        # --- Regex for Dead Code Features ---
        self.lhs_regex = re.compile(r'^\s*(\*?[a-zA-Z_t][a-zA-Z0-9_]*)\s*=')
        
        # --- Regex for Control Flow ---
        self.label_regex = re.compile(r'^LABEL\s+(\S+):')
        self.if_goto_else_regex = re.compile(r'if \((.+)\) GOTO (\S+) else GOTO (\S+)')
        self.if_not_goto_regex = re.compile(r'if NOT \((.+)\) GOTO (\S+)')
        self.goto_regex = re.compile(r'GOTO (\S+)')
        self.jump_regex = re.compile(r'JUMP to (\S+)')

        # --- Regex and Weights for CSE Features ---
        self.operator_regex = re.compile(r'([+\-*/<>=!])')
        self.operator_weights = {
            '*': 3, '/': 3, 
            '+': 1, '-': 1,
            '<': 1, '>': 1, '==': 1, '!=': 1, '<=': 1, '>=': 1
        }
        
        # --- Regex for Strength Reduction Features ---
        # Matches `i = i + 1` or `j = j - 2`
        self.basic_induction_regex = re.compile(r'^\s*([a-zA-Z_t][a-zA-Z0-9_]*)\s*=\s*\1\s*([+-])\s*(\d+)\s*$')
        self.expensive_op_regex = re.compile(r'([*/])')

    def _get_uses_and_def(self, line):
        """Helper to get all variables used (read) and defined (written) in a line."""
        uses = set()
        defs = set()

        all_vars_in_line = {
            m.group(0) for m in self.variable_regex.finditer(line) 
            if m.group(0) not in self.keywords
        }
        
        if line.startswith('alloc'):
            var = line.split(',')[0].split()[1]
            defs.add(var)
            return uses, defs
            
        lhs_match = self.lhs_regex.search(line)
        
        if lhs_match:
            # Assignment line
            lhs = lhs_match.group(1)
            rhs_match = self.expression_regex.search(line)
            rhs_vars = set()
            if rhs_match:
                rhs = rhs_match.group(1)
                rhs_vars = {
                    m.group(0) for m in self.variable_regex.finditer(rhs)
                    if m.group(0) not in self.keywords
                }
            
            if lhs.startswith('*'):
                # e.g., *t0 = ...
                defined_var = lhs.lstrip('*')
                uses.add(defined_var) # The pointer is used
                uses.update(rhs_vars)
            else:
                # e.g., x = ...
                defs.add(lhs)
                uses.update(rhs_vars)
        else:
            # Not an assignment (e.g., 'if' or 'GOTO'), all vars are uses
            uses.update(all_vars_in_line)
            
        return uses, defs

    def _get_expression_info(self, line):
        """Helper to get expression string and operands if a line is a non-trivial expression."""
        rhs_match = self.expression_regex.search(line)
        if not rhs_match:
            return None, None
            
        rhs = rhs_match.group(1).strip()
        operands = self.variable_regex.findall(rhs)
        
        # Ignore constant folding (no vars) and simple copies (t0 = t1)
        if not operands or (len(operands) == 1 and rhs == operands[0]):
            return None, None
            
        return rhs, set(operands)

    def _evaluate_expression(self, expr, constants):
        """
        Safely evaluates simple constant expressions (e.g., "a < 5", "100 == 100").
        """
        try:
            eval_expr = str(expr)
            for _ in range(len(constants) + 1):
                made_replacement = False
                for var, val in constants.items():
                    new_expr, count = re.subn(r'\b' + re.escape(var) + r'\b', str(val), eval_expr)
                    if count > 0:
                        eval_expr = new_expr
                        made_replacement = True
                if not made_replacement:
                    break
            
            if self.variable_regex.search(eval_expr):
                return False, None

            safe_expr = eval_expr.replace("==", "==")
            if not re.fullmatch(r'[\d\s+\-*/<>=!().]+', safe_expr):
                return False, None

            return True, eval(safe_expr)
            
        except Exception:
            return False, None

    def _propagate_constants(self):
        """
        Performs a single, simple pass of constant propagation.
        """
        constants = {}
        in_loop = False
        loop_labels = set()
        
        for i, line in enumerate(self.lines):
            jump_match = self.jump_regex.search(line)
            if jump_match:
                target_label = jump_match.group(1)
                for j, label_line in enumerate(self.lines):
                    if label_line.startswith(f'LABEL {target_label}:'):
                        if j < i:
                            loop_labels.add(target_label)
                        break

        for line in self.lines:
            label_match = self.label_regex.match(line)
            if label_match and label_match.group(1) in loop_labels:
                in_loop = True
            
            match = self.simple_assignment_regex.match(line)
            if match and not in_loop:
                var, val = match.groups()
                constants[var] = int(val)
                continue

            match = self.copy_assignment_regex.match(line)
            if match and not in_loop:
                var1, var2 = match.groups()
                if var2 in constants:
                    constants[var1] = constants[var2]
                elif var1 in constants:
                    del constants[var1]
                continue

            match = self.expr_assignment_regex.match(line)
            if match and not in_loop:
                var, lhs, op, rhs = match.groups()
                expr = f"{lhs} {op} {rhs}"
                success, value = self._evaluate_expression(expr, constants)
                if success:
                    constants[var] = value
                elif var in constants:
                    del constants[var]
                continue
            
            lhs_match = self.lhs_regex.search(line)
            if lhs_match:
                var = lhs_match.group(1).lstrip('*')
                if var in constants:
                    del constants[var]

        return constants

    def _perform_liveness_analysis(self, real_blocks, cfg, pred_cfg):
        """
        Performs backward dataflow analysis to find live variables.
        
        Returns:
            (dict, dict): live_in and live_out sets for each block index.
        """
        num_blocks = len(real_blocks)
        live_in = [set() for _ in range(num_blocks)]
        live_out = [set() for _ in range(num_blocks)]
        
        # 1. Compute use and def for all blocks
        use = []
        defs = []
        for block_lines in real_blocks:
            block_use = set()
            block_def = set()
            for line in reversed(block_lines):
                line_uses, line_defs = self._get_uses_and_def(line)
                block_use.update(line_uses - block_def)
                block_def.update(line_defs)
            use.append(block_use)
            defs.append(block_def)

        # 2. Iterate until convergence
        changed = True
        while changed:
            changed = False
            for i in reversed(range(num_blocks)):
                # live_out[i] = UNION of live_in[s] for all successors s
                new_live_out = set()
                for s_idx in cfg.get(i, set()):
                    new_live_out.update(live_in[s_idx])
                
                if new_live_out != live_out[i]:
                    live_out[i] = new_live_out
                    changed = True
                
                # live_in[i] = use[i] U (live_out[i] - def[i])
                new_live_in = use[i].union(live_out[i] - defs[i])
                
                if new_live_in != live_in[i]:
                    live_in[i] = new_live_in
                    changed = True
                    
        return live_in, live_out

    def _perform_available_expressions_analysis(self, real_blocks, cfg, pred_cfg, all_expressions):
        """
        Performs forward dataflow analysis to find available expressions.
        
        Returns:
            (dict, dict): avail_in and avail_out sets for each block index.
        """
        num_blocks = len(real_blocks)
        avail_in = [set() for _ in range(num_blocks)]
        avail_out = [set() for _ in range(num_blocks)]
        
        # 1. Compute gen and kill for all blocks
        gen = []
        kill = []
        for block_lines in real_blocks:
            block_gen = set()
            block_kill = set()
            
            for line in block_lines:
                expr, operands = self._get_expression_info(line)
                if expr:
                    # Gen the expression, but only if its operands aren't killed first
                    if not any(op in block_kill for op in operands):
                        block_gen.add(expr)
                
                _, line_defs = self._get_uses_and_def(line)
                if line_defs:
                    def_var = line_defs.pop() # Assuming single definition
                    block_kill.add(def_var)
                    
            # Kill set for expressions is based on defs in the block
            expr_kill = set()
            for expr, operands in all_expressions.items():
                if not operands.isdisjoint(block_kill):
                    expr_kill.add(expr)
            
            gen.append(block_gen)
            kill.append(expr_kill)
        
        # 2. Iterate until convergence
        # Initialize avail_in[0] as empty, all others as U (all expressions)
        # *** FIX: Convert dict_keys to sets ***
        all_expr_set = set(all_expressions.keys())
        avail_in = [all_expr_set.copy() if i > 0 else set() for i in range(num_blocks)]
        avail_out = [all_expr_set.copy() for _ in range(num_blocks)]

        changed = True
        while changed:
            changed = False
            for i in range(num_blocks): # Forward pass
                # avail_in[i] = INTERSECTION of avail_out[p] for all predecessors p
                if i in pred_cfg and pred_cfg[i]:
                    new_avail_in = set.intersection(*(avail_out[p_idx] for p_idx in pred_cfg[i]))
                else:
                    new_avail_in = set() # Entry block
                
                if new_avail_in != avail_in[i]:
                    avail_in[i] = new_avail_in
                    changed = True
                    
                # avail_out[i] = gen[i] U (avail_in[i] - kill[i])
                new_avail_out = gen[i].union(avail_in[i] - kill[i])
                
                if new_avail_out != avail_out[i]:
                    avail_out[i] = new_avail_out
                    changed = True
        
        return avail_in, avail_out

    def extract_features(self):
        """
        Calculates and returns all 14 features.
        """
        
        instructions = []
        conditional_branches = 0
        all_defined_vars_ever = set()
        
        # --- Pass 1: Get instruction list and count branches/vars ---
        # Note: This simple pass is just for basic counts.
        # Liveness analysis (Feature 7) is done later.
        for i, line in enumerate(self.lines):
            if not line.startswith('LABEL'):
                instructions.append(line)
                
            if line.startswith('if '):
                conditional_branches += 1
            
            _, line_defs = self._get_uses_and_def(line)
            all_defined_vars_ever.update(line_defs)
        
        # --- 1. Instruction_Count ---
        instruction_count = len(instructions)
        
        if instruction_count == 0:
            return {
                'Instruction_Count': 0, 'Basic_Block_Count': 0, 'Cyclomatic_Complexity': 1,
                'Variable_To_Instruction_Ratio': 0.0, 'Constant_Assignment_Count': 0,
                'Constant_Operand_Ratio': 0.0, 'Defined_But_Unused_Var_Count': 0,
                'Unreachable_Block_Count': 0, 'Redundant_Expression_Count': 0,
                'Expression_Complexity_Score': 0, 'Induction_Variable_Count': 0,
                'Expensive_Op_In_Loop_Count': 0, 'Loop_Depth': 0, 'Invariant_Expression_Count': 0
            }

        # --- 2, 8, and Dataflow Analysis Setup ---
        try:
            (real_blocks, reachable_real_indices, loops, 
             cfg, pred_cfg, all_expressions) = self._analyze_control_flow()
            
            basic_block_count = len(real_blocks)
            unreachable_block_count = len(real_blocks) - len(reachable_real_indices)
        
        except Exception as e:
            print(f"Warning: Could not analyze control flow. Defaulting values. Error: {e}")
            real_blocks = [instructions]
            basic_block_count = 1 
            unreachable_block_count = 0
            loops = []
            cfg = {0: set()}
            pred_cfg = {0: set()}
            all_expressions = {}
        
        # --- 3. Cyclomatic_Complexity ---
        cyclomatic_complexity = conditional_branches + 1
        
        # --- 4. Variable_To_Instruction_Ratio ---
        variable_count = len(all_defined_vars_ever) # Use a more accurate count
        variable_to_instruction_ratio = variable_count / instruction_count
        
        # --- 5 & 6. Constant Folding Features ---
        constant_assignment_count = 0
        total_expression_operands = 0
        constant_expression_operands = 0
        
        for line in instructions:
            if self.simple_assignment_regex.match(line):
                constant_assignment_count += 1
            
            rhs_match = self.expression_regex.search(line)
            if rhs_match:
                rhs = rhs_match.group(1)
                operands = self.operand_regex.findall(rhs)
                valid_operands = [op for op in operands if op not in self.keywords]
                
                if valid_operands:
                    total_expression_operands += len(valid_operands)
                    for op in valid_operands:
                        if self.constant_regex.match(op):
                            constant_expression_operands += 1

        constant_operand_ratio = (constant_expression_operands / total_expression_operands) if total_expression_operands > 0 else 0.0
            
        # --- 7. Defined_But_Unused_Var_Count (Liveness Analysis) ---
        live_in, live_out = self._perform_liveness_analysis(real_blocks, cfg, pred_cfg)
        dead_definitions_count = 0
        
        for i in range(len(real_blocks)):
            if i not in reachable_real_indices:
                continue # Skip unreachable blocks
                
            live_vars = live_out[i].copy()
            for line in reversed(real_blocks[i]):
                line_uses, line_defs = self._get_uses_and_def(line)
                
                if line_defs:
                    defined_var = line_defs.pop() # Assuming single def
                    if defined_var not in live_vars:
                        # This definition is dead
                        dead_definitions_count += 1
                    live_vars.discard(defined_var)
                
                live_vars.update(line_uses)
        defined_but_unused_count = dead_definitions_count

        # --- 9 & 10. CSE Features (Available Expressions) ---
        avail_in, avail_out = self._perform_available_expressions_analysis(real_blocks, cfg, pred_cfg, all_expressions)
        total_redundant_count = 0
        total_complexity_score = 0
        
        for i in range(len(real_blocks)):
            if i not in reachable_real_indices:
                continue # Skip unreachable blocks
            
            available_now = avail_in[i].copy()
            for line in real_blocks[i]:
                expr, operands = self._get_expression_info(line)
                if expr:
                    # --- 10. Expression_Complexity_Score ---
                    ops_in_line = self.operator_regex.findall(expr)
                    for op in ops_in_line:
                        cleaned_op = op.strip()
                        if cleaned_op in self.operator_weights:
                            total_complexity_score += self.operator_weights[cleaned_op]
                    
                    # --- 9. Redundant_Expression_Count ---
                    if expr in available_now:
                        total_redundant_count += 1
                    else:
                        available_now.add(expr)
                
                # Kill expressions killed by this line's definition
                _, line_defs = self._get_uses_and_def(line)
                if line_defs:
                    def_var = line_defs.pop()
                    # Remove all expressions that use this defined var
                    available_now = {e for e in available_now if def_var not in all_expressions[e]}

        # --- 11, 12, 13, 14. Loop Features ---
        all_induction_vars = set()
        total_expensive_op_count = 0
        total_invariant_expr_count = 0
        max_loop_depth = 0
        
        if loops:
            # --- 13. Loop_Depth ---
            max_depth = 0
            if loops:
                max_depth = 1 # At least one loop exists
                for loop_a in loops:
                    current_depth = 1
                    for loop_b in loops:
                        if loop_a != loop_b and loop_a.issubset(loop_b):
                            current_depth += 1
                    max_depth = max(max_depth, current_depth)
            max_loop_depth = max_depth

            
            # --- 11, 12, 14 (Refactored Logic) ---
            for loop_set in loops:
                current_loop_instructions = []
                vars_defined_in_this_loop = set()
                induction_vars_in_this_loop = set()
                
                for block_idx in loop_set:
                    if block_idx < len(real_blocks):
                        block_lines = real_blocks[block_idx]
                        current_loop_instructions.extend(block_lines)
                        for line in block_lines:
                            _, line_defs = self._get_uses_and_def(line)
                            vars_defined_in_this_loop.update(line_defs)
                
                # 2. Find Induction Variables for *this loop*
                for var in vars_defined_in_this_loop:
                    definitions = []
                    for line in current_loop_instructions:
                        if re.match(r'^\s*' + re.escape(var) + r'\s*=', line):
                            definitions.append(line)
                    
                    if len(definitions) != 1: continue

                    defn = definitions[0]
                    match1 = self.basic_induction_regex.match(defn)
                    if match1:
                        induction_vars_in_this_loop.add(var)
                        all_induction_vars.add(var)
                        continue

                    match2 = self.copy_assignment_regex.match(defn)
                    if match2:
                        var_name, temp_var = match2.groups()
                        if var_name != var: continue

                        temp_definitions = []
                        for line in current_loop_instructions:
                            if re.match(r'^\s*' + re.escape(temp_var) + r'\s*=', line):
                                temp_definitions.append(line)
                        
                        if len(temp_definitions) != 1: continue

                        temp_defn = temp_definitions[0]
                        iv_match_regex = re.compile(r'^\s*' + re.escape(temp_var) + r'\s*=\s*' + re.escape(var) + r'\s*([+-])\s*(\d+)\s*$')
                        if iv_match_regex.match(temp_defn):
                            induction_vars_in_this_loop.add(var)
                            all_induction_vars.add(var)

                # 3. Find Expensive Ops and Invariants for *this loop*
                for line in current_loop_instructions:
                    expr, var_operands = self._get_expression_info(line)
                    if not expr: continue
                    
                    # --- 12. Expensive_Op_In_Loop_Count ---
                    if self.expensive_op_regex.search(line):
                        if not var_operands.isdisjoint(induction_vars_in_this_loop):
                             total_expensive_op_count += 1
                    
                    # --- 14. Invariant_Expression_Count ---
                    is_invariant = True
                    for op in var_operands:
                        if op in vars_defined_in_this_loop:
                            is_invariant = False
                            break
                    
                    if is_invariant:
                        total_invariant_expr_count += 1
        
        induction_variable_count = len(all_induction_vars)
        expensive_op_in_loop_count = total_expensive_op_count
        invariant_expression_count = total_invariant_expr_count
        

        # --- Return all features ---
        return {
            'Instruction_Count': instruction_count,
            'Basic_Block_Count': basic_block_count,
            'Cyclomatic_Complexity': cyclomatic_complexity,
            'Variable_To_Instruction_Ratio': variable_to_instruction_ratio,
            'Constant_Assignment_Count': constant_assignment_count,
            'Constant_Operand_Ratio': constant_operand_ratio,
            'Defined_But_Unused_Var_Count': defined_but_unused_count,
            'Unreachable_Block_Count': unreachable_block_count,
            'Redundant_Expression_Count': total_redundant_count,
            'Expression_Complexity_Score': total_complexity_score,
            'Induction_Variable_Count': induction_variable_count,
            'Expensive_Op_In_Loop_Count': expensive_op_in_loop_count,
            'Loop_Depth': max_loop_depth,
            'Invariant_Expression_Count': invariant_expression_count
        }

    def _analyze_control_flow(self):
        """
        Builds a Control Flow Graph (CFG) and gathers block info.
        
        Returns:
            (list, set, list, dict, dict, dict): A tuple of:
                - real_blocks (list of basic blocks, where each block is a list of lines)
                - reachable_real_indices (a set of indices from real_blocks that are reachable)
                - loops (a list of sets, where each set contains the block indices for a loop)
                - cfg (successor graph)
                - pred_cfg (predecessor graph)
                - all_expressions (map of {expr_str: {operands}})
        """
        
        if not self.lines:
            return [], set(), [], {}, {}, {}
            
        constants = self._propagate_constants()
        
        # --- Pass 1: Find all leaders, labels, and expressions ---
        leader_lines = set()
        label_to_line = {}
        all_expressions = {} # Map of {expr_str: {operands}}
        
        for i, line in enumerate(self.lines):
            if i == 0:
                leader_lines.add(i)
                
            if line.startswith('LABEL'):
                label_name = line.split()[1].replace(':', '')
                leader_lines.add(i)
                label_to_line[label_name] = i
            
            if line.startswith('JUMP') or line.startswith('GOTO') or line.startswith('if '):
                if i + 1 < len(self.lines):
                    leader_lines.add(i + 1)
            
            expr, operands = self._get_expression_info(line)
            if expr:
                all_expressions[expr] = operands

        
        sorted_leaders = sorted(list(leader_lines))
        block_count = len(sorted_leaders)
        
        if block_count == 0:
            return [], set(), [], {}, {}, {}
            
        block_start_to_index = {line: i for i, line in enumerate(sorted_leaders)}
        label_to_block_index = {
            label: block_start_to_index[line]
            for label, line in label_to_line.items()
            if line in block_start_to_index
        }

        # --- Pass 2: Build CFG and Predecessor Graph ---
        cfg = {i: set() for i in range(block_count)}
        pred_cfg = {i: set() for i in range(block_count)}
        back_edges = []
        
        def add_edge(u, v):
            if v in block_start_to_index.values():
                cfg[u].add(v)
                pred_cfg[v].add(u)
                if sorted_leaders[v] <= sorted_leaders[u]:
                    back_edges.append((u, v))

        for i in range(block_count):
            current_block_index = i
            block_start_line = sorted_leaders[i]
            block_end_line = sorted_leaders[i+1] - 1 if i+1 < block_count else len(self.lines) - 1

            last_line_index = block_end_line
            while last_line_index > block_start_line and self.lines[last_line_index].startswith('LABEL'):
                last_line_index -= 1
            
            if last_line_index < block_start_line:
                if (i + 1 < block_count):
                    add_edge(i, i + 1) # Empty block falls through
                continue

            last_line = self.lines[last_line_index]
            has_fallthrough = True

            if_else_match = self.if_goto_else_regex.search(last_line)
            if_not_match = self.if_not_goto_regex.search(last_line)
            goto_match = self.goto_regex.search(last_line)
            jump_match = self.jump_regex.search(last_line)
            
            if if_else_match:
                cond, true_label, false_label = if_else_match.groups()
                success, value = self._evaluate_expression(cond, constants)
                
                if success:
                    target_label = true_label if value else false_label
                    if target_label in label_to_block_index:
                        add_edge(current_block_index, label_to_block_index[target_label])
                else:
                    if true_label in label_to_block_index:
                        add_edge(current_block_index, label_to_block_index[true_label])
                    if false_label in label_to_block_index:
                        add_edge(current_block_index, label_to_block_index[false_label])
                has_fallthrough = False
            
            elif if_not_match:
                cond, false_label = if_not_match.groups()
                success, value = self._evaluate_expression(cond, constants)
                
                if success:
                    if not value:
                        if false_label in label_to_block_index:
                            add_edge(current_block_index, label_to_block_index[false_label])
                        has_fallthrough = False
                    else:
                        pass
                else:
                    if false_label in label_to_block_index:
                        add_edge(current_block_index, label_to_block_index[false_label])
            
            elif goto_match:
                target_label = goto_match.group(1)
                if target_label in label_to_block_index:
                    add_edge(current_block_index, label_to_block_index[target_label])
                has_fallthrough = False
                
            elif jump_match:
                target_label = jump_match.group(1)
                if target_label in label_to_block_index:
                    add_edge(current_block_index, label_to_block_index[target_label])
                has_fallthrough = False
            
            if has_fallthrough and (i + 1 < block_count):
                add_edge(current_block_index, i + 1)

        # --- Pass 3: Traverse the CFG to find reachable blocks ---
        visited = set()
        if 0 in cfg:
            visited.add(0) 
            queue = deque([0])
            while queue:
                current_block = queue.popleft()
                for neighbor in cfg.get(current_block, set()):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                        
        # --- Build list of real (non-empty) blocks ---
        real_blocks = []
        real_block_indices = {} 
        
        for i in range(block_count):
            block_start_line = sorted_leaders[i]
            block_end_line = sorted_leaders[i+1] if i+1 < block_count else len(self.lines)
            
            block_lines = []
            is_empty = True
            for line_idx in range(block_start_line, block_end_line):
                if not self.lines[line_idx].startswith('LABEL'):
                    is_empty = False
                block_lines.append(self.lines[line_idx])

            if not is_empty:
                real_block_indices[i] = len(real_blocks)
                real_blocks.append(block_lines)
        
        reachable_real_indices = set()
        for visited_idx in visited:
            if visited_idx in real_block_indices:
                reachable_real_indices.add(real_block_indices[visited_idx])
        
        # --- Pass 4: Find loop bodies ---
        loops = []
        if back_edges:
            for u, v_header in back_edges:
                loop_blocks = {v_header}
                stack = [u]
                while stack:
                    curr = stack.pop()
                    if curr not in loop_blocks:
                        loop_blocks.add(curr)
                        for p in pred_cfg[curr]:
                            stack.append(p)
                
                real_loop_set = set()
                for b_idx in loop_blocks:
                    if b_idx in real_block_indices:
                        real_loop_set.add(real_block_indices[b_idx])
                
                if real_loop_set not in loops:
                    loops.append(real_loop_set)
        
        # --- Final Step: Remap CFG/Pred_CFG to real_block indices ---
        real_cfg = {i: set() for i in range(len(real_blocks))}
        real_pred_cfg = {i: set() for i in range(len(real_blocks))}

        for original_idx, real_idx in real_block_indices.items():
            if original_idx in cfg:
                for succ in cfg[original_idx]:
                    if succ in real_block_indices:
                        real_cfg[real_idx].add(real_block_indices[succ])
            if original_idx in pred_cfg:
                for pred in pred_cfg[original_idx]:
                    if pred in real_block_indices:
                        real_pred_cfg[real_idx].add(real_block_indices[pred])

        return real_blocks, reachable_real_indices, loops, real_cfg, real_pred_cfg, all_expressions


def generate_ir_from_c_file(c_file_path):
    """
    Generates IR from a C file using the compiler and returns the IR content.
    
    Args:
        c_file_path (str): Path to the C source file
        
    Returns:
        str: Generated IR content
    """
    
    try:
        # Create a temporary file to capture IR output
        with tempfile.NamedTemporaryFile(mode='w', suffix='.txt', delete=False) as temp_file:
            temp_ir_file = temp_file.name
        
        # Run the compiler with input redirection and output capture
        # Assuming your compiler executable is named 'compiler.exe'
        compiler_exe = 'compiler.exe' if os.name == 'nt' else './compiler.exe'
        with open(c_file_path, 'r') as input_file:
            result = subprocess.run(
                [compiler_exe], 
                stdin=input_file,
                capture_output=True,
                text=True,
                cwd='.'
            )
        
        if result.returncode != 0:
            print(f"Compiler error: {result.stderr}")
            return None
            
        # Extract IR from compiler output
        # The IR is in PHASE 4: INTERMEDIATE CODE GENERATION section
        output_lines = result.stdout.split('\n')
        ir_lines = []
        in_ir_section = False
        
        for line in output_lines:
            if "PHASE 4: INTERMEDIATE CODE GENERATION" in line:
                in_ir_section = True
                continue
            elif in_ir_section:
                # Keep collecting lines until we hit multiple empty lines or end of output
                if line.strip() == "" and len(ir_lines) > 0 and ir_lines[-1].strip() == "":
                    # Two consecutive empty lines indicate end of IR
                    break
                ir_lines.append(line)
        
        # Remove trailing empty lines
        while ir_lines and ir_lines[-1].strip() == "":
            ir_lines.pop()
            
        ir_content = '\n'.join(ir_lines)
        
        # Save IR to original_ic.txt file
        try:
            with open('original_ic.txt', 'w') as ir_file:
                ir_file.write(ir_content)
            print(f"Intermediate code saved to original_ic.txt")
        except Exception as e:
            print(f"Warning: Could not save IR to file: {e}")
        
        # Clean up temporary file
        try:
            os.unlink(temp_ir_file)
        except:
            pass
            
        return ir_content
        
    except Exception as e:
        print(f"Error generating IR: {e}")
        return None

# --- Main execution ---
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python ir_feature_extractor.py <c_file_path>")
        print("Example: python ir_feature_extractor.py input1.c")
        sys.exit(1)
    
    c_file_path = sys.argv[1]
    
    # Check if file exists
    if not os.path.exists(c_file_path):
        print(f"Error: File '{c_file_path}' not found!")
        sys.exit(1)
    
    print(f"Generating IR from {c_file_path}...")
    ir_code = generate_ir_from_c_file(c_file_path)
    
    if ir_code is None or ir_code.strip() == "":
        print("Failed to generate IR or IR is empty!")
        sys.exit(1)
    
    print("IR generated successfully!")
    print("\n" + "="*50)
    print("GENERATED IR:")
    print("="*50)
    print(ir_code)
    print("="*50 + "\n")
    
    # Create an extractor instance and get the features
    extractor = IRFeatureExtractor(ir_code)
    features = extractor.extract_features()
    
    # Print the results
    print("--- General & Structural Features ---")
    print(f"Instruction_Count: {features['Instruction_Count']}")
    print(f"Basic_Block_Count: {features['Basic_Block_Count']}")
    print(f"Cyclomatic_Complexity: {features['Cyclomatic_Complexity']}")
    print(f"Variable_To_Instruction_Ratio: {features['Variable_To_Instruction_Ratio']:.4f}")

    print("\n--- Constant Folding Features ---")
    print(f"Constant_Assignment_Count: {features['Constant_Assignment_Count']}")
    print(f"Constant_Operand_Ratio: {features['Constant_Operand_Ratio']:.4f}")

    print("\n--- Dead Code Elimination Features ---")
    print(f"Defined_But_Unused_Var_Count: {features['Defined_But_Unused_Var_Count']}")
    print(f"Unreachable_Block_Count: {features['Unreachable_Block_Count']}")

    print("\n--- Common Subexpression Elimination Features ---")
    print(f"Redundant_Expression_Count: {features['Redundant_Expression_Count']}")
    print(f"Expression_Complexity_Score: {features['Expression_Complexity_Score']}")
    
    print("\n--- Strength Reduction Features ---")
    print(f"Induction_Variable_Count: {features['Induction_Variable_Count']}")
    print(f"Expensive_Op_In_Loop_Count: {features['Expensive_Op_In_Loop_Count']}")

    print("\n--- Loop-Invariant Code Motion Features ---")
    print(f"Loop_Depth: {features['Loop_Depth']}")
    print(f"Invariant_Expression_Count: {features['Invariant_Expression_Count']}")

