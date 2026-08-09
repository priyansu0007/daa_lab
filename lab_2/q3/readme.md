# Merging K Sorted Arrays

## 📌 Overview

This project implements and compares two different approaches for merging **K sorted arrays**, where each array contains **N sorted elements**, into a single sorted array containing `K × N` elements.

The two approaches implemented are:

1. **Sequential Merging**
2. **Divide & Conquer Merging**

The project demonstrates how different algorithmic strategies can significantly affect execution time, particularly as the number of sorted arrays `K` increases.

---

# 🧠 Problem Statement

Given `K` individually sorted arrays, each containing `N` elements, the objective is to merge them into one sorted array containing:

```text
K × N elements
```

For example:

```text
Array 1: 1  5  9
Array 2: 2  6  10
Array 3: 3  7  11
Array 4: 4  8  12
```

The required output is:

```text
1 2 3 4 5 6 7 8 9 10 11 12
```

---

# 🔀 Methods Implemented

## 1. Sequential Merging

### Approach

Sequential merging treats the first array as an initial result and then merges each remaining array into the accumulated result one at a time.

The process can be visualized as:

```text
A₁ + A₂
   ↓
Merged Result
   +
A₃
   ↓
Merged Result
   +
A₄
   ↓
...
   ↓
Final Result
```

For `K` arrays, the algorithm performs `K - 1` merge operations.

### Intuition

This approach is simple and straightforward, but it repeatedly processes elements that were already merged.

For example:

```text
Merge A₁ + A₂       → 2N elements processed
Merge Result + A₃   → 3N elements processed
Merge Result + A₄   → 4N elements processed
...
```

As `K` increases, the amount of repeated work becomes significant.

---

# 🌳 2. Divide & Conquer Merging

### Approach

The divide-and-conquer approach recursively divides the collection of `K` sorted arrays into two groups.

The groups are then recursively merged until only individual arrays remain. During the return phase, pairs of sorted arrays are merged together.

For example, with 4 arrays:

```text
             [A₁ A₂ A₃ A₄]
                /       \
             [A₁ A₂]   [A₃ A₄]
              /  \       /  \
            A₁   A₂     A₃   A₄
              \  /       \  /
             Merge      Merge
                \       /
                 \     /
                Final Merge
```

### Intuition

Instead of repeatedly merging into one growing array, the algorithm merges arrays in a **balanced tree-like structure**.

Each element participates in approximately:

```text
log₂(K)
```

merge levels instead of potentially being processed `K` times.

This significantly reduces redundant work for large values of `K`.

---

# ⏱️ Time Complexity

| Method | Worst-Case Time Complexity | Merge Levels |
|:---|:---:|:---:|
| **Sequential Merging** | O(N × K²) | O(K) |
| **Divide & Conquer** | O(N × K log₂ K) | O(log₂ K) |

Here, `N` represents the number of elements in each array and `K` represents the number of arrays.

---

## Sequential Merging

The first merge combines two arrays:

```text
O(2N)
```

The next merge combines `2N` elements with another `N` elements:

```text
O(3N)
```

The process continues until the final merge:

```text
O(KN)
```

Therefore, the total work is approximately:

```text
N(2 + 3 + 4 + ... + K)
```

Since:

```text
2 + 3 + ... + K = O(K²)
```

the overall time complexity is:

```text
O(N × K²)
```

---

## Divide & Conquer

The arrays are merged in a balanced tree.

The depth of the tree is:

```text
log₂(K)
```

At every level, all `K × N` elements are processed once during merging.

Therefore:

```text
O(KN) × O(log₂ K)
```

giving:

```text
O(N × K log₂ K)
```

This is significantly better than sequential merging when `K` becomes large.

---

# 💾 Space Complexity

Both approaches require **O(N × K)** auxiliary space.

| Method | Result Array | Temporary Memory | Recursion Stack | Overall Space |
|:---|:---:|:---:|:---:|:---:|
| **Sequential Merging** | O(NK) | O(NK) | O(1) | **O(NK)** |
| **Divide & Conquer** | O(NK) | O(NK) | O(log K) | **O(NK)** |

### Sequential Merging

The sequential implementation requires:

- A result array capable of storing `K × N` elements.
- A temporary array of similar size during merging.

Therefore:

```text
O(NK) + O(NK) = O(NK)
```

The constant factor may be larger because both arrays can coexist in memory.

### Divide & Conquer

The divide-and-conquer implementation dynamically allocates intermediate merged arrays.

At the highest level, the total number of elements involved is:

```text
K × N
```

The recursion stack requires:

```text
O(log₂ K)
```

space.

Since:

```text
O(NK) > O(log K)
```

the overall auxiliary space complexity remains:

```text
O(NK)
```

---

# 📊 Complexity Summary

| Property | Sequential Merging | Divide & Conquer |
|:---|:---:|:---:|
| **Approach** | Iterative | Recursive |
| **Merge strategy** | One array at a time | Pairwise merging |
| **Number of merge levels** | O(K) | O(log₂ K) |
| **Worst-case time** | O(NK²) | O(NK log K) |
| **Auxiliary space** | O(NK) | O(NK) |
| **Recursion stack** | O(1) | O(log K) |
| **Output size** | NK | NK |

> **Key takeaway:** Both methods require the same asymptotic space, but Divide & Conquer provides a significantly better time complexity by avoiding repeated processing of previously merged elements.

---

# 🧪 Test Case

The program uses a simple test case with:

```text
K = 4
N = 3
```

The input arrays are:

```text
Array 1: 1 5 9
Array 2: 2 6 10
Array 3: 3 7 11
Array 4: 4 8 12
```

Both algorithms should produce the same sorted output:

```text
1 2 3 4 5 6 7 8 9 10 11 12
```

---

# ✅ Expected Output

When the program is executed, the output should be similar to:

```text
Input Data (4 arrays of 3 elements):
Array 1: 1 5 9
Array 2: 2 6 10
Array 3: 3 7 11
Array 4: 4 8 12

Method 1 Result: 1 2 3 4 5 6 7 8 9 10 11 12
Method 2 Result: 1 2 3 4 5 6 7 8 9 10 11 12
```

The identical outputs confirm that both implementations correctly merge the sorted arrays.

---

# 📁 Project Structure

```text
.
├── q3.c
├── a.out
└── README.md
```

### File Descriptions

| File | Description |
|:---|:---|
| `q3.c` | C implementation of Sequential and Divide & Conquer K-way array merging |
| `a.out` | Compiled executable generated from `q3.c` |
| `README.md` | Project documentation |

> **Note:** `a.out` is a generated executable and can be recreated by compiling `q3.c`.

---

# 🛠️ Prerequisites

The project requires:

- **GCC** or any standard C compiler.

### Check GCC

```bash
gcc --version
```

---

# 🚀 How to Run

## Step 1 — Compile

Compile the source code using GCC:

```bash
gcc q3.c
```

This generates the executable:

```text
a.out
```

For additional compiler warnings:

```bash
gcc -Wall -Wextra q3.c
```

---

## Step 2 — Execute

Run the compiled program:

```bash
./a.out
```

The program will:

1. Initialize the test arrays.
2. Display the input data.
3. Merge the arrays using **Sequential Merging**.
4. Merge the arrays using **Divide & Conquer**.
5. Display the results of both methods.

---

# 🔬 Comparison of the Two Approaches

The key difference between the two methods is how they organize the merge operations.

### Sequential

```text
A₁ + A₂ → R₁
R₁ + A₃ → R₂
R₂ + A₄ → R₃
...
```

This causes previously processed elements to be repeatedly copied and compared.

### Divide & Conquer

```text
A₁ + A₂ → R₁
A₃ + A₄ → R₂

R₁ + R₂ → Final
```

The work is distributed across multiple levels, allowing each element to participate in approximately `log₂ K` merge operations.

---

# 🎯 Objective

The objective of this experiment is to:

- Implement **Sequential Merging** of K sorted arrays.
- Implement **Divide & Conquer Merging** of K sorted arrays.
- Analyze the time complexity of both approaches.
- Analyze their space requirements.
- Verify that both approaches produce the same sorted result.
- Understand how divide-and-conquer techniques can reduce redundant computation.

The experiment demonstrates an important algorithmic principle:

> **A better organization of the same basic operations can dramatically improve performance without changing the final result.**

---

## 👨‍💻 Author

**Priyansu Kumar Mahapatra**  
B.Tech — Computer Science & Engineering  
International Institute of Information Technology Bhubaneswar