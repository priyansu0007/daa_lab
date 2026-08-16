# Lab 3: Algorithm Analysis and Divide & Conquer

This repository contains the implementations and theoretical analyses for Lab 3. The exercises focus on algorithm complexity, loop invariants, and various applications of the Divide and Conquer paradigm. 

---

## Directory Structure

The project is organized into individual directories for each question. Each folder contains the C source code, the compiled executable, and a dedicated readme.md containing the specific mathematical derivations and complexity analyses for that problem.

    lab_3
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
    └── readme.md

---

## Problem Summaries

### Q1: Binary vs. Ternary Search
* **Objective:** Implement and compare Binary Search and Ternary Search.
* **Key Concept:** Demonstrates mathematically and empirically why Binary Search is more efficient by tracking the exact number of element comparisons made during execution.

### Q2: Defective Coin Quality Control
* **Objective:** Find a single defective (lighter) coin among n coins using a balance scale.
* **Key Concept:** Uses a Divide and Conquer approach to achieve a time complexity of O(log_2 n). Handles both even and odd total coin counts and edge cases where no defective coin exists.

### Q3: Min and Max using Divide & Conquer
* **Objective:** Find the minimum and maximum elements in an array simultaneously.
* **Key Concept:** Utilizes recursive halving to pair elements, strictly bounding the worst-case number of comparisons to 3n/2 - 2, proving it is vastly more efficient than standard linear scanning.

### Q4: Strassen's Matrix Multiplication
* **Objective:** Multiply two n x n matrices using Strassen's Algorithm.
* **Key Concept:** Implements dynamic memory padding (rounding up to the nearest power of 2) to recursively multiply matrices in O(n^2.81) time by reducing the number of sub-matrix multiplications from 8 to 7.

### Q5: Special-Pattern Matrix Multiplication
* **Objective:** Multiply matrices with a strict recursive symmetric block structure.
* **Key Concept:** Exploits the mathematical symmetry of the matrices to reduce the necessary sub-multiplications down to 2, achieving a highly optimized O(n^2) time complexity.

### Q6: Selection Sort Analysis & Loop Invariants
* **Objective:** Analyze the Selection Sort algorithm's correctness and complexity.
* **Key Concept:** Validates the initialization, maintenance, and termination of loop invariants. Empirically proves that the best-case and worst-case time complexities are both Theta(n^2).

---

## General Compilation and Execution Instructions

To compile and run any of the programs, navigate into the respective directory and use the gcc compiler. 

**Standard Compilation:**

    cd q1
    gcc q1.c -o a.out
    ./a.out

**Note for Q2 (Math Library):**
Question 2 uses functions from math.h (ceil and log2). You must append the -lm flag during compilation:

    cd q2
    gcc q2.c -o a.out -lm
    ./a.out

For detailed time and space complexity derivations, please refer to the readme.md file located inside each individual question's folder.