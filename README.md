
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
| 1 | Find the $n$-th Fibonacci number using Dynamic Programming (Memoization and Tabulation) |
| 2 | Implement the 0/1 Knapsack problem using Bottom-Up Dynamic Programming |
| 3 | Implement the Longest Common Subsequence (LCS) algorithm with backtracking |
| 4 | Implement Matrix Chain Multiplication and optimal parenthesization |

## Lab-06.2 Experiments (Arrays, Matrices, Convolution & Reversal Sorting)

| Question | Topic |
|---:|---|
| 1 | 1D array operations and complexities (Max, largest, mean, median, std dev, mode, duplicates, reversal, partition) |
| 2 | 2D square matrix operations and complexities (Addition, multiplication, zero check, symmetry, determinant, transpose in situ, eigenvalues/eigenvectors) |
| 3 | Convolution operation on vectors of size n using $O(n \log n)$ Fast Fourier Transform (FFT) |
| 4 | Sorting via reversal procedure with an $O(n \log^2 n)$ block-rotation merge strategy |

## Lab-07 Experiments (Algorithm Application Puzzles)

| Question | Topic |
|---:|---|
| 1 | **Invert the coin-triangle:** Determine the minimum number of moves to flip a triangle of coins upside down by sliding one coin at a time. |
| 2 | **Super egg testing experiment:** Find the minimum guaranteed number of droppings to determine the highest safe floor using dynamic programming. |
| 3 | **Reve's puzzle:** Transfer $n$ disks across four pegs using minimum moves (Frame-Stewart Algorithm). |
| 4 | **Security switches:** Find the minimum sequence of toggles to turn off a row of $n$ interdependent security switches. |
| 5 | **Hitting a moving target:** Design a guaranteed sequence of shots to hit a target moving between adjacent hiding spots. |
| 6 | **The best time to be alive:** Find the year when the largest number of prominent scientists were alive simultaneously using a line sweep algorithm. |
| 7 | **Matrix Chain Multiplication (MCM):** Determine the minimum number of scalar multiplications required to multiply a chain of matrices. |

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