# DAA Lab 5 - Sorting and Selection Algorithms

This repository contains the C programs and complexity analyses for Design and Analysis of Algorithms (DAA) Lab 5. The lab focuses on linear-time selection algorithms (QuickSelect) and efficient sorting algorithms (Quick Sort, Heap Sort) combined with File I/O operations.

## Problem Statements

| Question | Problem Statement | Algorithm Used |
| :---: | :--- | :--- |
| **Q1** | Find the median of a list of N numbers without sorting the list. Do the complexity analysis of your algorithm. | QuickSelect |
| **Q2** | Find the K'th smallest element in a given list of N numbers without sorting the list. Do the complexity analysis of your algorithm. | QuickSelect |
| **Q3** | Implement Quick sort of N random elements stored in a file. | Quick Sort + File I/O |
| **Q4** | Implement Heap Sort to sort N randomly generated elements stored in a file. Do the complexity analysis of your algorithm. | Heap Sort + File I/O |

## Directory Structure

```text
.
├── q1
│   ├── a.out
│   ├── q1.c
│   └── README.md
├── q2
│   ├── a.out
│   ├── q2.c
│   └── README.md
├── q3
│   ├── a.out
│   ├── q3.c
│   ├── readme.md
│   ├── sorted.txt
│   └── unsorted.txt
└── q4
    ├── a.out
    ├── q4.c
    ├── README.md
    ├── sorted.txt
    └── unsorted.txt
```

## Compilation and Execution Instructions

To compile and run any of the C programs, open your terminal, navigate to the specific question's directory, and use the `gcc` compiler.

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

*Note: You can repeat the exact same steps for `q2`, `q3`, and `q4` by simply changing the directory and the `.c` file name (e.g., `cd ../q2` then `gcc q2.c -o a.out`). For Q3 and Q4, running the executable will also generate `unsorted.txt` and `sorted.txt` in their respective directories.*
