# DAA Lab 7 - Algorithm Application Puzzles

This repository contains the C programs and complexity analyses for Design and Analysis of Algorithms (DAA) Lab 7. The lab focuses on algorithmic applications to solve various medium and hard-level puzzles, employing techniques such as dynamic programming, mutual recursion, event processing, and mathematical optimization.

## Problem Statements

| Question | Problem Statement | Algorithm Used |
| :---: | :--- | :--- |
| **Q1** | **Invert the coin-triangle:** Determine the minimum number of moves to flip a triangle of coins upside down by sliding one coin at a time. | Mathematical Modeling / Geometric Overlap |
| **Q2** | **Super egg testing experiment:** Find the minimum guaranteed number of droppings to determine the highest safe floor in an $F$-storey building using $E$ eggs. | Dynamic Programming (Min-Max) |
| **Q3** | **Reve's puzzle:** Transfer $n$ disks across four pegs using minimum moves without placing a larger disk on a smaller one. | Dynamic Programming (Frame-Stewart Algorithm) |
| **Q4** | **Security switches:** Find the minimum sequence of toggles to turn off a row of $n$ interdependent security switches that are initially all turned on. | Mutual Recursion (Chinese Rings Variant) |
| **Q5** | **Hitting a moving target:** Design a guaranteed sequence of shots to hit an invisible target that moves to an adjacent hiding spot after every shot among $n$ spots. | Parity-based Sweeping Algorithm |
| **Q6** | **The best time to be alive:** Find the year when the largest number of prominent scientists were alive simultaneously, given an index of their birth and death years. | Line Sweep (Event Processing) & Sorting |
| **Q7** | **Matrix Chain Multiplication (MCM) problem:** Determine the minimum number of scalar multiplications required to multiply a chain of matrices and output the optimal parenthesization. | Dynamic Programming (Bottom-Up 2D Table) |

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
├── q4
│   ├── a.out
│   ├── q4.c
│   └── README.md
├── q5
│   ├── a.out
│   ├── q5.c
│   └── README.md
├── q6
│   ├── a.out
│   ├── q6.c
│   └── README.md
└── q7
    ├── a.out
    ├── q7.c
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

*Note: You can repeat the exact same steps for `q2` through `q7` by simply changing the directory and the `.c` file name (e.g., `cd ../q3` then `gcc q3.c -o a.out`).*
