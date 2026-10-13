# Lab 10: Disjoint Set Union (DSU) & Graph Components

**Course:** Design and Analysis of Algorithms (DAA)  
**Program:** BTech (CS-B and CE), $3^{\text{rd}}$ Semester  
**Instructor:** Dr. Ajaya Kumar Dash  

---

## 1. Directory Structure

```text
lab_10/
├── q1/
│   ├── a.out
│   ├── q1.c
│   └── readme.md
├── q2/
│   ├── a.out
│   ├── q2.c
│   └── readme.md
├── q3/
│   ├── a.out
│   ├── q3.c
│   └── readme.md
├── q4/
│   ├── a.out
│   ├── q4.c
│   └── readme.md
├── q5/
│   ├── a.out
│   ├── q5.c
│   └── readme.md
└── readme.md
```

---

## 2. Problem Statements

| Problem | Directory | Title | Summary / Core Requirement |
| :---: | :---: | :--- | :--- |
| **Q1** | [`q1/`](./q1/) | **Online Graph-Bipartiteness Testing** | Check whether an undirected graph remains bipartite as edges arrive dynamically one by one. Accept edges that preserve bipartiteness (spanning forest edges or even cycles) and reject edges introducing odd cycles using parity-augmented DSU. |
| **Q2** | [`q2/`](./q2/) | **Dynamic Connected Components in a Grid (Number of Islands II)** | Start with an $R \times C$ grid of water cells. Land cells arrive one by one at $(r_k, c_k)$. Output the running count of 4-directionally connected land components (islands) after each addition using coordinate flattening and DSU. |
| **Q3** | [`q3/`](./q3/) | **Maximum Weight Component with Size Constraints** | Vertices have weights and edges arrive sequentially. At every step, track and report the maximum total vertex weight of any connected component whose size does not exceed a given threshold $K$ using DSU and a lazy-deletion Max-Heap. |
| **Q4** | [`q4/`](./q4/) | **Reverse Time-Step DSU Application** | Vertices of a weighted graph are removed sequentially in a specified order $P = [p_1, \dots, p_V]$. Compute the maximum remaining component sum after each deletion by reversing time to incrementally add vertices and union neighbors. |
| **Q5** | [`q5/`](./q5/) | **Lexicographically Smallest Connected Component Permutation** | Given a permutation of $1 \dots n$ and allowable pairwise swap pairs, find the lexicographically smallest permutation achievable by identifying connected components with DSU and sorting values within each component index set. |

---

## 3. Compilation & Execution Instructions

All solutions are written in standard C (C99 / C11) and can be compiled using `gcc` or `clang`.

### General Build Command (from `lab_10` root)

```bash
# Question 1
gcc -O2 -Wall -Wextra q1/q1.c -o q1/a.out
./q1/a.out

# Question 2
gcc -O2 -Wall -Wextra q2/q2.c -o q2/a.out
./q2/a.out

# Question 3
gcc -O2 -Wall -Wextra q3/q3.c -o q3/a.out
./q3/a.out

# Question 4
gcc -O2 -Wall -Wextra q4/q4.c -o q4/a.out
./q4/a.out

# Question 5
gcc -O2 -Wall -Wextra q5/q5.c -o q5/a.out
./q5/a.out
```

### Compiling and Running Inside Subdirectories

Alternatively, navigate into each problem folder:

```bash
cd q1
gcc -O2 -Wall -Wextra q1.c -o a.out
./a.out
cd ..
```