#!/usr/bin/env python3
"""
GUI for displaying optimization results

Shows original vs optimized IR with statistics and cost analysis.
"""

import tkinter as tk
from tkinter import ttk, filedialog, scrolledtext, messagebox
import os
import sys
import re
import subprocess
import time
import threading
from optimization_predictor import OptimizationPredictor
from build_executables import build_executable
from compare_runtime import run_executable

class OptimizationGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("C Compiler Optimization Analyzer")
        self.root.geometry("1600x950")  # Wider to accommodate side-by-side stats and runtime
        
        # Instruction costs (in cycles/units)
        self.instruction_costs = {
            'add': 2,
            'sub': 2,
            '+': 2,
            '-': 2,
            'mul': 4,
            'div': 6,
            '*': 4,
            '/': 6,
            '%': 6,
            'load': 1,
            'store': 1,
            'jump': 1,
            'goto': 1,
            'if': 1,
            'alloc': 0,
            '=': 1,  # assignment
            '&': 0,  # address-of
            '*': 1,  # dereference
        }
        
        self.setup_ui()
        
    def setup_ui(self):
        # Main container
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)  # For side-by-side stats and runtime
        main_frame.rowconfigure(2, weight=2)  # Give more weight to statistics/runtime
        main_frame.rowconfigure(3, weight=3)  # Code comparison area
        
        # Title
        title_label = ttk.Label(main_frame, text="Compiler Optimization Analyzer", 
                               font=("Arial", 16, "bold"))
        title_label.grid(row=0, column=0, columnspan=2, pady=(0, 10))
        
        # File selection frame
        file_frame = ttk.Frame(main_frame)
        file_frame.grid(row=1, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=(0, 10))
        file_frame.columnconfigure(1, weight=1)
        
        ttk.Label(file_frame, text="C File:").grid(row=0, column=0, padx=(0, 5))
        
        self.file_entry = ttk.Entry(file_frame, width=50)
        self.file_entry.grid(row=0, column=1, sticky=(tk.W, tk.E), padx=(0, 5))
        
        browse_btn = ttk.Button(file_frame, text="Browse", command=self.browse_file)
        browse_btn.grid(row=0, column=2, padx=(0, 5))
        
        analyze_btn = ttk.Button(file_frame, text="Analyze", command=self.analyze_code)
        analyze_btn.grid(row=0, column=3)
        
        # Statistics and Runtime Comparison frames - side by side
        stats_runtime_frame = ttk.Frame(main_frame)
        stats_runtime_frame.grid(row=2, column=0, columnspan=2, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 10))
        stats_runtime_frame.columnconfigure(0, weight=1)
        stats_runtime_frame.columnconfigure(1, weight=1)
        stats_runtime_frame.rowconfigure(0, weight=1)
        
        # Statistics frame - left side
        stats_frame = ttk.LabelFrame(stats_runtime_frame, text="Optimization Statistics", padding="10")
        stats_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(0, 5))
        stats_frame.columnconfigure(0, weight=1)
        stats_frame.rowconfigure(0, weight=1)
        
        # Stats display with better font and more space
        self.stats_text = tk.Text(stats_frame, height=12, font=("Consolas", 10), wrap=tk.WORD)
        self.stats_text.pack(fill=tk.BOTH, expand=True)
        
        # Runtime Comparison frame - right side
        runtime_frame = ttk.LabelFrame(stats_runtime_frame, text="Runtime Performance Comparison", padding="10")
        runtime_frame.grid(row=0, column=1, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(5, 0))
        runtime_frame.columnconfigure(0, weight=1)
        runtime_frame.rowconfigure(0, weight=1)
        
        # Runtime display
        self.runtime_text = tk.Text(runtime_frame, height=12, font=("Consolas", 10), wrap=tk.WORD)
        self.runtime_text.pack(fill=tk.BOTH, expand=True)
        
        # Status label for building/running executables
        self.runtime_status = ttk.Label(runtime_frame, text="Click 'Analyze' to build and compare executables", 
                                        font=("Arial", 9), foreground="gray")
        self.runtime_status.pack(pady=(5, 0))
        
        # Comparison frame (side by side)
        comparison_frame = ttk.Frame(main_frame)
        comparison_frame.grid(row=3, column=0, columnspan=2, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 10))
        comparison_frame.columnconfigure(0, weight=1)
        comparison_frame.columnconfigure(1, weight=1)
        comparison_frame.rowconfigure(0, weight=1)
        
        # Original IR frame
        original_frame = ttk.LabelFrame(comparison_frame, text="Original Intermediate Code", padding="5")
        original_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(0, 5))
        original_frame.columnconfigure(0, weight=1)
        original_frame.rowconfigure(0, weight=1)
        
        self.original_text = scrolledtext.ScrolledText(original_frame, font=("Courier", 9), 
                                                       wrap=tk.NONE, width=50)
        self.original_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Optimized IR frame
        optimized_frame = ttk.LabelFrame(comparison_frame, text="Optimized Intermediate Code", padding="5")
        optimized_frame.grid(row=0, column=1, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(5, 0))
        optimized_frame.columnconfigure(0, weight=1)
        optimized_frame.rowconfigure(0, weight=1)
        
        self.optimized_text = scrolledtext.ScrolledText(optimized_frame, font=("Courier", 9),
                                                         wrap=tk.NONE, width=50)
        self.optimized_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Optimization info frame
        info_frame = ttk.LabelFrame(main_frame, text="Optimization Applied", padding="10")
        info_frame.grid(row=4, column=0, columnspan=2, sticky=(tk.W, tk.E))
        info_frame.columnconfigure(0, weight=1)
        
        self.info_text = tk.Text(info_frame, height=4, font=("Arial", 10))
        self.info_text.pack(fill=tk.BOTH, expand=True)
        
    def browse_file(self):
        filename = filedialog.askopenfilename(
            title="Select C File",
            filetypes=[("C files", "*.c"), ("All files", "*.*")]
        )
        if filename:
            self.file_entry.delete(0, tk.END)
            self.file_entry.insert(0, filename)
    
    def analyze_code(self):
        file_path = self.file_entry.get()
        
        if not file_path or not os.path.exists(file_path):
            messagebox.showerror("Error", "Please select a valid C file!")
            return
        
        try:
            # Clear previous results
            self.original_text.delete(1.0, tk.END)
            self.optimized_text.delete(1.0, tk.END)
            self.stats_text.delete(1.0, tk.END)
            self.runtime_text.delete(1.0, tk.END)
            self.info_text.delete(1.0, tk.END)
            self.runtime_status.config(text="Building executables...", foreground="blue")
            
            # Run optimization predictor
            predictor = OptimizationPredictor()
            results = predictor.predict_optimization(file_path, show_details=False)
            
            if "error" in results:
                messagebox.showerror("Error", f"Failed to analyze code: {results['error']}")
                return
            
            # Read original IR
            if os.path.exists('original_ic.txt'):
                with open('original_ic.txt', 'r', encoding='utf-8') as f:
                    original_ir = f.read()
                self.original_text.insert(1.0, original_ir)
            else:
                self.original_text.insert(1.0, "Original IR not found!")
            
            # Read optimized IR
            if os.path.exists('optimized_ic.txt'):
                with open('optimized_ic.txt', 'r', encoding='utf-8') as f:
                    optimized_ir = f.read()
                self.optimized_text.insert(1.0, optimized_ir)
            else:
                self.optimized_text.insert(1.0, "Optimized IR not found!")
            
            # Calculate statistics
            original_stats = self.calculate_statistics(original_ir)
            optimized_stats = self.calculate_statistics(optimized_ir)
            
            # Calculate improvement metrics
            instr_reduction = original_stats['instruction_count'] - optimized_stats['instruction_count']
            cost_savings = original_stats['total_cost'] - optimized_stats['total_cost']
            cost_reduction_pct = ((1 - optimized_stats['total_cost']/original_stats['total_cost']) * 100) if original_stats['total_cost'] > 0 else 0
            instr_reduction_pct = ((1 - optimized_stats['instruction_count']/original_stats['instruction_count']) * 100) if original_stats['instruction_count'] > 0 else 0
            
            # Calculate average cost per instruction
            orig_avg_cost = original_stats['total_cost'] / original_stats['instruction_count'] if original_stats['instruction_count'] > 0 else 0
            opt_avg_cost = optimized_stats['total_cost'] / optimized_stats['instruction_count'] if optimized_stats['instruction_count'] > 0 else 0
            
            # Display statistics with improved formatting
            stats_display = f"""
═══════════════════════════════════════════════════════════════════════════════
                          OPTIMIZATION STATISTICS REPORT
═══════════════════════════════════════════════════════════════════════════════

ORIGINAL INTERMEDIATE CODE:
───────────────────────────────────────────────────────────────────────────────
  Total Instructions:       {original_stats['instruction_count']:>6}
  Total Execution Cost:     {original_stats['total_cost']:>6} cycles
  Average Cost/Instruction: {orig_avg_cost:>6.2f} cycles
───────────────────────────────────────────────────────────────────────────────

OPTIMIZED INTERMEDIATE CODE:
───────────────────────────────────────────────────────────────────────────────
  Total Instructions:       {optimized_stats['instruction_count']:>6}
  Total Execution Cost:     {optimized_stats['total_cost']:>6} cycles
  Average Cost/Instruction: {opt_avg_cost:>6.2f} cycles
───────────────────────────────────────────────────────────────────────────────

PERFORMANCE IMPROVEMENT:
───────────────────────────────────────────────────────────────────────────────
  Instructions Removed:     {instr_reduction:>6}  ({instr_reduction_pct:>5.1f}% reduction)
  Execution Cost Saved:     {cost_savings:>6} cycles  ({cost_reduction_pct:>5.1f}% reduction)
  
  Efficiency Gain:          {cost_reduction_pct:>5.1f}% faster execution
  Code Size Reduction:      {instr_reduction_pct:>5.1f}% smaller code
───────────────────────────────────────────────────────────────────────────────

COST BREAKDOWN (per instruction type):
───────────────────────────────────────────────────────────────────────────────
  Addition/Subtraction:      2 cycles each
  Multiplication:           4 cycles each
  Division/Modulo:          6 cycles each
  Assignment/Load/Store:    1 cycle each
  Control Flow (jump/goto): 1 cycle each
═══════════════════════════════════════════════════════════════════════════════
"""
            self.stats_text.insert(1.0, stats_display)
            
            # Display optimization info
            opt_name = results['predicted_optimization']
            
            info_display = f"""
Optimization Applied: {opt_name}

{self.get_optimization_description(opt_name)}
"""
            self.info_text.insert(1.0, info_display)
            
            # Build executables and compare runtime (in a separate thread to avoid blocking)
            self.build_and_compare_runtime()
            
        except Exception as e:
            messagebox.showerror("Error", f"An error occurred: {str(e)}")
            import traceback
            traceback.print_exc()
    
    def calculate_statistics(self, ir_code):
        """Calculate instruction count and total cost from IR."""
        if not ir_code:
            return {'instruction_count': 0, 'total_cost': 0}
        
        lines = ir_code.split('\n')
        instruction_count = 0
        total_cost = 0
        
        for line in lines:
            line = line.strip()
            if not line or line.startswith('LABEL'):
                continue
            
            instruction_count += 1
            cost = self.estimate_line_cost(line)
            total_cost += cost
        
        return {
            'instruction_count': instruction_count,
            'total_cost': total_cost
        }
    
    def estimate_line_cost(self, line):
        """Estimate the cost of a single IR instruction."""
        line_stripped = line.strip()
        if not line_stripped:
            return 0
        
        # Skip labels
        if line_stripped.startswith('LABEL'):
            return 0
        
        # Alloc instructions have no cost
        if 'alloc' in line_stripped.lower():
            return 0
        
        cost = 0
        
        # Assignment operations (base cost)
        if '=' in line_stripped:
            cost += 1
            
            # Extract the right-hand side
            if '=' in line_stripped:
                parts = line_stripped.split('=', 1)
                if len(parts) == 2:
                    rhs = parts[1].strip()
                    
                    # Check for arithmetic operations in RHS
                    # Pattern matching for operations like "a + b", "10 * 5", etc.
                    
                    # Addition: Look for patterns like "var + var" or "num + num"
                    add_matches = re.findall(r'\w+\s*\+\s*\w+', rhs)
                    cost += len(add_matches) * 2
                    
                    # Subtraction: Look for patterns like "var - var" (not negative numbers)
                    # Negative numbers would be like "-5" at start or after operator
                    sub_matches = re.findall(r'\w+\s*-\s*\w+', rhs)
                    cost += len(sub_matches) * 2
                    
                    # Multiplication: "var * var" or "num * num"
                    # Exclude dereference patterns like "*t5" which are at line start
                    mult_matches = re.findall(r'\w+\s*\*\s*\w+', rhs)
                    cost += len(mult_matches) * 4
                    
                    # Division
                    div_matches = re.findall(r'\w+\s*/\s*\w+', rhs)
                    cost += len(div_matches) * 6
                    
                    # Modulo
                    mod_matches = re.findall(r'\w+\s*%\s*\w+', rhs)
                    cost += len(mod_matches) * 6
                    
                    # Memory operations
                    if '&' in rhs:
                        cost += 0  # Address-of is essentially free
                    if line_stripped.startswith('*') and '=' in line_stripped:
                        cost += 1  # Store operation
                    elif '*' in rhs and not line_stripped.startswith('*'):
                        cost += 1  # Load operation
        
        # Control flow operations
        if 'goto' in line_stripped.lower() or 'jump' in line_stripped.lower():
            cost += 1
        elif line_stripped.startswith('if'):
            cost += 1  # Conditional jump
        
        return max(cost, 1) if cost == 0 and line_stripped else cost
    
    def get_optimization_description(self, optimization_name):
        """Get description of the optimization."""
        descriptions = {
            "Constant Folding": 
                "This optimization evaluates constant expressions at compile-time, "
                "replacing them with their computed values. This eliminates runtime "
                "calculations and reduces instruction count.",
            
            "Dead Code Elimination":
                "This optimization removes code that is never executed (unreachable) "
                "or variables that are assigned but never used. This reduces both "
                "instruction count and memory usage.",
            
            "Common Subexpression Elimination":
                "This optimization identifies and eliminates redundant calculations of "
                "the same expression, storing the result once and reusing it. This "
                "reduces computation overhead.",
            
            "Strength Reduction":
                "This optimization replaces expensive operations (like multiplication "
                "or division) with cheaper operations (like addition) inside loops. "
                "This is particularly effective for induction variables.",
            
            "Loop-Invariant Code Motion":
                "This optimization moves calculations that don't depend on loop variables "
                "outside the loop, so they're computed once instead of every iteration. "
                "This significantly reduces loop overhead."
        }
        
        return descriptions.get(optimization_name, "Optimization applied to improve code efficiency.")
    
    def build_and_compare_runtime(self):
        """Build executables and compare their runtime performance."""
        # Run in a separate thread to avoid blocking the GUI
        thread = threading.Thread(target=self._build_and_compare_thread, daemon=True)
        thread.start()
    
    def _build_and_compare_thread(self):
        """Thread function to build executables and compare runtime."""
        try:
            # Update status
            self.root.after(0, lambda: self.runtime_status.config(
                text="Building executables...", foreground="blue"))
            self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
            self.root.after(0, lambda: self.runtime_text.insert(1.0, "Building executables...\n\nPlease wait..."))
            
            # Check if IR files exist
            if not os.path.exists('original_ic.txt') or not os.path.exists('optimized_ic.txt'):
                self.root.after(0, lambda: self.runtime_status.config(
                    text="Error: IR files not found", foreground="red"))
                self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
                self.root.after(0, lambda: self.runtime_text.insert(
                    1.0, "ERROR: original_ic.txt or optimized_ic.txt not found!\n\nPlease run the analysis first."))
                return
            
            # Build original.exe
            self.root.after(0, lambda: self.runtime_status.config(
                text="Building original.exe...", foreground="blue"))
            original_success = build_executable('original_ic.txt', 'original.exe', 'original.c')
            
            if not original_success:
                self.root.after(0, lambda: self.runtime_status.config(
                    text="Error: Failed to build original.exe", foreground="red"))
                self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
                self.root.after(0, lambda: self.runtime_text.insert(
                    1.0, "ERROR: Failed to build original.exe\n\nPlease check if you have a C compiler installed (gcc/clang)."))
                return
            
            # Build optimized.exe
            self.root.after(0, lambda: self.runtime_status.config(
                text="Building optimized.exe...", foreground="blue"))
            optimized_success = build_executable('optimized_ic.txt', 'optimized.exe', 'optimized.c')
            
            if not optimized_success:
                self.root.after(0, lambda: self.runtime_status.config(
                    text="Error: Failed to build optimized.exe", foreground="red"))
                self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
                self.root.after(0, lambda: self.runtime_text.insert(
                    1.0, "ERROR: Failed to build optimized.exe\n\nPlease check if you have a C compiler installed (gcc/clang)."))
                return
            
            # Update status - running executables
            self.root.after(0, lambda: self.runtime_status.config(
                text="Running executables for comparison...", foreground="blue"))
            self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
            self.root.after(0, lambda: self.runtime_text.insert(
                1.0, "Executables built successfully!\n\nRunning performance tests...\n\nPlease wait..."))
            
            # Run performance comparison
            iterations = 5  # Run each executable 5 times for accuracy
            
            original_time, original_success = run_executable('original.exe', iterations)
            
            if not original_success:
                self.root.after(0, lambda: self.runtime_status.config(
                    text="Error: Failed to run original.exe", foreground="red"))
                self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
                self.root.after(0, lambda: self.runtime_text.insert(
                    1.0, "ERROR: Failed to run original.exe\n\nThe executable may have crashed or timed out."))
                return
            
            optimized_time, optimized_success = run_executable('optimized.exe', iterations)
            
            if not optimized_success:
                self.root.after(0, lambda: self.runtime_status.config(
                    text="Error: Failed to run optimized.exe", foreground="red"))
                self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
                self.root.after(0, lambda: self.runtime_text.insert(
                    1.0, "ERROR: Failed to run optimized.exe\n\n"
                    "The executable timed out (likely infinite loop) or crashed.\n\n"
                    "Possible causes:\n"
                    "  • Infinite loop in the optimized code\n"
                    "  • Missing loop counter increment\n"
                    "  • Incorrect optimization that removed necessary code\n\n"
                    "Please check the generated optimized.c file for issues.\n"
                    "You may need to review the optimization process."))
                return
            
            # Calculate comparison metrics
            if optimized_time < original_time:
                speedup = original_time / optimized_time
                improvement = ((original_time - optimized_time) / original_time) * 100
                result_icon = "✓"
                result_color = "green"
                result_text = "Optimization improved performance!"
            elif optimized_time > original_time:
                slowdown = optimized_time / original_time
                degradation = ((optimized_time - original_time) / original_time) * 100
                result_icon = "⚠"
                result_color = "orange"
                result_text = "Optimized version is slower"
            else:
                result_icon = "≈"
                result_color = "blue"
                result_text = "Execution times are essentially the same"
                speedup = 1.0
                improvement = 0.0
            
            # Format runtime display
            runtime_display = f"""
═══════════════════════════════════════════════════════════════════════════════
                          RUNTIME PERFORMANCE REPORT
═══════════════════════════════════════════════════════════════════════════════

EXECUTION TIME (averaged over {iterations} runs):
───────────────────────────────────────────────────────────────────────────────
  Original Executable:    {original_time * 1000:>10.4f} ms
  Optimized Executable:  {optimized_time * 1000:>10.4f} ms
───────────────────────────────────────────────────────────────────────────────

PERFORMANCE COMPARISON:
───────────────────────────────────────────────────────────────────────────────
  {result_icon} {result_text}
"""
            
            if optimized_time < original_time:
                runtime_display += f"""  Speedup Factor:        {speedup:>10.2f}x faster
  Performance Improvement: {improvement:>10.2f}% faster
"""
            elif optimized_time > original_time:
                runtime_display += f"""  Slowdown Factor:       {slowdown:>10.2f}x slower
  Performance Degradation: {degradation:>10.2f}% slower
"""
            else:
                runtime_display += f"""  Speedup Factor:        {speedup:>10.2f}x
"""
            
            runtime_display += """───────────────────────────────────────────────────────────────────────────────

NOTE: Runtime measurements may vary due to system load and other factors.
      Multiple runs are averaged to provide more accurate results.
═══════════════════════════════════════════════════════════════════════════════
"""
            
            # Update GUI with results
            self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
            self.root.after(0, lambda: self.runtime_text.insert(1.0, runtime_display))
            self.root.after(0, lambda: self.runtime_status.config(
                text="Runtime comparison complete", foreground=result_color))
            
        except Exception as e:
            error_msg = f"Error during runtime comparison: {str(e)}"
            self.root.after(0, lambda: self.runtime_status.config(
                text="Error occurred", foreground="red"))
            self.root.after(0, lambda: self.runtime_text.delete(1.0, tk.END))
            self.root.after(0, lambda: self.runtime_text.insert(1.0, f"ERROR: {error_msg}"))
            import traceback
            traceback.print_exc()


def main():
    root = tk.Tk()
    app = OptimizationGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()

