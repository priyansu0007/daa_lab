# Merge Sort Benchmarking: 2-Way vs. 3-Way

## 📌 Overview

This project provides a **C-based benchmarking framework** to compare the empirical performance of **standard 2-Way Merge Sort** and a modified **3-Way Merge Sort**.

The program sorts arrays containing randomly generated integers across multiple input sizes and measures the **CPU execution time** of both algorithms. The collected results are stored in `merge.dat`, which can then be visualized using the provided Gnuplot script.

The primary objective is to compare the **theoretical time and space complexities** of both approaches with their **actual execution performance**.

---

# 🧠 Algorithms Implemented

## 1. 2-Way Merge Sort

The standard Merge Sort algorithm follows the classic **divide-and-conquer** approach.

### Divide

The input array is divided into two approximately equal halves.

```text
        [ N elements ]
          /       \
       N/2         N/2
```

### Conquer

Each half is recursively sorted until the base case is reached.

### Combine

The two sorted halves are merged by repeatedly selecting the smaller element from the front of the two subarrays.

---

## 2. 3-Way Merge Sort

The modified 3-Way Merge Sort divides the array into **three approximately equal segments**.

### Divide

```text
          [ N elements ]
          /     |     \
       N/3     N/3     N/3
```

### Conquer

All three segments are recursively sorted.

The recursion continues until the subarray reaches the base case. For very small arrays, simple swaps are used instead of further recursive division.

### Combine

The three sorted segments are merged together.

The algorithm compares the front elements of the three subarrays and selects the smallest element at each step. Once one subarray is exhausted, the remaining arrays are merged using 2-way merging.

### Intuition

3-Way Merge Sort produces a **shallower recursion tree** because the array is divided by 3 instead of 2.

However, each merge operation is more complicated because the algorithm may need to compare **three elements instead of two**.

Therefore, fewer recursion levels do not necessarily mean better practical performance.

---

# ⏱️ Time Complexity

| Algorithm | Best Case | Average Case | Worst Case | Recursion Depth |
|:---|:---:|:---:|:---:|:---:|
| **2-Way Merge Sort** | O(N log N) | O(N log N) | O(N log N) | O(log₂ N) |
| **3-Way Merge Sort** | O(N log N) | O(N log N) | O(N log N) | O(log₃ N) |

### 2-Way Merge Sort

The array is divided into two parts at every recursion level.

The number of recursion levels is approximately:

```text
log₂(N)
```

At each level, merging all elements takes **O(N)** time.

Therefore:

```text
O(N) × O(log₂ N)
= O(N log₂ N)
```

---

### 3-Way Merge Sort

The array is divided into three parts at every recursion level.

The recursion depth is approximately:

```text
log₃(N)
```

Each level still processes all `N` elements during merging:

```text
O(N) × O(log₃ N)
= O(N log₃ N)
```

Since logarithms differ only by a constant factor:

```text
log₃(N) = log₂(N) / log₂(3)
```

both algorithms have the same asymptotic complexity:

```text
O(N log N)
```

The difference is primarily in their constant factors and practical implementation overhead.

---

# 💾 Space Complexity

Both algorithms require **O(N)** auxiliary space.

| Algorithm | Auxiliary Space | Recursion Stack | Overall Space |
|:---|:---:|:---:|:---:|
| **2-Way Merge Sort** | O(N) | O(log₂ N) | **O(N)** |
| **3-Way Merge Sort** | O(N) | O(log₃ N) | **O(N)** |

### Auxiliary Memory

The merge operation uses temporary arrays to store elements while combining sorted subarrays.

For 2-Way Merge Sort, the temporary arrays contain a total of **O(N)** elements during the top-level merge.

For 3-Way Merge Sort, the temporary arrays for the three subarrays also contain a total of **O(N)** elements.

Therefore, both algorithms require:

```text
O(N)
```

auxiliary memory.

### Recursion Stack

The recursion stack requires:

- **2-Way:** O(log₂ N)
- **3-Way:** O(log₃ N)

Since:

```text
O(N) > O(log N)
```

the overall space complexity for both algorithms remains:

```text
O(N)
```

---

# 📊 Complexity Summary

| Property | 2-Way Merge Sort | 3-Way Merge Sort |
|:---|:---:|:---:|
| **Divide factor** | 2 | 3 |
| **Recursive calls** | 2 | 3 |
| **Recursion depth** | O(log₂ N) | O(log₃ N) |
| **Best-case time** | O(N log N) | O(N log N) |
| **Average-case time** | O(N log N) | O(N log N) |
| **Worst-case time** | O(N log N) | O(N log N) |
| **Auxiliary space** | O(N) | O(N) |
| **Overall space** | O(N) | O(N) |
| **Merge work per level** | O(N) | O(N) |

> **Note:** Although the 3-Way version has fewer recursion levels, its merge operation has a higher constant overhead due to comparisons among three subarrays. Therefore, recursion depth alone does not determine which implementation will be faster in practice.

---

# 🧪 Benchmarking Methodology

The benchmark evaluates both sorting algorithms using arrays of different sizes.

The input sizes range from:

```text
N = 10,000
N = 20,000
N = 30,000
...
N = 200,000
```

For each input size:

1. A random integer array is generated.
2. The array is sorted using **2-Way Merge Sort**.
3. The CPU execution time is measured.
4. The same input is benchmarked using **3-Way Merge Sort**.
5. The measured results are written to `merge.dat`.

This allows both algorithms to be compared under the same input-size conditions.

---

# ⏱️ Execution Time Measurement

The program uses the C standard library's `clock()` function to measure CPU execution time.

```c
#include <time.h>
```

The measured execution times represent the CPU time consumed by the sorting operations.

The benchmark focuses on empirical performance in addition to theoretical complexity.

---

# 📈 Visualization

The project includes a Gnuplot script:

```text
plot.plt
```

The script reads the benchmark data from:

```text
merge.dat
```

and generates a graph comparing:

- **2-Way Merge Sort**
- **3-Way Merge Sort**

The graph uses:

```text
X-axis → Number of Elements (N)
Y-axis → Execution Time
```

This provides a visual representation of how the running time of both algorithms grows as the input size increases.

---

# 📁 Project Structure

```text
.
├── q2.c
├── a.out
├── merge.dat
├── plot.plt
├── README.md
└── <generated graph>
```

### File Descriptions

| File | Description |
|:---|:---|
| `q2.c` | C implementation of 2-Way and 3-Way Merge Sort along with benchmarking code |
| `a.out` | Compiled executable generated from `q2.c` |
| `merge.dat` | Benchmark data containing execution times |
| `plot.plt` | Gnuplot script used to generate the performance graph |
| `README.md` | Project documentation |
| Generated graph | Visualization comparing both sorting algorithms |

> **Note:** `a.out` and `merge.dat` are generated files and can be recreated by compiling and running the program.

---

# 🛠️ Prerequisites

The following software is required:

- **GCC** — GNU C Compiler
- **Gnuplot** — For generating the performance graph

### Check GCC

```bash
gcc --version
```

### Check Gnuplot

```bash
gnuplot --version
```

---

# 🚀 How to Run

## Step 1 — Compile the Program

Compile `q2.c` using GCC:

```bash
gcc q2.c
```

This generates the executable:

```text
a.out
```

For additional compiler warnings:

```bash
gcc -Wall -Wextra q2.c
```

---

## Step 2 — Run the Benchmark

Execute the compiled program:

```bash
./a.out
```

The program benchmarks both algorithms for input sizes ranging from **10,000 to 200,000**, in increments of **10,000**.

The benchmark results will be stored in:

```text
merge.dat
```

> **Note:** The benchmark may take some time for larger input sizes because both sorting algorithms perform recursive sorting and merging operations.

---

## Step 3 — Generate the Graph

Once `merge.dat` has been generated, run:

```bash
gnuplot plot.plt
```

The Gnuplot script will generate the performance visualization.

---

## Step 4 — View the Results

Open the generated graph to visually compare the execution times of:

```text
2-Way Merge Sort
        vs.
3-Way Merge Sort
```

---

# 🔬 Theoretical vs. Empirical Performance

The main purpose of this benchmark is to understand the difference between **asymptotic complexity** and **real-world performance**.

Both algorithms have an asymptotic time complexity of:

```text
O(N log N)
```

However, their actual execution times can differ because of:

- Number of comparisons
- Function-call overhead
- Memory allocation
- Cache locality
- Memory access patterns
- Compiler optimizations
- CPU architecture
- Branch prediction
- Implementation details

The 3-Way algorithm has a shallower recursion tree, but its merge operation involves more complicated comparisons.

Therefore, the benchmark helps determine whether the theoretical advantage of fewer recursion levels translates into an actual performance advantage.

---

# 🎯 Objective

The objective of this experiment is to:

- Implement **2-Way Merge Sort**.
- Implement **3-Way Merge Sort**.
- Analyze their time and space complexities.
- Benchmark both algorithms for increasing input sizes.
- Record their empirical CPU execution times.
- Visualize and compare their performance using Gnuplot.
- Understand the relationship between **theoretical complexity and practical performance**.

Ultimately, the experiment demonstrates that algorithms with the same asymptotic complexity can still exhibit different real-world performance because of implementation details and hardware-level characteristics.

---

## 👨‍💻 Author

**Priyansu Kumar Mahapatra**  
B.Tech — Computer Science & Engineering  
International Institute of Information Technology Bhubaneswar