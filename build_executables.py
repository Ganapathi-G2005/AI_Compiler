#!/usr/bin/env python3
"""
Build Script to Create Executables from IR
Compiles original_ic.txt and optimized_ic.txt to original.exe and optimized.exe
"""

import os
import sys
import subprocess
import platform
import time
from ir_to_c import translate_ir_to_c


def build_executable(ir_file: str, exe_name: str, c_file_name: str = None) -> bool:
    """
    Build an executable from an IR file.
    
    Args:
        ir_file: Path to input IR file
        exe_name: Name of output executable
        c_file_name: Optional name for intermediate C file (defaults to exe_name.c)
        
    Returns:
        True if successful, False otherwise
    """
    if c_file_name is None:
        c_file_name = exe_name.replace('.exe', '.c')
    
    # Step 0: Try to terminate any running instance of the executable
    _terminate_executable(exe_name)
    
    print(f"Building {exe_name} from {ir_file}...")
    
    # Step 1: Translate IR to C
    print(f"  [1/2] Translating IR to C: {c_file_name}")
    if not translate_ir_to_c(ir_file, c_file_name):
        print(f"  ERROR: Failed to translate {ir_file} to C", file=sys.stderr)
        return False
    
    # Step 2: Compile C to executable
    print(f"  [2/2] Compiling C to executable: {exe_name}")
    try:
        # Use gcc or clang (on Windows, might need to use gcc from MinGW or similar)
        # Check which compiler is available
        compiler = None
        for cc in ['gcc', 'clang', 'cl']:
            try:
                result = subprocess.run([cc, '--version'], capture_output=True, timeout=5)
                if result.returncode == 0 or cc == 'cl':
                    compiler = cc
                    break
            except (FileNotFoundError, subprocess.TimeoutExpired):
                continue
        
        if compiler is None:
            print("  ERROR: No C compiler found (gcc, clang, or cl)", file=sys.stderr)
            print("  Please install a C compiler (MinGW-w64 for Windows, or GCC/Clang)", file=sys.stderr)
            return False
        
        # Compile command
        if compiler == 'cl':
            # MSVC on Windows
            compile_cmd = [compiler, c_file_name, f'/Fe:{exe_name}', '/link', '/OUT:' + exe_name]
        else:
            # GCC or Clang
            compile_cmd = [compiler, c_file_name, '-o', exe_name, '-O2']
        
        result = subprocess.run(compile_cmd, capture_output=True, text=True)
        
        if result.returncode != 0:
            print(f"  ERROR: Compilation failed", file=sys.stderr)
            print(f"  Compiler output: {result.stderr}", file=sys.stderr)
            return False
        
        print(f"  SUCCESS: Created {exe_name}")
        return True
        
    except Exception as e:
        print(f"  ERROR: Exception during compilation: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc(file=sys.stderr)
        return False


def _terminate_executable(exe_name: str):
    """
    Try to terminate any running instance of the executable to avoid permission errors.
    
    Args:
        exe_name: Name of the executable file
    """
    if not os.path.exists(exe_name):
        return  # File doesn't exist, nothing to terminate
    
    try:
        if platform.system() == "Windows":
            # On Windows, use taskkill to terminate the process
            process_name = os.path.basename(exe_name)
            # Remove .exe extension if present for process name matching
            proc_name = process_name.replace('.exe', '')
            
            # Try to kill any running instance
            subprocess.run(
                ['taskkill', '/F', '/IM', process_name],
                capture_output=True,
                timeout=2
            )
            # Also try without .exe extension
            if proc_name != process_name:
                subprocess.run(
                    ['taskkill', '/F', '/IM', proc_name],
                    capture_output=True,
                    timeout=2
                )
            time.sleep(0.5)  # Give it a moment to release the file
        else:
            # On Unix-like systems, use pkill
            process_name = os.path.basename(exe_name)
            subprocess.run(
                ['pkill', '-f', process_name],
                capture_output=True,
                timeout=2
            )
            time.sleep(0.5)
    except (FileNotFoundError, subprocess.TimeoutExpired, Exception):
        # Ignore errors - file might not be locked, or process might not be running
        pass


def main():
    """Main function to build both executables."""
    print("=" * 60)
    print("Building Executables from Intermediate Code")
    print("=" * 60)
    print()
    
    # Build original.exe
    original_success = build_executable('original_ic.txt', 'original.exe', 'original.c')
    print()
    
    # Build optimized.exe
    optimized_success = build_executable('optimized_ic.txt', 'optimized.exe', 'optimized.c')
    print()
    
    # Summary
    print("=" * 60)
    if original_success and optimized_success:
        print("SUCCESS: Both executables built successfully!")
        print("  - original.exe  (from original_ic.txt)")
        print("  - optimized.exe    (from optimized_ic.txt)")
        print()
        print("You can now run both executables to compare performance:")
        print("  original.exe")
        print("  optimized.exe")
    else:
        print("BUILD FAILED!")
        if not original_success:
            print("  - Failed to build original.exe")
        if not optimized_success:
            print("  - Failed to build optimized.exe")
        sys.exit(1)
    
    print("=" * 60)


if __name__ == "__main__":
    main()

