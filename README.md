# Design and Analysis of Algorithms (DAA) Lab

This repository contains my **Design and Analysis of Algorithms (DAA) laboratory work**, including C implementations, experimental data, graphs, Gnuplot scripts, and reports.

The repository is organized lab-wise, with each subfolder containing the source code and supporting files for a particular experiment.

## Repository Structure

```text
├── lab_1
│   ├── q1
│   ├── q2
│   ├── q3
│   ├── q4
│   ├── q5
│   └── q6
└── README.md

> The exact folder and file names may vary as more experiments are added.

## Lab-01 Experiments

| Question | Topic |
|---:|---|
| 1 | Ordering functions by their asymptotic growth rates |
| 2 | Fair vs. biased coin-toss simulation |
| 3 | Performance comparison of optimized and unoptimized Bubble Sort |
| 4 | Towers of Hanoi and analysis of the number of moves |
| 5 | Finding the partition point between a run of `0`s and a run of `1`s |
| 6 | Element uniqueness and duplicate detection |

## Contents of Each Experiment

Depending on the experiment, a subfolder may contain:

- `*.c` — C source code
- `*.plt` — Gnuplot script used to generate graphs
- `*.txt` or `*.csv` — Experimental data
- `*.png` — Generated graph or visualization
- `*.md` — Explanation of the approach, observations, and complexity analysis

## Lab-01: Function Growth-Rate Comparison

The first experiment compares the growth of the following functions:

\[
\frac{1}{n},\quad \log_2 n,\quad 12\sqrt n,\quad 50n^{0.5},\quad n^{0.51}
\]

\[
2^{32}n,\quad n\log_2 n,\quad n^2-324,\quad 100n^2+6n
\]

\[
2n^3,\quad n^{\log_2 n},\quad 3^n
\]

The implementation uses logarithmic transformations to compare functions over a large range of values without numerical overflow.

For sufficiently large values of \(n\), the growth rates are ordered approximately as:

\[
\frac{1}{n}
<
\log n
<
\sqrt n
<
n^{0.51}
<
n
<
n\log n
<
n^2
<
n^3
<
n^{\log_2 n}
<
3^n
\]

## Tools Used

- **C** — Algorithm implementation and simulation
- **GCC** — Compilation
- **Gnuplot** — Graph generation
- **Markdown** — Documentation and analysis

## How to Run

### Compile a C program

```bash
gcc filename.c -o program -lm
```

The `-lm` flag links the C math library and is required when functions such as `log10()`, `log2()`, `sqrt()`, or `pow()` are used.

### Run the program

```bash
./program
```

### Generate a graph using Gnuplot

```bash
gnuplot filename.plt
```

The generated graph will be saved according to the output filename specified in the `.plt` file.

## Purpose

The purpose of this repository is to:

- Implement algorithms in C
- Study algorithm correctness and efficiency
- Compare empirical and theoretical performance
- Analyze time and space complexity
- Visualize algorithmic behavior using graphs
- Maintain organized documentation for DAA lab experiments

## Notes

- Each experiment is stored in a separate subfolder for easier navigation.
- Generated data and graphs are included whenever they are useful for analysis.
- Complexity results describe asymptotic behavior; constants and lower-order terms may affect practical performance but do not change the Big-O growth class.

## Author

**Priyansu Kumar Mahapatra**  
B.Tech — Computer Science and Engineering
