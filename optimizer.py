#!/usr/bin/env python3
"""
Optimization Engine for Intermediate Code

Applies various optimizations to three-address code (IR) based on a provided list.
This is a fully corrected and functional version.
"""

import re
import sys
from typing import List, Dict, Set, Tuple, Optional


class Optimizer:
    """
    Applies optimizations to intermediate code (three-address code).
    """
    
    def __init__(self, ir_content: str):
        """
        Initialize optimizer with IR content.
        
        Args:
            ir_content: String containing the intermediate code
        """
        self.lines = [line.rstrip() for line in ir_content.split('\n') if line.strip()]
        self.label_map = {}  # Maps label names to line indices
        self.modified = True # Flag to run optimizations iteratively
        self.temp_counter = 500 # Counter for new temp variables

    def optimize(self, optimizations: List[str]) -> str:
        """
        Apply optimizations in order.
        
        Args:
            optimizations: List of optimization names to apply
            
        Returns:
            Optimized IR as string
        """
        # --- Optimization Pipeline ---
        # We run the pipeline iteratively until no more changes are made.
        # This is crucial as one optimization (like Constant Folding)
        # can create new opportunities for another (like Dead Code Elimination).
        
        MAX_PASSES = 10
        for _ in range(MAX_PASSES):
            self.modified = False
            self._build_label_map()
            
            # Run optimizations in a logical order
            if "Constant Folding" in optimizations:
                self._constant_folding()
            
            if "Strength Reduction" in optimizations:
                self._strength_reduction()
            
            if "Common Subexpression Elimination" in optimizations:
                self._common_subexpression_elimination()

            if "Loop-Invariant Code Motion" in optimizations:
                self._loop_invariant_code_motion()

            if "Dead Code Elimination" in optimizations:
                self._dead_code_elimination()

            if not self.modified:
                # No changes in this full pass, optimization is stable.
                break
        
        return '\n'.join(self.lines)
    
    def _build_label_map(self):
        """Build a map of label names to line indices."""
        self.label_map = {}
        for i, line in enumerate(self.lines):
            match = re.match(r'^LABEL\s+(\w+):', line)
            if match:
                self.label_map[match.group(1)] = i
    
    def _constant_folding(self):
        """
        Apply constant folding and constant propagation.
        
        This function iterates through the IR, tracks the constant value of
        variables, and performs two actions:
        1.  **Folding**: Computes expressions (e.g., 10 + 20) at compile time.
        2.  **Propagation**: Replaces uses of variables known to be constant
            (e.g., replaces 't1' with '30' if 't1 = 30').
        It also simplifies conditional branches whose conditions can be
        evaluated at compile time (e.g., if (10 < 5) ...).
        """
        
        # Tracks known constant values of variables {var: value}
        variable_values = {}
        new_lines = []
        
        # Regex patterns for optimization
        # Pattern 1: t1 = 10 (Constant assignment)
        p_const_assign = re.compile(r'^\s*(\w+)\s*=\s*(-?\d+)\s*$')
        
        # Pattern 2: t1 = t2 (Copy propagation)
        p_copy_assign = re.compile(r'^\s*(\w+)\s*=\s*(\w+)\s*$')
        
        # Pattern 3: t1 = 10 + 20 (Binary op with two numbers)
        p_binop_num_num = re.compile(r'^\s*(\w+)\s*=\s*(-?\d+)\s*([+\-*/%])\s*(-?\d+)\s*$')
        
        # Pattern 4: t1 = t2 + 10 (Binary op with var and number)
        p_binop_var_num = re.compile(r'^\s*(\w+)\s*=\s*(\w+)\s*([+\-*/%])\s*(-?\d+)\s*$')
        
        # Pattern 5: t1 = 10 + t2 (Binary op with number and var)
        p_binop_num_var = re.compile(r'^\s*(\w+)\s*=\s*(-?\d+)\s*([+\-*/%])\s*(\w+)\s*$')
        
        # Pattern 6: t1 = t2 + t3 (Binary op with two vars)
        p_binop_var_var = re.compile(r'^\s*(\w+)\s*=\s*(\w+)\s*([+\-*/%])\s*(\w+)\s*$')
        
        # Parentheses around the condition are now optional \(? and \)?
        
        # Pattern 7: if (10 < 20) GOTO L1 else GOTO L2
        p_cond_num_num = re.compile(r'^\s*if\s+\(?(-?\d+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)')
        
        # Pattern 8: if (t1 < 20) GOTO L1 else GOTO L2
        p_cond_var_num = re.compile(r'^\s*if\s+\(?(\w+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)')
        
        # Pattern 9: if (10 < t1) GOTO L1 else GOTO L2
        p_cond_num_var = re.compile(r'^\s*if\s+\(?(-?\d+)\s*([<>=!]+)\s*(\w+)\)?\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)')
        
        # Pattern 10: if (t1 < t2) GOTO L1 else GOTO L2
        p_cond_var_var = re.compile(r'^\s*if\s+\(?(\w+)\s*([<>=!]+)\s*(\w+)\)?\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)')
        
        # Pattern 11: if NOT (10 < 20) GOTO L1
        p_cond_not_num_num = re.compile(r'^\s*if\s+NOT\s+\(?(-?\d+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)')
        
        # Pattern 12: if NOT (t1 < 20) GOTO L1
        p_cond_not_var_num = re.compile(r'^\s*if\s+NOT\s+\(?(\w+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)')
        
        # Pattern 13: if NOT (10 < t1) GOTO L1
        p_cond_not_num_var = re.compile(r'^\s*if\s+NOT\s+\(?(-?\d+)\s*([<>=!]+)\s*(\w+)\)?\s+GOTO\s+(\w+)')
        
        # Pattern 14: if NOT (t1 < t2) GOTO L1
        p_cond_not_var_var = re.compile(r'^\s*if\s+NOT\s+\(?(\w+)\s*([<>=!]+)\s*(\w+)\)?\s+GOTO\s+(\w+)')


        for line in self.lines:
            # --- 1. Control Flow and Dataflow Invalidation ---
            if line.startswith("LABEL"):
                new_lines.append(line)
                # We are entering a new basic block.
                # A simple (but safe) approach is to clear all known constants,
                # as we don't know which path was taken to get here.
                variable_values = {}
                continue
                
            # Check for GOTO/JUMP *after* checking for optimizable conditionals
            is_conditional = (p_cond_num_num.match(line) or p_cond_var_num.match(line) or 
                              p_cond_num_var.match(line) or p_cond_var_var.match(line) or 
                              p_cond_not_num_num.match(line) or p_cond_not_var_num.match(line) or
                              p_cond_not_num_var.match(line) or p_cond_not_var_var.match(line))
            
            if (line.startswith("GOTO") or line.startswith("JUMP")) and not is_conditional:
                new_lines.append(line)
                variable_values = {}
                continue


            # --- 2. Constant Expression Folding ---
            
            # t1 = 10 + 20
            match = p_binop_num_num.match(line)
            if match:
                var, num1, op, num2 = match.groups()
                result = self._compute(int(num1), op, int(num2))
                new_lines.append(f"{var} = {result}")
                variable_values[var] = result
                self.modified = True
                continue
            
            # t1 = t2 + 10 (where t2 is a known constant)
            match = p_binop_var_num.match(line)
            if match:
                var, var1, op, num2 = match.groups()
                if var1 in variable_values:
                    result = self._compute(variable_values[var1], op, int(num2))
                    new_lines.append(f"{var} = {result}")
                    variable_values[var] = result
                    self.modified = True
                    continue
            
            # t1 = 10 + t2 (where t2 is a known constant)
            match = p_binop_num_var.match(line)
            if match:
                var, num1, op, var2 = match.groups()
                if var2 in variable_values:
                    result = self._compute(int(num1), op, variable_values[var2])
                    new_lines.append(f"{var} = {result}")
                    variable_values[var] = result
                    self.modified = True
                    continue
            
            # t1 = t2 + t3 (where t2 and t3 are known constants)
            match = p_binop_var_var.match(line)
            if match:
                var, var1, op, var2 = match.groups()
                if var1 in variable_values and var2 in variable_values:
                    result = self._compute(variable_values[var1], op, variable_values[var2])
                    new_lines.append(f"{var} = {result}")
                    variable_values[var] = result
                    self.modified = True
                    continue
            
            # --- 3. Constant and Copy Propagation ---
            
            # t1 = t2 (where t2 is a known constant)
            match = p_copy_assign.match(line)
            if match:
                var1, var2 = match.groups()
                # Check that var2 is not a digit (like 't1 = 10' which is p_const_assign)
                if not var2.isdigit() and var2 in variable_values:
                    result = variable_values[var2]
                    new_lines.append(f"{var1} = {result}")
                    variable_values[var1] = result
                    self.modified = True
                    continue
                elif var1 in variable_values:
                    # t1 = t2 (where t2 is NOT constant)
                    # We must remove t1 from our constant map
                    del variable_values[var1]
            
            # t1 = 10 (a new constant assignment)
            match = p_const_assign.match(line)
            if match:
                var, num = match.groups()
                variable_values[var] = int(num)
                new_lines.append(line)
                continue
            
            # --- 4. Conditional Branch Folding ---
            
            # if (10 < 20) GOTO L1 else GOTO L2
            match = p_cond_num_num.match(line)
            if match:
                num1, relop, num2, l_true, l_false = match.groups()
                if self._evaluate_condition(int(num1), relop, int(num2)):
                    new_lines.append(f"JUMP to {l_true}")
                else:
                    new_lines.append(f"JUMP to {l_false}")
                self.modified = True
                continue
                
            # if (t1 < 20) ... (where t1 is constant)
            match = p_cond_var_num.match(line)
            if match:
                var1, relop, num2, l_true, l_false = match.groups()
                if var1 in variable_values:
                    if self._evaluate_condition(variable_values[var1], relop, int(num2)):
                        new_lines.append(f"JUMP to {l_true}")
                    else:
                        new_lines.append(f"JUMP to {l_false}")
                    self.modified = True
                    continue

            # if (10 < t1) ... (where t1 is constant)
            match = p_cond_num_var.match(line)
            if match:
                num1, relop, var2, l_true, l_false = match.groups()
                if var2 in variable_values:
                    if self._evaluate_condition(int(num1), relop, variable_values[var2]):
                        new_lines.append(f"JUMP to {l_true}")
                    else:
                        new_lines.append(f"JUMP to {l_false}")
                    self.modified = True
                    continue

            # if (t1 < t2) ... (where t1 and t2 are constant)
            match = p_cond_var_var.match(line)
            if match:
                var1, relop, var2, l_true, l_false = match.groups()
                if var1 in variable_values and var2 in variable_values:
                    if self._evaluate_condition(variable_values[var1], relop, variable_values[var2]):
                        new_lines.append(f"JUMP to {l_true}")
                    else:
                        new_lines.append(f"JUMP to {l_false}")
                    self.modified = True
                    continue
            
            # if NOT (10 < 20) GOTO L1
            match = p_cond_not_num_num.match(line)
            if match:
                num1, relop, num2, label = match.groups()
                if not self._evaluate_condition(int(num1), relop, int(num2)):
                    new_lines.append(f"JUMP to {label}")
                # else: fall through
                self.modified = True
                continue
                
            # if NOT (t1 < 20) ... (where t1 is constant)
            match = p_cond_not_var_num.match(line)
            if match:
                var1, relop, num2, label = match.groups()
                if var1 in variable_values:
                    if not self._evaluate_condition(variable_values[var1], relop, int(num2)):
                        new_lines.append(f"JUMP to {label}")
                    # else: fall through
                    self.modified = True
                    continue

            # if NOT (10 < t1) ... (where t1 is constant)
            match = p_cond_not_num_var.match(line)
            if match:
                num1, relop, var2, label = match.groups()
                if var2 in variable_values:
                    if not self._evaluate_condition(int(num1), relop, variable_values[var2]):
                        new_lines.append(f"JUMP to {label}")
                    # else: fall through
                    self.modified = True
                    continue

            # if NOT (t1 < t2) ... (where t1 and t2 are constant)
            match = p_cond_not_var_var.match(line)
            if match:
                var1, relop, var2, label = match.groups()
                if var1 in variable_values and var2 in variable_values:
                    if not self._evaluate_condition(variable_values[var1], relop, variable_values[var2]):
                        new_lines.append(f"JUMP to {label}")
                    # else: fall through
                    self.modified = True
                    continue

            # --- 5. Default Case ---
            
            # Any other assignment (e.g., t1 = a + b)
            # This invalidates any constant value t1 might have had
            assign_match = re.match(r'^\s*(\w+)\s*=', line)
            if assign_match:
                var = assign_match.group(1)
                if var in variable_values:
                    del variable_values[var]

            new_lines.append(line)
        
        self.lines = new_lines

    def _compute(self, a: int, op: str, b: int) -> int:
        """Compute result of a op b."""
        if op == '+': return a + b
        if op == '-': return a - b
        if op == '*': return a * b
        if op == '/': return a // b if b != 0 else 0
        if op == '%': return a % b if b != 0 else 0
        return 0
    
    def _evaluate_condition(self, a: int, relop: str, b: int) -> bool:
        """Evaluate condition a relop b."""
        if relop == '<': return a < b
        if relop == '>': return a > b
        if relop == '<=': return a <= b
        if relop == '>=': return a >= b
        if relop == '==': return a == b
        if relop == '!=': return a != b
        return False
    
    def _dead_code_elimination(self):
        """
        Apply dead code elimination (unreachable code + unused variables).
        
        This function runs in two main passes, iterating until no more
        changes are made.
        
        1.  **Unreachable Code Elimination**: Uses a graph traversal (worklist)
            to find all lines of code that are reachable from the start.
            **This pass now includes a constant conditional evaluator.**
            It will simplify `if (0 == 1) ...` to its correct
            unconditional jump, thus finding unreachable blocks.
            
        2.  **Unused Variable Elimination**: Uses liveness analysis. It
            iterates *backwards* from the end of the program, tracking
            which variables are "live" (i.e., will be read in the future).
            An assignment to a variable that is not live is "dead"
            and can be removed.
        """
        
        # --- Pass 1: Unreachable Code Elimination ---
        reachable = set()
        queue = [0] # Start from the first line (index 0)
        self._build_label_map() # Ensure map is fresh
        
        if not self.lines:
            return

        # Pre-compile regexes for constant conditionals
        p_cond_num_num = re.compile(r'^\s*if\s+\(?(-?\d+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)')
        p_cond_not_num_num = re.compile(r'^\s*if\s+NOT\s+\(?(-?\d+)\s*([<>=!]+)\s*(-?\d+)\)?\s+GOTO\s+(\w+)')

        while queue:
            i = queue.pop(0)
            if i >= len(self.lines) or i in reachable:
                continue
            
            reachable.add(i)
            line = self.lines[i]

            # --- Evaluate constant conditionals FIRST ---

            # Pattern: if (10 < 20) GOTO L1 else GOTO L2
            match = p_cond_num_num.match(line)
            if match:
                num1, relop, num2, l_true, l_false = match.groups()
                if self._evaluate_condition(int(num1), relop, int(num2)):
                    # Condition is TRUE, only L_TRUE is reachable
                    if l_true in self.label_map and self.label_map[l_true] not in reachable:
                        queue.append(self.label_map[l_true])
                else:
                    # Condition is FALSE, only L_FALSE is reachable
                    if l_false in self.label_map and self.label_map[l_false] not in reachable:
                        queue.append(self.label_map[l_false])
                self.modified = True # We are simplifying this line
                continue # No fall-through

            # Pattern: if NOT (10 < 20) GOTO L1
            match = p_cond_not_num_num.match(line)
            if match:
                num1, relop, num2, label = match.groups()
                if not self._evaluate_condition(int(num1), relop, int(num2)):
                    # NOT(False) is True, so we JUMP
                    if label in self.label_map and self.label_map[label] not in reachable:
                        queue.append(self.label_map[label])
                    # No fall-through, as we must jump
                else:
                    # NOT(True) is False, so we FALL-THROUGH
                    if i + 1 < len(self.lines) and i + 1 not in reachable:
                        queue.append(i + 1)
                self.modified = True # We are simplifying this line
                continue

            # --- Handle non-constant and unconditional jumps ---

            # Unconditional jump (JUMP to L1)
            goto_match = re.match(r'^\s*JUMP\s+to\s+(\w+)', line)
            if goto_match:
                label = goto_match.group(1)
                if label in self.label_map and self.label_map[label] not in reachable:
                    queue.append(self.label_map[label])
                continue # No fall-through

            # Conditional jump (if (a < b) GOTO L1 else GOTO L2)
            if_else_match = re.match(r'^\s*if\s+\(.*\)\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)', line)
            if if_else_match:
                label_true, label_false = if_else_match.groups()
                if label_true in self.label_map and self.label_map[label_true] not in reachable:
                    queue.append(self.label_map[label_true])
                if label_false in self.label_map and self.label_map[label_false] not in reachable:
                    queue.append(self.label_map[label_false])
                continue # No fall-through

            # Conditional jump (if NOT (a < b) GOTO L1)
            if_not_match = re.match(r'^\s*if\s+NOT\s+\(.*\)\s+GOTO\s+(\w+)', line)
            if if_not_match:
                label = if_not_match.group(1)
                if label in self.label_map and self.label_map[label] not in reachable:
                    queue.append(self.label_map[label])
                # Fall-through is also possible
                if i + 1 < len(self.lines) and i + 1 not in reachable:
                    queue.append(i + 1)
                continue

            # Fall-through for all other lines (assignments, labels, etc.)
            if i + 1 < len(self.lines) and i + 1 not in reachable:
                queue.append(i + 1)
        
        # --- Filter and Rebuild Code from Pass 1 ---
        original_line_count = len(self.lines)
        new_lines = []
        
        # We need to *keep* referenced labels, even if the label line itself
        # was marked unreachable (e.g., in a loop).
        referenced_labels = set()
        for i in reachable:
            line = self.lines[i]
            match = re.search(r'GOTO\s+(\w+)', line)
            if match: referenced_labels.add(match.group(1))
            match = re.search(r'JUMP\s+to\s+(\w+)', line)
            if match: referenced_labels.add(match.group(1))

        for i, line in enumerate(self.lines):
            if i in reachable:
                # If it's a constant conditional we evaluated, simplify it
                match = p_cond_num_num.match(line)
                if match:
                    num1, relop, num2, l_true, l_false = match.groups()
                    if self._evaluate_condition(int(num1), relop, int(num2)):
                        new_lines.append(f"JUMP to {l_true}")
                    else:
                        new_lines.append(f"JUMP to {l_false}")
                    continue

                match = p_cond_not_num_num.match(line)
                if match:
                    num1, relop, num2, label = match.groups()
                    if not self._evaluate_condition(int(num1), relop, int(num2)):
                        new_lines.append(f"JUMP to {label}")
                    # else: fall through, line is effectively removed
                    continue
                
                new_lines.append(line)
            
            # Keep labels that are referenced, even if unreachable
            # (This prevents dataflow from breaking in liveness pass)
            elif line.startswith("LABEL"):
                match = re.match(r'^LABEL\s+(\w+):', line)
                if match and match.group(1) in referenced_labels:
                    new_lines.append(line)
        
        if len(new_lines) != original_line_count:
            self.modified = True
            
        self.lines = new_lines
        self._build_label_map() # Rebuild map after removing lines

        # --- Pass 2: Unused Variable Elimination (Liveness Analysis) ---
        live_vars = set()
        final_lines = [] # Build the final list here

        # Find all variables that have side effects (memory, I/O, return)
        # and are "live" by default.
        for line in self.lines:
            if (line.startswith('alloc') or line.startswith('*') or 
                "printf" in line or "scanf" in line or "return" in line):
                used_vars = re.findall(r'\b([a-zA-Z_]\w*)\b', line)
                live_vars.update(used_vars)

        for line in reversed(self.lines):
            is_live = False
            
            # Define essential lines that are always "live"
            if (line.startswith("LABEL") or line.startswith("if") or 
                line.startswith("JUMP") or line.startswith("GOTO") or 
                line.startswith("alloc") or line.startswith("*") or
                "printf" in line or "scanf" in line or "return" in line):
                is_live = True

            # Find variables used/read in this line
            used_in_line = set()
            # 1. RHS of = (e.g., t1 = R1 + R2)
            match = re.match(r'^\s*\w+\s*=\s*(.*)$', line)
            if match:
                expr = match.group(1)
                reads = re.findall(r'\b([a-zA-Z_]\w*)\b', expr)
                used_in_line.update(reads)
            
            # 2. Inside an if(...)
            match = re.match(r'^\s*if\s+\(?(.*)\)?\s+GOTO', line)
            if match:
                expr = match.group(1)
                reads = re.findall(r'\b([a-zA-Z_]\w*)\b', expr)
                used_in_line.update(reads)

            # 3. Store to memory: *R1 = R2 (reads R1 and R2)
            match = re.match(r'^\s*\*\s*(\w+)\s*=\s*([\w\d.-]+)', line)
            if match:
                used_in_line.add(match.group(1))
                if not match.group(2).isdigit():
                    used_in_line.add(match.group(2))

            # Find variable defined/written in this line
            assign_match = re.match(r'^\s*(\w+)\s*=', line)
            defined_var = None
            
            if assign_match:
                defined_var = assign_match.group(1)
                if defined_var in live_vars:
                    # This assignment is live because its result is used later
                    is_live = True
                    live_vars.remove(defined_var)
            
            # Add all used variables to the live set for the next iteration
            live_vars.update(used_in_line)
            
            if is_live:
                final_lines.append(line)
            elif not assign_match:
                # This is a non-essential, non-assignment line
                # (e.g., an empty line that snuck in).
                # We can safely ignore it.
                pass
            else:
                # This is a dead assignment (e.g., t1 = a + b where t1 is not live)
                # We mark that we made a change and *do not* add the line
                self.modified = True

        final_lines.reverse()
        if len(final_lines) != len(self.lines):
            self.modified = True
            
        self.lines = final_lines
    
    def _common_subexpression_elimination(self):
        """Apply common subexpression elimination within basic blocks."""
        new_lines = []
        expr_to_var = {}  # Maps (op, op1, op2) -> var

        for line in self.lines:
            # New block starts at a label, clear the expression cache
            if line.startswith("LABEL") or "GOTO" in line or "JUMP" in line:
                new_lines.append(line)
                expr_to_var = {}
                continue
            
            # A store to memory must invalidate any expression that reads from memory
            # (e.g., *t1 = ...) or involves array addresses (&arr)
            if line.startswith("*") or line.startswith("alloc"):
                new_lines.append(line)
                expr_to_var = {} # Be safe, clear everything
                continue
            
            # Pattern: t1 = op1 op op2
            match = re.match(r'^\s*(\w+)\s*=\s*(\w+)\s*([+\-*/%])\s*(\w+)\s*$', line)
            if match:
                var, op1, op, op2 = match.groups()
                
                # Canonicalize: (a + b) is same as (b + a)
                if op in ['+', '*'] and op1 > op2:
                    op1, op2 = op2, op1
                
                expr_key = (op, op1, op2)
                
                if expr_key in expr_to_var:
                    # Found CSE! Replace with copy.
                    new_lines.append(f"{var} = {expr_to_var[expr_key]}")
                    self.modified = True
                else:
                    # First time. Add line and store expression.
                    new_lines.append(line)
                    expr_to_var[expr_key] = var
                
                # Invalidate any expressions that used `var`
                invalid_keys = [k for k, v in expr_to_var.items() if var in (v, k[1], k[2])]
                for k in invalid_keys:
                    if k in expr_to_var:
                        del expr_to_var[k]
                # Re-add the current expression
                expr_to_var[expr_key] = var
                continue
            
            # Any other assignment invalidates old expressions using that var
            assign_match = re.match(r'^\s*(\w+)\s*=', line)
            if assign_match:
                var = assign_match.group(1)
                invalid_keys = [k for k, v in expr_to_var.items() if var in (v, k[1], k[2])]
                for k in invalid_keys:
                    if k in expr_to_var:
                        del expr_to_var[k]

            new_lines.append(line)
        
        self.lines = new_lines
    
    def _strength_reduction(self):
        """
        Apply strength reduction for expensive operations in loops.
        This is a safe, non-destructive-modification implementation.
        """
        loops = self._identify_loops()
        if not loops:
            return

        # --- Analysis Pass ---
        # We perform analysis on self.lines and build a plan of modifications.
        # We don't modify self.lines directly.
        
        lines_to_add_in_preheader = {} # Map pre_header_idx -> [list of init lines]
        lines_to_replace = {}          # Map line_idx -> new_line
        lines_to_add_post_iv_step = {} # Map iv_step_idx -> [list of step lines]
        indices_to_delete = set()      # Not used here, but good for other refactors

        for loop_header_idx, loop_end_idx in loops:
            iv_data = self._find_induction_variable(loop_header_idx, loop_end_idx, self.lines)
            if not iv_data:
                continue
            
            iv, iv_step_val, iv_step_line_idx = iv_data

            pre_header_idx = loop_header_idx - 1
            if pre_header_idx < 0:
                continue

            # Find IV initial value
            iv_init_val = None
            for i in range(pre_header_idx, -1, -1):
                if self.lines[i].startswith("LABEL"):
                    break
                init_match = re.match(rf'^\s*{re.escape(iv)}\s*=\s*(-?\d+)\s*$', self.lines[i])
                if init_match:
                    iv_init_val = int(init_match.group(1))
                    break
            
            if iv_init_val is None:
                continue # Cannot optimize

            # We are making a change
            self.modified = True
            
            if pre_header_idx not in lines_to_add_in_preheader:
                lines_to_add_in_preheader[pre_header_idx] = []
            if iv_step_line_idx not in lines_to_add_post_iv_step:
                lines_to_add_post_iv_step[iv_step_line_idx] = []

            # Find all reducible operations in this loop
            for i in range(loop_header_idx + 1, loop_end_idx + 1):
                line = self.lines[i]
                match = re.match(rf'^\s*(\w+)\s*=\s*{re.escape(iv)}\s*\*\s*(-?\d+)\s*$', line)
                if match:
                    result_var, const_val_str = match.groups()
                    const_val = int(const_val_str)
                    
                    new_temp_var = f"t{self.temp_counter}"
                    self.temp_counter += 1
                    
                    new_init_val = iv_init_val * const_val
                    new_step_val = iv_step_val * const_val
                    
                    lines_to_add_in_preheader[pre_header_idx].append(f"{new_temp_var} = {new_init_val}")
                    lines_to_add_post_iv_step[iv_step_line_idx].append(f"{new_temp_var} = {new_temp_var} + {new_step_val}")
                    lines_to_replace[i] = f"{result_var} = {new_temp_var}"
        
        # --- Rebuilding Pass ---
        if not self.modified:
            return

        final_lines = []
        for i, line in enumerate(self.lines):
            # 1. Add pre-header lines (if any)
            if i in lines_to_add_in_preheader:
                final_lines.extend(lines_to_add_in_preheader[i])
            
            # 2. Replace or keep the current line
            if i in lines_to_replace:
                final_lines.append(lines_to_replace[i])
            elif i not in indices_to_delete:
                final_lines.append(line)
            
            # 3. Add new step lines (if any)
            if i in lines_to_add_post_iv_step:
                final_lines.extend(lines_to_add_post_iv_step[i])

        self.lines = final_lines

    def _find_induction_variable(self, loop_start: int, loop_end: int, lines: List[str]) -> Optional[Tuple[str, int, int]]:
        """Finds the primary induction variable (e.g., i = i + 1) in a loop."""
        for i in range(loop_start, loop_end + 1):
            if i >= len(lines): break
            line = lines[i]
            # Pattern: i = i + 1
            match = re.match(r'^\s*(\w+)\s*=\s*\1\s*\+\s*(-?\d+)\s*$', line)
            if match:
                var, step = match.groups()
                end_line = lines[loop_end]
                if f"({var} <" in end_line or f"({var} >" in end_line or f"({var} !=" in end_line:
                    return var, int(step), i
            # Pattern: i = i - 1
            match = re.match(r'^\s*(\w+)\s*=\s*\1\s*-\s*(-?\d+)\s*$', line)
            if match:
                var, step = match.groups()
                end_line = lines[loop_end]
                if f"({var} <" in end_line or f"({var} >" in end_line or f"({var} !=" in end_line:
                    return var, -int(step), i
        return None

    def _identify_loops(self) -> List[Tuple[int, int]]:
        """Identify loop boundaries (header index, end index)."""
        loops = []
        for i, line in enumerate(self.lines):
            jump_match = re.search(r'JUMP\s+to\s+(\w+)', line)
            if jump_match:
                label = jump_match.group(1)
                if label in self.label_map:
                    target = self.label_map[label]
                    if target < i:  # Back edge (jumping backwards)
                        loops.append((target, i)) # (loop_header_idx, loop_end_idx)
        
        # Sort loops by header index to process them in order
        loops.sort(key=lambda x: x[0])
        return loops
    
    def _loop_invariant_code_motion(self):
        """
        Move loop-invariant code outside loops.
        This is a safe, non-destructive-modification implementation.
        """
        loops = self._identify_loops()
        if not loops:
            return
            
        # --- Analysis Pass ---
        lines_to_move_by_header = {} # Map loop_header_idx -> [list of invariant lines]
        indices_to_delete = set()

        # We must process loops from the innermost outwards.
        # Sorting by loop size (end - start) is a good heuristic for this.
        loops.sort(key=lambda x: x[1] - x[0])
        
        for loop_header_idx, loop_end_idx in loops:
            pre_header_idx = loop_header_idx - 1
            if pre_header_idx < 0:
                continue
                
            invariant_moved_this_pass = True
            while invariant_moved_this_pass: # Keep iterating until no more code can be moved
                invariant_moved_this_pass = False
                
                # Find variables defined *inside* the loop
                defined_in_loop = set()
                for i in range(loop_header_idx + 1, loop_end_idx):
                    if i in indices_to_delete: # Skip lines we've already moved
                        continue
                    match = re.match(r'^\s*(\w+)\s*=', self.lines[i])
                    if match:
                        defined_in_loop.add(match.group(1))

                # Find invariant lines to move
                lines_to_move = [] # (index, line)
                for i in range(loop_header_idx + 1, loop_end_idx):
                    if i in indices_to_delete:
                        continue
                        
                    line = self.lines[i]
                    
                    # Skip control flow, labels, memory stores, etc.
                    if (not line.strip() or 
                        re.match(r'^LABEL\s+\w+:', line) or
                        'GOTO' in line or 'JUMP' in line or
                        line.strip().startswith('if ') or
                        line.strip().startswith('*')):
                        continue
                    
                    is_invariant = False
                    
                    # Pattern: t1 = a + b
                    match = re.match(r'^\s*(\w+)\s*=\s*(\w+)\s*([+\-*/%])\s*(\w+)\s*$', line)
                    if match:
                        var, op1, op, op2 = match.groups()
                        if op1 not in defined_in_loop and op2 not in defined_in_loop:
                            is_invariant = True
                            
                    # Pattern: t1 = 10 (Constant)
                    elif re.match(r'^\s*(\w+)\s*=\s*(-?\d+)\s*$', line):
                        is_invariant = True
                        
                    # Pattern: t1 = &arr1 (Address)
                    elif re.match(r'^\s*(\w+)\s*=\s*&\s*(\w+)\s*$', line):
                        is_invariant = True
                    
                    # Pattern: t1 = a (Copy)
                    else:
                        match_copy = re.match(r'^\s*(\w+)\s*=\s*(\w+)\s*$', line)
                        if match_copy:
                            if match_copy.group(1).isdigit() or match_copy.group(2).isdigit():
                                continue # This is a const assignment, handled above
                            var, op1 = match_copy.groups()
                            if op1 not in defined_in_loop:
                                is_invariant = True

                    if is_invariant:
                        lines_to_move.append((i, line))
                
                # Store the lines to be moved
                if lines_to_move:
                    self.modified = True
                    invariant_moved_this_pass = True
                    
                    if loop_header_idx not in lines_to_move_by_header:
                        lines_to_move_by_header[loop_header_idx] = []
                        
                    for i, line in lines_to_move:
                        lines_to_move_by_header[loop_header_idx].append(line)
                        indices_to_delete.add(i)

        # --- Rebuilding Pass ---
        if not self.modified:
            return

        final_lines = []
        for i, line in enumerate(self.lines):
            # 1. Add pre-header lines (if any)
            # We add them *before* the label they are associated with
            if i in lines_to_move_by_header:
                final_lines.extend(lines_to_move_by_header[i])
            
            # 2. Add or skip the current line
            if i not in indices_to_delete:
                final_lines.append(line)

        self.lines = final_lines


def optimize_ir(input_file: str, optimizations: List[str], output_file: str = "optimized_ic.txt"):
    """
    Main function to optimize intermediate code.
    
    Args:
        input_file: Path to input IR file (e.g., "original_ic.txt")
        optimizations: List of optimization names to apply
        output_file: Path to output file (default: "optimized_ic.txt")
    """
    try:
        # Read input file
        with open(input_file, 'r', encoding='utf-8') as f:
            ir_content = f.read()
        
        # Create optimizer and apply optimizations
        optimizer = Optimizer(ir_content)
        optimized_ir = optimizer.optimize(optimizations)
        
        # Write output file
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(optimized_ir)
        
        return True
        
    except Exception as e:
        print(f"Error during optimization: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc(file=sys.stderr)
        return False


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python optimizer.py <input_file> <optimization1> [optimization2] ...")
        print("Example: python optimizer.py original_ic.txt 'Constant Folding' 'Dead Code Elimination'")
        sys.exit(1)
    
    input_file = sys.argv[1]
    # Handle single-quoted arguments from shell
    optimizations = [opt.strip("'") for opt in sys.argv[2:]]
    
    success = optimize_ir(input_file, optimizations)
    
    if success:
        print("Done")
    else:
        sys.exit(1)