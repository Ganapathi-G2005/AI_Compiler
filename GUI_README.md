# Optimization GUI User Guide

## Overview
The Optimization GUI provides a visual interface to analyze how your C code is optimized by the ML model. It displays:

- **Original Intermediate Code** - The IR generated from your C code
- **Optimized Intermediate Code** - The IR after applying the predicted optimization
- **Statistics** - Instruction counts and cost analysis
- **Optimization Information** - Details about the applied optimization

## Running the GUI

```bash
python optimization_gui.py
```

## Using the GUI

1. **Select a C File**
   - Click "Browse" to select your C source file
   - Or type the file path directly in the text field

2. **Analyze**
   - Click the "Analyze" button
   - The GUI will:
     - Run the optimization predictor
     - Generate IR from your C code
     - Apply the predicted optimization
     - Display results side-by-side

3. **View Results**
   - **Left Panel**: Original IR code
   - **Right Panel**: Optimized IR code
   - **Statistics Panel**: 
     - Instruction counts (original vs optimized)
     - Total execution cost (in cycles)
     - Improvement metrics
   - **Info Panel**: Description of the applied optimization

## Cost Model

The cost estimation uses the following instruction costs:
- **Add/Subtract**: 2 cycles
- **Multiply**: 4 cycles
- **Divide/Modulo**: 6 cycles
- **Assignment**: 1 cycle
- **Load/Store**: 1 cycle
- **Jump/Goto**: 1 cycle
- **Conditional (if)**: 1 cycle
- **Alloc**: 0 cycles (compile-time)

## Features

- **Side-by-side comparison** of original and optimized code
- **Scrollable text areas** for viewing large IR files
- **Automatic statistics calculation** including:
  - Instruction count reduction
  - Cost savings
  - Percentage improvement
- **Optimization descriptions** explaining what each optimization does

## Requirements

- Python 3.x
- tkinter (usually included with Python)
- All project dependencies (numpy, scikit-learn, etc.)

