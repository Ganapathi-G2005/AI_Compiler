#!/usr/bin/env python3
"""
Runtime Comparison Script
Compares the execution time of original.exe and optimized.exe
"""

import time
import subprocess
import sys
import os


def run_executable(exe_name: str, iterations: int = 1) -> tuple[float, bool]:
    """
    Run an executable and measure its execution time.
    
    Args:
        exe_name: Name of the executable to run
        iterations: Number of times to run (for averaging)
        
    Returns:
        Tuple of (average_time_seconds, success)
    """
    if not os.path.exists(exe_name):
        print(f"ERROR: {exe_name} not found!", file=sys.stderr)
        return (0.0, False)
    
    times = []
    timeout_seconds = 5  # Reduced timeout - if code takes longer, it's likely infinite loop
    for i in range(iterations):
        start_time = time.perf_counter()
        try:
            result = subprocess.run(
                [exe_name],
                capture_output=True,
                timeout=timeout_seconds,
                text=True
            )
            end_time = time.perf_counter()
            elapsed = end_time - start_time
            times.append(elapsed)
            
            # Check return code - non-zero might indicate issues
            if result.returncode != 0:
                print(f"  WARNING: {exe_name} returned non-zero exit code {result.returncode} on iteration {i+1}", file=sys.stderr)
                if result.stderr:
                    print(f"  stderr: {result.stderr[:200]}", file=sys.stderr)
        except subprocess.TimeoutExpired:
            print(f"  WARNING: {exe_name} timed out after {timeout_seconds}s on iteration {i+1} (likely infinite loop)", file=sys.stderr)
            # Continue to next iteration instead of failing immediately
            # This allows other iterations to complete if this was a one-off issue
            continue
        except Exception as e:
            print(f"  ERROR running {exe_name}: {e}", file=sys.stderr)
            return (0.0, False)
    
    if not times:
        # All iterations timed out
        return (0.0, False)
    
    avg_time = sum(times) / len(times)
    return (avg_time, True)


def main():
    """Main comparison function."""
    print("=" * 60)
    print("Runtime Comparison: original.exe vs optimized.exe")
    print("=" * 60)
    print()
    
    iterations = 5  # Run each executable 5 times and average
    
    print(f"Running each executable {iterations} times for accuracy...")
    print()
    
    # Run original.exe
    print("Running original.exe...")
    original_time, original_success = run_executable('original.exe', iterations)
    
    if not original_success:
        print("Failed to run original.exe", file=sys.stderr)
        sys.exit(1)
    
    print(f"  Average execution time: {original_time * 1000:.4f} ms")
    print()
    
    # Run optimized.exe
    print("Running optimized.exe...")
    optimized_time, optimized_success = run_executable('optimized.exe', iterations)
    
    if not optimized_success:
        print("Failed to run optimized.exe", file=sys.stderr)
        print("This may indicate an infinite loop or crash in the optimized code.", file=sys.stderr)
        print("Please check the generated optimized.c file for issues.", file=sys.stderr)
        sys.exit(1)
    
    print(f"  Average execution time: {optimized_time * 1000:.4f} ms")
    print()
    
    # Compare results
    print("=" * 60)
    print("RESULTS:")
    print("=" * 60)
    print(f"Original:   {original_time * 1000:10.4f} ms")
    print(f"Optimized:  {optimized_time * 1000:10.4f} ms")
    print()
    
    if optimized_time < original_time:
        speedup = original_time / optimized_time
        improvement = ((original_time - optimized_time) / original_time) * 100
        print(f"✓ Optimization improved performance!")
        print(f"  Speedup: {speedup:.2f}x")
        print(f"  Improvement: {improvement:.2f}% faster")
    elif optimized_time > original_time:
        slowdown = optimized_time / original_time
        degradation = ((optimized_time - original_time) / original_time) * 100
        print(f"⚠ Optimized version is slower (this can happen with minimal code)")
        print(f"  Slowdown: {slowdown:.2f}x")
        print(f"  Degradation: {degradation:.2f}% slower")
    else:
        print("≈ Execution times are essentially the same")
    
    print("=" * 60)


if __name__ == "__main__":
    main()

