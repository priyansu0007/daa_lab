# DAA Lab 6 - Dynamic Programming

This repository contains the C programs and complexity analyses for Design and Analysis of Algorithms (DAA) Lab 6. The lab focuses on core Dynamic Programming (DP) techniques, exploring both top-down (memoization) and bottom-up (tabulation) approaches to efficiently solve complex optimization problems by breaking them down into overlapping subproblems.

## Problem Statements

| Question | Problem Statement | Algorithm Used |
| :---: | :--- | :--- |
| **Q1** | Write a program to find the $n$-th Fibonacci number using Dynamic Programming. | DP (Memoization & Space-Optimized Tabulation) |
| **Q2** | Implement the 0/1 Knapsack problem using Dynamic Programming. Given $n$ items with their weights and profits and a knapsack of capacity $W$, determine the maximum profit that can be obtained. | DP (Bottom-Up 2D Table) |
| **Q3** | Implement the Longest Common Subsequence (LCS) algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the subsequence. | DP (Bottom-Up 2D Table with Backtracking) |
| **Q4** | Implement Matrix Chain Multiplication using Dynamic Programming. Given matrix dimensions, determine the minimum number of scalar multiplications required to multiply the chain and output the optimal parenthesization. | DP (Bottom-Up 2D Table) |

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

To compile and run any of the C programs, open your terminal, navigate to the specific question's directory, and use the standard `gcc` compiler. 

### Example for Question 1:
```bash
# 1. Navigate to the specific directory
cd q1

# 2. Compile the C program
gcc q1.c -o a.out

# 3. Run the executable (Linux/macOS)
./a.out

# (If using Windows Command Prompt/PowerShell, run:)
# a.out.exe
```

*Note: You can repeat the exact same steps for `q2`, `q3`, and `q4` by simply changing the directory and the `.c` file name (e.g., `cd ../q3` then `gcc q3.c -o a.out`).*