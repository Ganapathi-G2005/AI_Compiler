# Building Executables from Intermediate Code

This guide explains how to create executable files from your intermediate code (IR) files for performance comparison.

## Quick Start

To build both `original.exe` and `optimized.exe` from your IR files:

```bash
python build_executables.py
```

This will:
1. Translate `original_ic.txt` to `original.c` and compile it to `original.exe`
2. Translate `optimized_ic.txt` to `optimized.c` and compile it to `optimized.exe`

## Comparing Runtime Performance

To compare the execution time of both executables:

```bash
python compare_runtime.py
```

This script runs each executable multiple times and calculates:
- Average execution time
- Speedup factor
- Performance improvement percentage

## Files Created

- `original.exe` - Executable compiled from `original_ic.txt` (before optimization)
- `optimized.exe` - Executable compiled from `optimized_ic.txt` (after optimization)
- `original.c` - C code generated from original IR
- `optimized.c` - C code generated from optimized IR

## Manual Usage

### Translate IR to C

```bash
python ir_to_c.py <input_ir_file> <output_c_file>
```

Example:
```bash
python ir_to_c.py original_ic.txt original.c
```

### Compile C to Executable

Using GCC:
```bash
gcc original.c -o original.exe -O2
```

Using Clang:
```bash
clang original.c -o original.exe -O2
```

## Requirements

- Python 3.x
- A C compiler (GCC, Clang, or MSVC)
  - Windows: Install MinGW-w64 or use MSVC from Visual Studio
  - Linux/Mac: Usually comes with GCC or Clang

## Troubleshooting

### Compiler Not Found

If you see "No C compiler found", install one:
- **Windows**: Install MinGW-w64 from [mingw-w64.org](https://www.mingw-w64.org/)
- **Linux**: Install via package manager: `sudo apt-get install gcc` (Ubuntu/Debian)
- **Mac**: Install Xcode Command Line Tools: `xcode-select --install`

### Compilation Errors

If you get compilation errors, check:
1. The IR file format is correct
2. All variables are properly declared
3. Array operations are valid
4. Pointer operations are correct

## Notes

- The IR-to-C translator handles:
  - Variable declarations (including arrays)
  - Pointer operations
  - Arithmetic expressions
  - Control flow (if-else, loops via goto labels)
  - Array indexing via pointer arithmetic

- The generated C code uses `goto` statements to preserve the control flow structure from the IR

- Both executables are compiled with optimization level `-O2` for fair comparison

