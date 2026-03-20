# Search Algorithms Performance Measurement

This project implements four search algorithms (iterative/recursive sequential search and iterative/recursive binary search) and measures their worst case running times for various input sizes.

## File Structure

```
.
├── benchmark_results.csv //Analyze the results more conveniently
├── search.h          // Header file with function declarations
├── search.c          // Implementation of the four search functions
├── test_search.c     // Test program to verify correctness
├── measure_search.c  // Performance measurement program
└── plot_n_runtime.py // Run this file to check N-run_time plot
```

notes: 
Here we provide plot_n_runtime.py and benchmark_results.csv to help you to analyse the performance of the four search algorithm conveniently.
If you open this file in IDE like devcpp that doesn't support python, csv ,please ignore plot_n_runtime.py and benchmark_results.csv 

## Compilation Instructions

### 1. Compile the Test Program

To verify that all search functions work correctly, compile `test_search.c` together with `search.c`:

```bash
gcc -o test_search test_search.c search.c -std=c99
```

notes:
- `-o test_search`: names the executable `test_search` (add `.exe` on Windows).
- `-std=c99`: enables C99 standard (optional but recommended if your code uses C99 features like `//` comments).

Run the test:

```bash
./test_search        # Linux/macOS
test_search.exe      # Windows
```

All test cases should print `PASS`. If any test fails, check your implementation.

### 2. Compile the Performance Measurement Program

Once the functions are verified, compile the measurement program:

```bash
gcc -o measure_search measure_search.c search.c -std=c99 -O2
```

- `-O2`: enables compiler optimizations for more realistic performance results.

Run the measurement:

```bash
./measure_search
```

The program will output a table of average running times for each N and algorithm.

## Common Compilation Errors

- **`undefined reference to 'function_name'`**  
  Make sure the function is implemented in `search.c` and the declaration in `search.h` matches exactly. Also ensure `search.c` includes `search.h`.

- **`fatal error: search.h: No such file or directory`**  
  Verify that `search.h` is in the same directory as the source files. If not, use the `-I` flag to specify the include path:
  ```bash
  gcc -o test_search test_search.c search.c -I/path/to/headers
  ```

- **`implicit declaration of function`**  
  Check that `#include "search.h"` is present at the top of each source file that calls the search functions.

## Notes

- The recursive sequential search may cause a stack overflow for large `N` (e.g., 10000) when the key is not found, due to deep recursion. This is a known limitation and is discussed in the report.
- For performance measurement, ensure your system is not under heavy load to obtain stable timings.
- The provided `-std=c99` flag is optional; if your compiler defaults to a later standard (e.g., C11, C17), you can omit it.

---

For a detailed explanation of the algorithms, test cases, complexity analysis, and measurement results, please refer to the project report.