# DAA Lab 6 - Arrays, Matrices, Convolution, and Reversal Sorting

This repository contains the C programs and complexity analyses for Design and Analysis of Algorithms (DAA) Lab 6. The lab focuses on fundamental 1D array operations, complex 2D matrix computations, an $O(n \log n)$ vector convolution approach, and an in-place sorting algorithm achieved strictly through sub-array reversals.

## Problem Statements

| Question | Problem Statement | Algorithm Used |
| :---: | :--- | :--- |
| **Q1** | 1D array operations: Find max, first/second largest, mean, median, standard deviation, mode, remove duplicates, reverse, and partition. | Linear Scans + `qsort` |
| **Q2** | 2D square matrix operations: Addition, multiplication, zero check, symmetry check, determinant, in-situ transpose, and eigenvalue/eigenvector. | Nested Traversals, Laplace Expansion, Power Iteration |
| **Q3** | Compute the convolution of two vectors of size m and n in $O(n \log n)$ time. | Fast Fourier Transform (FFT) |
| **Q4** | Sort a permutation of integers using only a `reverse(p, i, j)` operation with an overall cost of $O(n \log^2 n)$. | In-Place Merge Sort via Block Rotations |

## Directory Structure

```text
.
├── q1
│   ├── a.out
│   ├── q1.c
│   └── README.md
├── q2
│   ├── a.out
│   ├── q2.c
│   └── README.md
├── q3
│   ├── a.out
│   ├── q3.c
│   └── README.md
└── q4
    ├── a.out
    ├── q4.c
    └── README.md
```

## Compilation and Execution Instructions

To compile and run any of the C programs, open your terminal, navigate to the specific question's directory, and use the `gcc` compiler. 

*Note: Since questions 1, 2, and 3 use functions from `<math.h>` and `<complex.h>`, you must append `-lm` to the compile command to link the math library.*

### Example for Question 1:
```bash
# 1. Navigate to the specific directory
cd q1

# 2. Compile the C program (linking the math library)
gcc q1.c -o a.out -lm

# 3. Run the executable (Linux/macOS)
./a.out

# (If using Windows Command Prompt/PowerShell, run:)
# a.out.exe
```

*Note: You can repeat the exact same steps for `q2`, `q3`, and `q4` by simply changing the directory and the `.c` file name (e.g., `cd ../q3` then `gcc q3.c -o a.out -lm`).*