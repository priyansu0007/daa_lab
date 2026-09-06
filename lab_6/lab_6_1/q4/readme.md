# DAA Lab 6 - Question 4: Matrix Chain Multiplication

## Problem Statement
Write a program to implement Matrix Chain Multiplication using Dynamic Programming. Given the dimensions of $N-1$ matrices in an array `arr[]`, determine the minimum number of scalar multiplications required to multiply the complete matrix chain, and output the optimal parenthesization. Analyze the time and space complexity of the algorithm.

---

## Approach
The program uses a **Bottom-Up Dynamic Programming** approach to find the most efficient way to multiply a given sequence of matrices. The problem is not to perform the multiplications, but merely to decide the sequence of the matrix multiplications.

1.  **Cost Matrix (`m`)**: A 2D table `m[i][j]` is constructed to store the minimum number of scalar multiplications needed to compute the matrix $A_{i \dots j}$. Chains of length 1 require 0 multiplications. The algorithm progressively solves for chains of length 2, 3, up to $N$.
2.  **Split Matrix (`s`)**: Another 2D table `s[i][j]` is maintained to store the index $k$ at which the optimal split occurred for the chain $A_{i \dots j}$.
3.  **Reconstruction**: Once the tables are fully populated, the minimum cost is found at `m[1][n-1]`. A recursive function (`printOptimalParenthesis`) uses the split points recorded in the `s` table to backtrack and format the optimal parenthesization string.

---

## Algorithm / Pseudocode
```text
procedure MatrixChainOrder(p[], n):
    Create table m[n][n] and s[n][n]
    
    // Base case: zero cost for multiplying one matrix
    for i = 1 to n - 1:
        m[i][i] = 0
        
    // L is the chain length
    for L = 2 to n - 1:
        for i = 1 to n - L:
            j = i + L - 1
            m[i][j] = INFINITY
            
            // Try every possible split point k
            for k = i to j - 1:
                cost = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j])
                
                if cost < m[i][j]:
                    m[i][j] = cost
                    s[i][j] = k  // Store the optimal split point

    return m[1][n - 1], s

procedure PrintOptimalParenthesis(s, i, j):
    if i == j:
        print "A", i
        return
        
    print "("
    PrintOptimalParenthesis(s, i, s[i][j])
    PrintOptimalParenthesis(s, s[i][j] + 1, j)
    print ")"
```

---

## Complexity Analysis

### Time Complexity
*   **$O(n^3)$**: The algorithm relies on three nested loops. The outermost loop iterates over the chain length $L$ (up to $n$), the middle loop iterates over the starting index $i$ (up to $n$), and the innermost loop tests all possible split points $k$ between $i$ and $j$. This results in a cubic time complexity, mathematically represented as $O(n^3)$. 

### Space Complexity
*   **$O(n^2)$**: The dynamic programming implementation requires the allocation of two 2D arrays, `m` (cost matrix) and `s` (split matrix), each of dimensions $n \times n$. Therefore, the space complexity is quadratic, $O(n^2)$.

---

## Sample Output
*(Based on the hardcoded input: p = {40, 20, 30, 10, 30})*

```text
Matrix Dimensions:
A1: 40 x 20
A2: 20 x 30
A3: 30 x 10
A4: 10 x 30

Minimum number of scalar multiplications: 26000
Optimal Parenthesization: ((A1(A2A3))A4)

--- Cost Matrix (m) ---
     0  24000  14000  26000 
     -      0   6000  12000 
     -      -      0   9000 
     -      -      -      0 

--- Split/Parenthesis Matrix (s) ---
   -    1    1    3 
   -    -    2    3 
   -    -    -    3 
   -    -    -    - 
```