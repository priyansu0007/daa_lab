# Lab 8: Dynamic Programming and Algorithmic Implementations

## 1. Lab Number
**Lab 8**

## 2. Problem Statements

This repository contains C implementations for the following algorithmic problems:

*   **Question 1: Minimum Coin Change**
    Given an array of distinct coin denominations and a target amount, find the minimum number of coins required to make up the target amount.
*   **Question 2: Coin Change - Total Ways**
    Given an array of distinct coin denominations and a target amount, find the total number of distinct combinations of coins that sum up to the target amount.
*   **Question 3: Longest Common Subsequence (LCS)**
    Given two strings, compute the length of their longest common subsequence and reconstruct the actual subsequence string.
*   **Question 4: Longest Increasing Subsequence (LIS)**
    Given an integer array, find the length of the longest strictly increasing subsequence.
*   **Question 5: Maximum Sum Increasing Subsequence**
    Given an array of positive integers, find the maximum possible sum of a strictly increasing subsequence.
*   **Question 6: Edit Distance with Traceback**
    Given two strings, compute the minimum number of operations (insertions, deletions, or substitutions) required to transform the first string into the second, and print the exact sequence of operations.
*   **Question 7: Rod Cutting with Reconstruction**
    Given a rod of length $n$ and an array of prices for pieces of various lengths, determine the maximum revenue obtainable and the exact lengths of the optimal pieces.
*   **Question 8: Optimal Binary Search Trees (OBST)**
    Given a set of distinct sorted keys with successful search probabilities and dummy keys with unsuccessful search probabilities, find the minimum expected search cost of a binary search tree.
*   **Question 9: Collatz Conjecture Analysis**
    Analyze the trajectory of a user-provided starting value $n \ge 1$ and across an interval $[a, b]$ for the Collatz Conjecture (3n+1 problem) using dynamic memory allocation and overflow handling.

## 3. Directory Structure

```text
.
├── q1
│   ├── a.out
│   ├── q1.c
│   └── readme.md
├── q2
│   ├── a.out
│   ├── q2.c
│   └── readme.md
├── q3
│   ├── a.out
│   ├── q3.c
│   └── readme.md
├── q4
│   ├── a.out
│   ├── q4.c
│   └── readme.md
├── q5
│   ├── a.out
│   ├── q5.c
│   └── readme.md
├── q6
│   ├── a.out
│   ├── q6.c
│   └── readme.md
├── q7
│   ├── a.out
│   ├── q7.c
│   └── readme.md
├── q8
│   ├── a.out
│   ├── q8.c
│   └── readme.md
└── q9
    ├── a.out
    ├── q9.c
    └── readme.md
```

## 4. Compile Instructions

Each question is contained within its own dedicated directory. To compile and run any of the C programs, navigate to its directory and use the GNU C Compiler (`gcc`).

For example, to compile and run the solution for **Question 1**:

```bash
# 1. Navigate to the specific directory
cd q1

# 2. Compile the C source file
gcc q1.c -o a.out

# 3. Execute the compiled program
./a.out
```

You can repeat this exact process for any of the other directories (`q2`, `q3`, ..., `q9`) by simply changing the directory and filename numbers. 

To view the detailed complexity analysis and algorithms for a specific problem, read the `readme.md` file located inside its respective directory.