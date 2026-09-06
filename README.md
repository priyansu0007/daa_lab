# Design and Analysis of Algorithms (DAA) Lab

This repository contains my Design and Analysis of Algorithms (DAA) laboratory work, including C implementations, experimental data, graphs, Gnuplot scripts, and reports. 

The repository is organized lab-wise, with each subfolder containing the source code and supporting files for a particular experiment.

## Repository Structure

    ├── lab_1
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   ├── q4
    │   ├── q5
    │   └── q6
    ├── lab_2
    │   ├── q1
    │   ├── q2
    │   └── q3
    ├── lab_3
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   ├── q4
    │   ├── q5
    │   └── q6
    ├── lab_4
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   ├── q4
    │   ├── q5
    │   └── q6
    ├── lab_5
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   └── q4
    ├── lab_6_1
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   └── q4
    ├── lab_6_2
    │   ├── q1
    │   ├── q2
    │   ├── q3
    │   └── q4
    ├── questions
    └── README.md

> *The exact folder and file names may vary as more experiments are added.*

---

## Lab-01 Experiments

| Question | Topic |
|---:|---|
| 1 | Ordering functions by their asymptotic growth rates |
| 2 | Fair vs. biased coin-toss simulation |
| 3 | Performance comparison of optimized and unoptimized Bubble Sort |
| 4 | Towers of Hanoi and analysis of the number of moves |
| 5 | Finding the partition point between a run of 0s and a run of 1s |
| 6 | Element uniqueness and duplicate detection |

## Lab-02 Experiments

| Question | Topic |
|---:|---|
| 1 | Dictionary Operations |
| 2 | Merge sort vs. modified merge sort |
| 3 | Merging k sorted arrays |

## Lab-03 Experiments

| Question | Topic |
|---:|---|
| 1 | Binary vs. Ternary Search Analysis |
| 2 | Defective Coin Quality Control (Divide and Conquer) |
| 3 | Min and Max using Divide and Conquer |
| 4 | Strassen's Matrix Multiplication |
| 5 | Special-Pattern Matrix Multiplication |
| 6 | Selection Sort Analysis and Loop Invariants |

## Lab-04 Experiments (Applications of Sorting)

| Question | Topic |
|---:|---|
| 1 | Stable Color Sort: Grouping pairs by color while preserving numerical order |
| 2 | Two Sum Across Sets: Finding a cross-set pair that adds up to a target |
| 3 | k-Sum Target Finder: Recursive reduction to find k integers that sum to T |
| 4 | Peak Party Time: Analyzing entry/exit intervals to find max simultaneous attendees |
| 5 | Merge Intervals: Consolidating overlapping timeframes |
| 6 | Max Interval Overlap: Identifying the single point covered by the most intervals |

## Lab-05 Experiments (Selection & File I/O Sorting)

| Question | Topic |
|---:|---|
| 1 | Find the median of a list of N numbers without sorting the list (QuickSelect) |
| 2 | Find the K'th smallest element in a given list of N numbers without sorting the list |
| 3 | Implement Quick sort of N random elements stored in a file |
| 4 | Implement Heap Sort to sort N randomly generated elements stored in a file |

## Lab-06.1 Experiments (Dynamic Programming)

| Question | Topic |
|---:|---|
| 1 | Find the $n$-th Fibonacci number using Dynamic Programming (Memoization and Tabulation)[cite: 1] |
| 2 | Implement the 0/1 Knapsack problem using Bottom-Up Dynamic Programming[cite: 1] |
| 3 | Implement the Longest Common Subsequence (LCS) algorithm with backtracking[cite: 1] |
| 4 | Implement Matrix Chain Multiplication and optimal parenthesization[cite: 1] |

## Lab-06.2 Experiments (Arrays, Matrices, Convolution & Reversal Sorting)

| Question | Topic |
|---:|---|
| 1 | 1D array operations and complexities (Max, largest, mean, median, std dev, mode, duplicates, reversal, partition)[cite: 1] |
| 2 | 2D square matrix operations and complexities (Addition, multiplication, zero check, symmetry, determinant, transpose in situ, eigenvalues/eigenvectors)[cite: 1] |
| 3 | Convolution operation on vectors of size n using $O(n \log n)$ Fast Fourier Transform (FFT)[cite: 1] |
| 4 | Sorting via reversal procedure with an $O(n \log^2 n)$ block-rotation merge strategy[cite: 1] |

---

## Contents of Each Experiment

Depending on the experiment, a subfolder may contain:

*   **.c** — C source code
*   **.plt** — Gnuplot script used to generate graphs
*   **.txt** or **.csv** — Experimental data
*   **.png** — Generated graph or visualization
*   **.md** — Explanation of the approach, observations, and complexity analysis

---

## Tools Used

*   **C** — Algorithm implementation and simulation
*   **GCC** — Compilation
*   **Gnuplot** — Graph generation
*   **Markdown** — Documentation and analysis

---

## How to Run

### Compile a C program

    gcc filename.c -o program -lm

*The -lm flag links the C math library and is required when functions such as log10(), log2(), sqrt(), or pow() (as well as complex number operations) are used.*

### Run the program

    ./program

### Generate a graph using Gnuplot

    gnuplot filename.plt

*The generated graph will be saved according to the output filename specified in the .plt file.*

---

## Purpose

The purpose of this repository is to:
*   Implement algorithms in C
*   Study algorithm correctness and efficiency
*   Compare empirical and theoretical performance
*   Analyze time and space complexity
*   Visualize algorithmic behavior using graphs
*   Maintain organized documentation for DAA lab experiments

## Notes

*   Each experiment is stored in a separate subfolder for easier navigation.
*   Generated data and graphs are included whenever they are useful for analysis.
*   Complexity results describe asymptotic behavior; constants and lower-order terms may affect practical performance but do not change the Big-O growth class.

## Author

**Priyansu Kumar Mahapatra**  
B.Tech — Computer Science and Engineering  
IIIT Bhubaneswar