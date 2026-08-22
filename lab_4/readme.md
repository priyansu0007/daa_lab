# Design and Analysis of Algorithm (DAA) - Lab 04

This repository contains the C programs for Lab-04, focusing on the applications of sorting algorithms [cite: 7]. 

## Directory Structure

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
└── q6
    ├── a.out
    ├── q6.c
    └── readme.md
```

## Problem Summaries

*   **q1 (Stable Color Sort):** An $O(n)$ algorithm to sort $n$ pairs of items (number, color) by color (red, blue, yellow) such that the original numerical order of identical colors is preserved [cite: 7].
*   **q2 (Two Sum Across Sets):** An $O(n \log n)$ algorithm to determine if a pair of elements, one from set $S_{1}$ and one from $S_{2}$, adds up to a given number $x$ [cite: 7].
*   **q3 (k-Sum Target Finder):** An $O(n^{k-1} \log n)$ algorithm to test whether exactly $k$ integers in a set $S$ of $n$ integers add up to a target value $T$ [cite: 7].
*   **q4 (Peak Party Time):** An $O(n \log n)$ algorithm to analyze distinct entry and exit times of attendees to determine the exact time when the most people were simultaneously present at a party [cite: 7].
*   **q5 (Merge Intervals):** An $O(n \log n)$ algorithm that takes a list of $n$ intervals $(x_{i}, y_{i})$ and merges any overlapping intervals into a consolidated list [cite: 7].
*   **q6 (Max Interval Overlap):** An $O(n \log n)$ algorithm to identify a specific point on a line that exists within the largest number of given intervals [cite: 7].

## Execution Guide

To compile and run any of the solutions, navigate to the specific question's directory and use the GNU C Compiler (`gcc`).

1.  **Navigate to the directory:**
    ```bash
    cd q1
    ```
2.  **Compile the source code:**
    ```bash
    gcc q1.c -o a.out
    ```
3.  **Execute the compiled binary:**
    ```bash
    ./a.out
    ```
    
*(Repeat these steps for `q2`, `q3`, etc., by changing the directory and filename accordingly.)*
