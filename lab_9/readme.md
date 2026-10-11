# Lab 9

This repository contains the C implementations, validation programs, and complexity analyses for various advanced algorithmic problems focusing on greedy strategies, priority queues, and timeline simulations.

## 1. Problem Statements

| Question | Problem Name | Description |
| :--- | :--- | :--- |
| **Q1** | Fractional Knapsack with Deterioration Rate | You have $n$ items with base values $v_i$, weights $w_i$, and decay rates $\lambda_i > 0$. If an item is consumed at time $t$, its effective value density decays to $(v_i / w_i) - \lambda_i \cdot t$. Knapsack capacity is $W$. Determine the optimal scheduling order and fractional choices to maximise total value. |
| **Q2** | Huffman Coding | Given symbol frequencies, construct a prefix-free binary code of minimum expected length, and output the canonical Huffman codebook (where codes are ordered lexicographically by length). |
| **Q3** | Minimum Initial Fuel (Reverse Greedy) | A vehicle needs to reach the target $D$ starting with fuel $F$. Along the way are stations $(d_i, f_i)$ (distance from origin and refuel amount). What is the minimum number of refuelling stops required to reach the target? |
| **Q4** | Minimum Cost to Connect Sticks | You have sticks of lengths $L_1, L_2, \dots, L_n$. Connecting two sticks of lengths $x$ and $y$ costs $x + y$, resulting in a single stick of length $x + y$. Find the minimum total cost to connect all sticks into one. |
| **Q5** | Candy Distribution Problem (Bi-directional Slope Greedy) | $n$ children stand in a line, each assigned a rating. Each child must get at least one candy. Children with a higher rating than their immediate neighbours must get more candies than their neighbours. Find the minimum total number of candies needed. |
| **Q6** | Reorganise String with K-Distance Apart | Given a string $S$ and an integer $K$, rearrange $S$ such that the same characters are at least distance $K$ apart. If impossible, return an empty string. |
| **Q7** | Minimise Deviation in Array (Two-Way Greedy with Max-Heap) | Given an array of positive integers, you can perform two operations: multiply any odd element by $2$, or divide any even element by $2$. The deviation is $(\max(A) - \min(A))$. Minimise the deviation after any number of operations. |
| **Q8** | Minimum Number of Meeting Rooms | Given an array of meeting time intervals consisting of start and end times $[[s_1, e_1], [s_2, e_2], \dots]$, find the minimum number of conference rooms required. |
| **Q9** | Hu-Tucker Greedy Simulation | Given an ordered sequence of weights $w_1, w_2, \dots, w_n$, construct an optimal alphabetic binary search tree or merge pattern that maintains the strict in-order sequence of indices while minimizing $\sum w_i \cdot \text{depth}(i)$. |

## 2. Directory Structure

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

## 3. Compile and Execution Instructions

All solutions are written in standard C. To compile and run any of the programs, navigate to the specific question's directory using your terminal and use the `gcc` compiler.

**Example for Question 1:**

1. Navigate to the directory:
   ```bash
   cd q1
   ```
2. Compile the C file:
   ```bash
   gcc q1.c -o a.out
   ```
   *(Note: If the code uses the math library, append `-lm` at the end of the compile command: `gcc q1.c -o a.out -lm`)*

3. Execute the compiled output:
   ```bash
   ./a.out
   ```

Each sub-directory contains its own specific `readme.md` detailing the problem approach, algorithm, pseudocode, and complexity analysis for that individual question.