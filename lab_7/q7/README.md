# Matrix Chain Multiplication (MCM) Problem

## 1. Problem Statement
Consider a sequence (chain) of $n$ matrices to be multiplied: $A_1 	imes A_2 	imes \dots 	imes A_n$. Matrix multiplication is associative, meaning we can parenthesize the product in many different ways without changing the final result. However, the order in which we multiply the matrices can drastically affect the total number of scalar multiplications required. Given an array $P$ that represents the dimensions of these matrices (where matrix $A_i$ has dimensions $P[i-1] 	imes P[i]$), the objective is to find the most efficient way to multiply these matrices. This involves determining the minimum number of scalar multiplications and identifying the optimal parenthesization.

## 2. Approach
We solve this using **Dynamic Programming** because the problem exhibits optimal substructure and overlapping subproblems. 
Let `m[i][j]` represent the minimum number of scalar multiplications needed to compute the matrix chain $A_i \dots A_j$. 
- **Base Case:** When $i = j$ (only one matrix), the cost is 0, so `m[i][i] = 0`.
- **Recursive Step:** For a chain of length 2 or more, we split the product at some point $k$ (where $i \le k < j$). The cost of evaluating this split is the cost of computing the left half ($A_i \dots A_k$), plus the cost of computing the right half ($A_{k+1} \dots A_j$), plus the cost of multiplying the two resulting matrices together. 

The cost to multiply a matrix of size $(P[i-1] 	imes P[k])$ with a matrix of size $(P[k] 	imes P[j])$ is $P[i-1] 	imes P[k] 	imes P[j]$.
Thus, the recurrence relation is:
`m[i][j] = min(m[i][k] + m[k+1][j] + P[i-1]*P[k]*P[j])` for $i \le k < j$.

We build a table `m` to store these minimum costs and another table `s` to store the optimal split point $k$ for each subproblem, which allows us to reconstruct the final optimal parenthesis placement.

## 3. Algorithm/ Pseudocode
```text
Algorithm MATRIX_CHAIN_ORDER(P, n)
// Input: Array P of size n containing matrix dimensions. (Number of matrices is n-1)
// Output: Tables m and s representing minimum costs and split points.

START
    1. CREATE 2D arrays m[n][n] and s[n][n]
    2. FOR i = 1 TO n - 1 DO:
           m[i][i] = 0  // Base case: cost of multiplying 1 matrix is 0
           
    3. FOR L = 2 TO n - 1 DO:  // L is the chain length
           FOR i = 1 TO n - L DO:
               j = i + L - 1
               m[i][j] = INFINITY
               FOR k = i TO j - 1 DO:
                   cost = m[i][k] + m[k+1][j] + P[i-1] * P[k] * P[j]
                   IF cost < m[i][j] THEN:
                       m[i][j] = cost
                       s[i][j] = k
                       
    4. PRINT "Minimum scalar multiplications: ", m[1][n-1]
    5. CALL PRINT_OPTIMAL_PARENS(s, 1, n-1)
END

Algorithm PRINT_OPTIMAL_PARENS(s, i, j)
    IF i == j THEN
        PRINT "A" (with appropriate index)
    ELSE
        PRINT "("
        PRINT_OPTIMAL_PARENS(s, i, s[i][j])
        PRINT_OPTIMAL_PARENS(s, s[i][j] + 1, j)
        PRINT ")"
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** The dynamic programming approach uses three nested loops. 
    - The outermost loop `L` controls the length of the chain being evaluated (runs $O(n)$ times).
    - The middle loop `i` controls the starting index of the chain (runs $O(n)$ times).
    - The innermost loop `k` checks every possible split point between `i` and `j` (runs up to $O(n)$ times).
    Multiplying these together yields an overall scaling proportional to the cube of the input size.
* **Result:** **O(n^3)** (Cubic Time Complexity).

### ii) Space Complexity
* **Derivation:** The algorithm allocates two 2D matrices (or tables), `m` and `s`, each of size $n 	imes n$, to store the subproblem costs and the optimal split points respectively.
* **Result:** **O(n^2)** (Quadratic Space Complexity).

## 5. Sample Output
Given an input array `P = [30, 35, 15, 5, 10, 20, 25]` (representing 6 matrices):
```text
Minimum scalar multiplications: 15125
Optimal parenthesization: ((A(BC))((DE)F))
```
*(Explanation: The input represents matrices of sizes 30x35, 35x15, 15x5, 5x10, 10x20, and 20x25. By grouping the multiplications as `((A(BC))((DE)F))`, we minimize the intermediate element multiplications to a total of 15,125 operations, which is the most optimal arrangement compared to standard left-to-right multiplication.)*
