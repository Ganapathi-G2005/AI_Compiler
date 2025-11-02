#!/usr/bin/env python3
"""
IR-to-C Translator
Converts three-address code intermediate representation to executable C code.
"""

import re
import sys
from typing import Set, Dict, List


class IRToCTranslator:
    """Translates Intermediate Representation (IR) to C code."""
    
    def __init__(self, ir_content: str):
        """
        Initialize translator with IR content.
        
        Args:
            ir_content: String containing the intermediate code
        """
        self.lines = [line.strip() for line in ir_content.split('\n') if line.strip()]
        self.variables: Set[str] = set()
        self.temp_variables: Set[str] = set()
        self.labels: Set[str] = set()
        self.pointer_variables: Set[str] = set()  # Variables that store pointers
        
    def extract_variables_and_labels(self):
        """Extract all variables and labels from IR."""
        # Pattern for variable names (alphanumeric and underscore, not starting with number)
        var_pattern = r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b'
        label_pattern = r'LABEL\s+(\w+):'
        goto_pattern = r'GOTO\s+(\w+)'
        jump_pattern = r'JUMP\s+to\s+(\w+)'
        if_goto_pattern = r'if\s*\(.+\)\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)'
        
        for line in self.lines:
            # Extract labels first
            label_match = re.search(label_pattern, line, re.IGNORECASE)
            if label_match:
                self.labels.add(label_match.group(1))
            
            # Extract labels from GOTO/JUMP
            goto_match = re.search(goto_pattern, line, re.IGNORECASE)
            if goto_match:
                self.labels.add(goto_match.group(1))
            
            jump_match = re.search(jump_pattern, line, re.IGNORECASE)
            if jump_match:
                self.labels.add(jump_match.group(1))
            
            # Extract labels from if-else GOTO
            if_goto_match = re.search(if_goto_pattern, line, re.IGNORECASE)
            if if_goto_match:
                self.labels.add(if_goto_match.group(1))
                self.labels.add(if_goto_match.group(2))
            
            # Skip label lines when extracting variables
            if line.strip().startswith('LABEL'):
                continue
            
            # Extract variables (but exclude keywords, numbers, and labels)
            matches = re.findall(var_pattern, line)
            for match in matches:
                # Skip if it's a label
                if match in self.labels:
                    continue
                # Skip if it's a keyword or number
                if match.lower() in ['if', 'else', 'goto', 'label', 'jump', 'to', 'not', 'alloc']:
                    continue
                # Check if it's a number
                try:
                    float(match)
                    continue
                except ValueError:
                    pass
                # Check if it's a temporary variable (starts with 't' followed by digits)
                if re.match(r'^t\d+$', match):
                    self.temp_variables.add(match)
                else:
                    self.variables.add(match)
    
    def translate_instruction(self, line: str) -> str:
        """
        Translate a single IR instruction to C code.
        
        Args:
            line: Single line of IR code
            
        Returns:
            Translated C code line
        """
        line = line.strip()
        if not line:
            return ""
        
        # Handle LABEL
        label_match = re.match(r'^LABEL\s+(\w+):\s*$', line)
        if label_match:
            label_name = label_match.group(1)
            return f"    {label_name}:"
        
        # Handle array allocation (skip, handled in variable declarations)
        if re.match(r'^alloc\s+\w+,\s*\d+\s*$', line, re.IGNORECASE):
            return ""  # Skip alloc statements (already handled)
        
        # Handle pointer assignment: *ptr = value
        ptr_assign_match = re.match(r'^\*(\w+)\s*=\s*(.+)$', line)
        if ptr_assign_match:
            ptr = ptr_assign_match.group(1)
            value = ptr_assign_match.group(2).strip()
            # Check if ptr is used in pointer arithmetic (will be a pointer)
            for prev_line in self.lines[:self.lines.index(line) if line in self.lines else len(self.lines)]:
                if f"{ptr} +" in prev_line or f"{ptr} -" in prev_line:
                    # This is used in pointer arithmetic, so it's a pointer
                    self.pointer_variables.add(ptr)
                    break
            return f"    *{ptr} = {value};"
        
        
        # Handle address assignment: var = &array
        addr_assign_match = re.match(r'^(\w+)\s*=\s*&(\w+)\s*$', line)
        if addr_assign_match:
            var = addr_assign_match.group(1)
            array = addr_assign_match.group(2)
            self.pointer_variables.add(var)
            # In C, array name already decays to int* (pointer to first element)
            # Using &array gives int (*)[N] (pointer to array), which is incompatible
            # So we use just the array name, which automatically decays to int*
            return f"    {var} = {array};  // Array name decays to pointer to first element"
        
        # Handle assignment: var = value
        assign_match = re.match(r'^(\w+)\s*=\s*(.+)$', line)
        if assign_match:
            var = assign_match.group(1)
            expr = assign_match.group(2).strip()
            # Check if expression needs translation (arithmetic operations)
            # Simple case: just a number or variable
            if re.match(r'^[\w.]+$', expr):
                return f"    {var} = {expr};"
            # Arithmetic operations: t0 = a + b
            arith_match = re.match(r'^(\w+)\s*([+\-*/])\s*(\w+)$', expr)
            if arith_match:
                left = arith_match.group(1)
                op = arith_match.group(2)
                right = arith_match.group(3)
                return f"    {var} = {left} {op} {right};"
        
        # Handle if NOT condition GOTO
        if_not_goto_match = re.match(r'^if\s+NOT\s+\((.+)\)\s+GOTO\s+(\w+)\s*$', line, re.IGNORECASE)
        if if_not_goto_match:
            condition = if_not_goto_match.group(1).strip()
            label = if_not_goto_match.group(2)
            # Negate the condition
            return f"    if (!({condition})) {{\n        goto {label};\n    }}"
        
        # Handle if-else GOTO
        if_goto_match = re.match(r'^if\s*\((.+)\)\s+GOTO\s+(\w+)\s+else\s+GOTO\s+(\w+)\s*$', line, re.IGNORECASE)
        if if_goto_match:
            condition = if_goto_match.group(1).strip()
            true_label = if_goto_match.group(2)
            false_label = if_goto_match.group(3)
            return f"    if ({condition}) {{\n        goto {true_label};\n    }} else {{\n        goto {false_label};\n    }}"
        
        # Handle GOTO
        goto_match = re.match(r'^GOTO\s+(\w+)\s*$', line, re.IGNORECASE)
        if goto_match:
            label = goto_match.group(1)
            return f"    goto {label};"
        
        # Handle JUMP to (same as GOTO)
        jump_match = re.match(r'^JUMP\s+to\s+(\w+)\s*$', line, re.IGNORECASE)
        if jump_match:
            label = jump_match.group(1)
            return f"    goto {label};"
        
        # If no pattern matches, return as comment or skip
        return f"    // {line}"
    
    def translate(self) -> str:
        """
        Translate entire IR to C code.
        
        Returns:
            Complete C program as string
        """
        self.extract_variables_and_labels()
        
        # First pass: identify pointer variables by analyzing all instructions
        for line in self.lines:
            # Check for address assignment
            addr_assign_match = re.match(r'^(\w+)\s*=\s*&(\w+)\s*$', line)
            if addr_assign_match:
                var = addr_assign_match.group(1)
                self.pointer_variables.add(var)
        
        # Second pass: identify pointer arithmetic results (iterate multiple times to catch all)
        changed = True
        while changed:
            changed = False
            for i, line in enumerate(self.lines):
                ptr_arith_match = re.match(r'^(\w+)\s*=\s*(\w+)\s*([+\-])\s*(\w+)\s*$', line)
                if ptr_arith_match:
                    result = ptr_arith_match.group(1)
                    left = ptr_arith_match.group(2)
                    if left in self.pointer_variables and result not in self.pointer_variables:
                        self.pointer_variables.add(result)
                        changed = True
        
        # Third pass: identify pointers used in dereferencing
        for line in self.lines:
            ptr_deref_match = re.match(r'^\*(\w+)\s*=', line)
            if ptr_deref_match:
                ptr = ptr_deref_match.group(1)
                # Check if this pointer was used in arithmetic before
                for prev_line in self.lines:
                    if prev_line.startswith(f"{ptr} = ") and ("+ " in prev_line or "- " in prev_line):
                        # This is a pointer result from arithmetic
                        if ptr not in self.pointer_variables:
                            self.pointer_variables.add(ptr)
                            changed = True
        
        # Generate variable declarations
        c_code_lines = ["#include <stdio.h>", "", "int main() {", ""]
        
        # Declare all variables (exclude labels - they don't need declarations in C)
        all_vars = sorted(self.variables | self.temp_variables)
        # Filter out any labels that might have been incorrectly identified as variables
        all_vars = [v for v in all_vars if v not in self.labels]
        
        # Check if array is used and get its size
        array_size = 80  # default
        has_array = False
        for line in self.lines:
            if 'alloc arr' in line.lower():
                has_array = True
                # Extract array size from "alloc arr, size" format
                alloc_match = re.search(r'alloc\s+\w+,\s*(\d+)', line, re.IGNORECASE)
                if alloc_match:
                    # Size is in bytes (4 bytes per int), so divide by 4 to get element count
                    array_size_bytes = int(alloc_match.group(1))
                    array_size = array_size_bytes // 4
                break
            elif '&arr' in line or (has_array and 'arr' in line):
                has_array = True
        
        if has_array:
            c_code_lines.append(f"    int arr[{array_size}];  // Array allocation")
            # Remove 'arr' from regular variables if present
            all_vars = [v for v in all_vars if v != 'arr']
        
        # Separate pointer variables from regular variables
        pointer_vars = [v for v in all_vars if v in self.pointer_variables]
        regular_vars = [v for v in all_vars if v not in self.pointer_variables]
        
        if pointer_vars:
            # Group pointer variables (each needs * prefix in C)
            for i in range(0, len(pointer_vars), 10):
                vars_group = pointer_vars[i:i+10]
                # Prefix each variable with * for proper pointer declaration
                pointer_decls = ", ".join("*" + v for v in vars_group)
                c_code_lines.append(f"    int {pointer_decls};")
            c_code_lines.append("")
        
        if regular_vars:
            # Group variables for cleaner output (max 10 per line)
            var_decls = []
            for i in range(0, len(regular_vars), 10):
                vars_group = regular_vars[i:i+10]
                var_decls.append("    int " + ", ".join(vars_group) + ";")
            c_code_lines.extend(var_decls)
            c_code_lines.append("")
        
        # Translate instructions
        for line in self.lines:
            translated = self.translate_instruction(line)
            if translated:
                # Handle multi-line instructions (like if-else)
                if '\n' in translated:
                    c_code_lines.append(translated)
                else:
                    c_code_lines.append(translated)
        
        c_code_lines.append("    return 0;")
        c_code_lines.append("}")
        
        return '\n'.join(c_code_lines)


def translate_ir_to_c(input_file: str, output_file: str) -> bool:
    """
    Translate IR file to C file.
    
    Args:
        input_file: Path to input IR file
        output_file: Path to output C file
        
    Returns:
        True if successful, False otherwise
    """
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            ir_content = f.read()
        
        translator = IRToCTranslator(ir_content)
        c_code = translator.translate()
        
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(c_code)
        
        return True
        
    except Exception as e:
        print(f"Error translating IR to C: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc(file=sys.stderr)
        return False


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python ir_to_c.py <input_ir_file> <output_c_file>", file=sys.stderr)
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    success = translate_ir_to_c(input_file, output_file)
    sys.exit(0 if success else 1)

