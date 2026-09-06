# DAA Lab 6 - Question 2: 2D Square Matrix Operations and Complexities

## Problem Statement
Given square matrices with $n$ rows and $n$ columns, perform the following operations:
1. Matrix Addition.
2. Matrix Multiplication.
3. Find if the given matrix is a zero matrix.
4. Find if the given matrix is a symmetric matrix.
5. Compute the determinant of the given matrix.
6. Transpose the matrix in situ (in place).
7. Find the eigenvalue and eigenvector of the matrix.

Validate the procedures with a C program and perform the corresponding complexity analysis.

---

## Approach
The program handles the fundamental matrix operations using nested loop traversals and introduces specialized algorithms for the determinant and eigenvalues:

*   **Standard Traversals:** Matrix addition, zero-checking, symmetry-checking, and in-place transposition are achieved using single or nested loops that iterate through the $n \times n$ grid. Transposition specifically iterates only through the upper triangle to swap elements across the main diagonal.
*   **Matrix Multiplication:** Utilizes the standard $O(n^3)$ dot-product approach for rows and columns.
*   **Determinant:** Implemented using **Laplace Expansion (Cofactor Expansion)**. This is a recursive approach that breaks the matrix down into smaller sub-matrices until it reaches a $1 \times 1$ base case.
*   **Eigenvalue and Eigenvector:** Implemented using the **Power Iteration Method**. This iterative numerical algorithm repeatedly multiplies the matrix by a guess vector to approximate the dominant (largest magnitude) eigenvalue and its corresponding eigenvector.

---

## Algorithm / Pseudocode
```text
procedure MatrixMultiplication(A, B, n):
    for i = 0 to n-1:
        for j = 0 to n-1:
            C[i][j] = 0
            for k = 0 to n-1:
                C[i][j] = C[i][j] + (A[i][k] * B[k][j])
    return C

procedure Determinant(mat, current_n):
    if current_n == 1: return mat[0][0]
    
    D = 0, sign = 1
    for f = 0 to current_n - 1:
        temp = getCofactor(mat, 0, f, current_n)
        D = D + sign * mat[0][f] * Determinant(temp, current_n - 1)
        sign = -sign
    return D

procedure PowerIteration(mat, n):
    Initialize vector x of size n with 1.0
    tolerance = 0.00001
    
    do:
        lambda_old = lambda
        // Matrix-vector multiplication
        x_new = mat * x 
        
        // Find dominant element
        lambda = max_magnitude(x_new)
        
        // Normalize
        x = x_new / lambda
    while abs(lambda - lambda_old) > tolerance
    
    return lambda, x

procedure TransposeInSitu(mat, n):
    for i = 0 to n-1:
        for j = i + 1 to n-1:
            swap(mat[i][j], mat[j][i])
```

---

## Complexity Analysis

### Time Complexity
*   **Matrix Addition:** $O(n^2)$ - Iterates through all corresponding elements of both matrices.
*   **Matrix Multiplication:** $O(n^3)$ - Requires three nested loops iterating $n$ times each.
*   **Zero & Symmetric Check:** $O(n^2)$ - Worst-case requires visiting all or half of the $n \times n$ elements, respectively.
*   **Transpose (In Situ):** $O(n^2)$ - Swaps elements in the upper triangular half of the matrix, requiring roughly $n^2 / 2$ operations.
*   **Determinant:** $O(n!)$ - The Laplace expansion branches factorially, making it computationally expensive for large matrices. (An LU decomposition approach would be $O(n^3)$).
*   **Eigenvalue (Power Iteration):** $O(k \times n^2)$ - Where $k$ is the number of iterations required to converge, and each iteration performs a matrix-vector multiplication taking $O(n^2)$ time.

### Space Complexity
*   **Base Storage:** $O(n^2)$ to store matrices `A`, `B`, and `C`.
*   **Determinant Recursion:** $O(n^3)$ - The recursive stack depth is $n$, and at each level, an $(n-1) \times (n-1)$ temporary cofactor matrix is allocated. 
*   **Power Iteration vectors:** $O(n)$ - Requires 1D arrays of size $n$ (`x` and `x_new`).
*   **Overall Space Complexity:** Dominated by the cofactor allocation in the recursive determinant function, making it **$O(n^3)$** in this specific implementation.

---

## Sample Output
```text
Enter the size (n) for the n x n square matrices: 2

--- Input Matrix A ---
A[0][0]: 2
A[0][1]: 1
A[1][0]: 1
A[1][1]: 2

--- Input Matrix B (for Addition/Multiplication) ---
B[0][0]: 1
B[0][1]: 0
B[1][0]: 0
B[1][1]: 1

(i) Matrix Addition (A + B):
3	1	
1	3	

(ii) Matrix Multiplication (A * B):
2	1	
1	2	

(iii) Matrix A is NOT a Zero Matrix.
(iv) Matrix A is a Symmetric Matrix.
(v) Determinant of Matrix A: 3

(vii) Dominant Eigenvalue: 3.0000
      Corresponding Eigenvector: [ 1.0000 1.0000 ]

(vi) Matrix A Transposed (In Situ):
2	1	
1	2	
```