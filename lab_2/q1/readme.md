# Data Structures Operations Benchmarking

## 📌 Overview

This project implements a benchmarking framework in **C** to measure and compare the empirical execution times of standard dictionary operations across **six fundamental data structures**.

The project compares the practical performance of different data structure implementations against their theoretical **Big-O time and space complexities**. A **Gnuplot** script is also included to visualize the benchmark results and compare the growth of different operations.

---

## 🌳 Data Structures Implemented

The following six data structures are implemented and benchmarked:

1. **Unsorted Array (UA)**
   - Elements are appended dynamically.
   - Deletion is optimized by replacing the deleted element with the last element.

2. **Sorted Array (SA)**
   - Elements are inserted into their correct sorted position.
   - Maintains ascending order at all times.

3. **Singly Linked Unsorted List (SLLU)**
   - Elements are inserted at the head.
   - No ordering is maintained.

4. **Singly Linked Sorted List (SLLS)**
   - Elements are inserted in ascending order.
   - A head pointer is maintained.

5. **Doubly Linked Unsorted List (DLLU)**
   - Elements are inserted at the head.
   - Each node maintains both `prev` and `next` pointers.

6. **Doubly Linked Sorted List (DLLS)**
   - Elements are inserted in ascending order.
   - Both `head` and `tail` pointers are maintained.

---

## ⚙️ Operations Tested

The benchmark evaluates the following seven dictionary operations:

- **Insert**
- **Search**
- **Maximum**
- **Minimum**
- **Predecessor**
- **Successor**
- **Delete**

This results in:

```text
6 Data Structures × 7 Operations = 42 Variants
```

---

# ⏱️ Time Complexity

The following table represents the **worst-case time complexity** for the specific implementations used in this project.

| Operation | Unsorted Array | Sorted Array | SLL Unsorted | SLL Sorted | DLL Unsorted | DLL Sorted |
|:---|:---:|:---:|:---:|:---:|:---:|:---:|
| **Insert** | O(1) | O(N) | O(1) | O(N) | O(1) | O(N) |
| **Search** | O(N) | O(log N) | O(N) | O(N) | O(N) | O(N) |
| **Maximum** | O(N) | O(1) | O(N) | O(N)* | O(N) | O(1)** |
| **Minimum** | O(N) | O(1) | O(N) | O(1) | O(N) | O(1) |
| **Predecessor** | O(N) | O(1) | O(N) | O(N) | O(N) | O(1) |
| **Successor** | O(N) | O(1) | O(N) | O(1) | O(N) | O(1) |
| **Delete** | O(1)*** | O(N) | O(N) | O(N) | O(1) | O(1) |

### Implementation Notes

- `*` **SLLS Maximum — O(N):** Only a `head` pointer is maintained, so finding the maximum requires traversing the entire list.
- `**` **DLLS Maximum — O(1):** A `tail` pointer is explicitly maintained, allowing direct access to the maximum element.
- `***` **Unsorted Array Delete — O(1):** The target element is replaced with the last element, after which the array size is decremented. This avoids shifting elements.

---

# 💾 Space Complexity

All six data structures require **O(N)** space to store `N` elements.

| Data Structure | Space Complexity | Reason |
|:---|:---:|:---|
| **Unsorted Array (UA)** | O(N) | Stores N elements in an array |
| **Sorted Array (SA)** | O(N) | Stores N elements in an array |
| **SLL Unsorted (SLLU)** | O(N) | N nodes with one `next` pointer each |
| **SLL Sorted (SLLS)** | O(N) | N nodes with one `next` pointer each |
| **DLL Unsorted (DLLU)** | O(N) | N nodes with `prev` and `next` pointers |
| **DLL Sorted (DLLS)** | O(N) | N nodes with `prev` and `next` pointers |

Although all structures have **O(N)** asymptotic space complexity, doubly linked lists require more memory per element because every node contains two link pointers.

---

# 📊 Complete Complexity Summary

| Data Structure | Insert | Search | Min | Max | Pred. | Succ. | Delete | Space |
|:---|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| **UA** | O(1) | O(N) | O(N) | O(N) | O(N) | O(N) | O(1) | O(N) |
| **SA** | O(N) | O(log N) | O(1) | O(1) | O(1) | O(1) | O(N) | O(N) |
| **SLLU** | O(1) | O(N) | O(N) | O(N) | O(N) | O(N) | O(N) | O(N) |
| **SLLS** | O(N) | O(N) | O(1) | O(N) | O(N) | O(1) | O(N) | O(N) |
| **DLLU** | O(1) | O(N) | O(N) | O(N) | O(N) | O(N) | O(1) | O(N) |
| **DLLS** | O(N) | O(N) | O(1) | O(1) | O(1) | O(1) | O(1) | O(N) |

> **Note:** These complexities correspond specifically to the implementations used in `q1.c`. Different implementations or additional pointers/metadata may change the complexity of individual operations.

---

# 🧪 Benchmarking Methodology

The program evaluates the data structures using multiple dataset sizes:

```text
N = 1000
N = 2000
N = 4000
N = 8000
N = 10000
```

For each dataset size, the following procedure is performed.

### 1. Data Generation

`N` random integer keys are generated and used as input for the data structures.

### 2. Execution and Measurement

Each operation is executed repeatedly to obtain measurable execution times.

CPU execution time is measured using the C standard library function:

```c
clock()
```

from:

```c
#include <time.h>
```

The benchmark measures the accumulated execution time for the different data structure and operation combinations.

### 3. Data Export

The measured results are written to:

```text
results.csv
```

The CSV file contains the execution times for all **42 data structure-operation variants** across the selected dataset sizes.

---

# 📈 Visualization

The project includes a Gnuplot script:

```text
plot.plt
```

which reads the benchmark data from:

```text
results.csv
```

and generates the final visualization:

```text
q1_plot_results_gnuplot.png
```

The generated image contains a **2 × 4 grid** showing the relationship between:

- **Number of Elements (N)**
- **Execution Time (seconds)**

for the different dictionary operations and data structures.

The plotting script uses `linespoints` to connect valid data points and employs missing-value handling to prevent invalid data points from producing broken or misleading curves.

---

# 📁 Project Structure

```text
.
├── q1.c
├── a.out
├── plot.plt
├── results.csv
├── q1_plot_results_gnuplot.png
└── README.md
```

### File Descriptions

| File | Description |
|:---|:---|
| `q1.c` | C source code containing the data structure implementations and benchmarking logic |
| `a.out` | Compiled executable generated from `q1.c` |
| `plot.plt` | Gnuplot script used to generate the benchmark graphs |
| `results.csv` | Benchmark execution-time data |
| `q1_plot_results_gnuplot.png` | Generated benchmark visualization |
| `README.md` | Project documentation |

> **Note:** `a.out` is a generated executable and does not need to be committed to the repository if the project is intended to be source-code focused. It can be regenerated from `q1.c`.

---

# 🛠️ Prerequisites

The following software is required:

- **GCC** or another C compiler
- **Gnuplot**

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

Compile `q1.c` using GCC:

```bash
gcc q1.c
```

This generates the executable:

```text
a.out
```

For additional compiler warnings, you can use:

```bash
gcc -Wall -Wextra q1.c
```

---

## Step 2 — Run the Benchmark

Execute the compiled program:

```bash
./a.out
```

The program will generate:

```text
results.csv
```

> **Note:** Larger values of `N` may take longer to process. Operations such as sorted-array insertion can be computationally expensive because elements may need to be shifted repeatedly.

---

## Step 3 — Generate the Graph

After `results.csv` has been generated, run the Gnuplot script:

```bash
gnuplot plot.plt
```

This generates:

```text
q1_plot_results_gnuplot.png
```

---

## Step 4 — View the Results

Open:

```text
q1_plot_results_gnuplot.png
```

to view the empirical execution-time comparisons.

---

# 🔬 Theoretical vs Empirical Complexity

A major objective of this project is to compare **theoretical algorithmic complexity** with **actual execution time**.

Big-O notation describes the asymptotic growth of an algorithm as the input size `N` increases. However, real-world execution time is affected by several additional factors, including:

- CPU architecture
- Compiler optimizations
- Cache locality
- Memory hierarchy
- Dynamic memory allocation
- Pointer dereferencing
- Branch prediction
- Operating system scheduling
- Implementation details

For example, two operations may have similar theoretical complexity but significantly different practical execution times because arrays generally provide better **cache locality** than linked lists.

Therefore, empirical benchmarking provides a useful perspective on how theoretical complexity translates into real hardware performance.

---

# 🔍 Key Observations

### Unsorted Array

- Insertion at the end is **O(1)**.
- Search requires **O(N)** time.
- Deletion is optimized to **O(1)** using the swap-with-last technique.
- Minimum and maximum require a complete scan.

### Sorted Array

- Binary search provides **O(log N)** search.
- Minimum and maximum are directly accessible.
- Insertion and deletion can require shifting elements, resulting in **O(N)** complexity.
- Provides efficient ordered operations at the cost of expensive updates.

### Singly Linked Lists

- Unsorted insertion at the head is **O(1)**.
- Searching requires **O(N)** traversal.
- Sorted insertion requires finding the appropriate position.
- Without a tail pointer, finding the maximum in SLLS requires traversing the entire list.

### Doubly Linked Lists

- Nodes contain both `prev` and `next` pointers.
- Deletion can be **O(1)** when the target node is already available.
- DLLS maintains both `head` and `tail`, allowing constant-time access to minimum and maximum.
- Requires more memory per node compared to singly linked lists.

---

# 🎯 Objective

The primary objective of this project is to experimentally analyze the performance of dictionary operations across different data structures and compare:

```text
Theoretical Big-O Complexity
            ↓
       Implementation
            ↓
     Empirical Benchmark
            ↓
     Hardware Performance
```

The experiment demonstrates the practical trade-offs between arrays and linked lists and shows why choosing the right data structure depends not only on theoretical complexity, but also on **memory layout, access patterns, implementation details, and hardware characteristics**.

---

## 👨‍💻 Author

**Priyansu Kumar Mahapatra**  
B.Tech — Computer Science & Engineering  
International Institute of Information Technology Bhubaneswar