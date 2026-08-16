# Strassen's Matrix Multiplication (Divide and Conquer)

This repository contains a C program (`q4.c`) that implements Strassen's method for matrix multiplication. By using a Divide and Conquer approach, Strassen's algorithm reduces the time complexity compared to the standard naive O(n^3) matrix multiplication algorithm.

## Approach

The standard method of matrix multiplication requires 8 recursive multiplications for a matrix divided into quadrants. Strassen's brilliant insight was to reduce these 8 multiplications to **7 multiplications** using algebraic manipulation, at the cost of extra additions and subtractions.

Our implementation handles arbitrary square matrices (not just powers of 2) using a **padding strategy**:
1. **Pad to Power of 2:** The function `nextPowerOf2(n)` finds the next power of 2 (let's call it `m`). The program allocates `m x m` matrices and initializes the extra padded elements to `0`. This guarantees perfect subdivisions at every recursive step without altering the mathematical result.
2. **Divide:** The `m x m` matrices A and B are logically and physically divided into 4 sub-matrices of size `m/2 x m/2` (A11, A12, A21, A22, and B11, B12, B21, B22).
3. **Conquer:** The algorithm recursively computes 7 intermediate matrices (M1 through M7) using specific formulas of additions, subtractions, and multiplications.
4. **Combine:** The 4 quadrants of the result matrix (C11, C12, C21, C22) are computed by adding and subtracting the intermediate `M` matrices.
5. **Clean up:** The program safely deallocates the extensive memory used during the recursive steps, and finally prints only the original `n x n` bounding box of the result matrix C.

---

## Time Complexity Derivation (Step-by-Step)

Let T(n) be the time taken to multiply two n x n matrices.
In Strassen's algorithm, the matrices are divided into halves (size n/2), and we perform exactly 7 recursive multiplications and a constant number of additions/subtractions of size (n/2 x n/2).

The recurrence relation is:
T(n) = 7 * T(n/2) + O(n^2)  (since matrix addition takes O(n^2) time)

Let's expand this using the substitution method. Let c * n^2 represent the O(n^2) work.
Step 1: T(n) = 7 * T(n/2) + c * n^2
Step 2: Substitute T(n/2) with (7 * T(n/4) + c * (n/2)^2):
        T(n) = 7 * [7 * T(n/4) + c * (n^2 / 4)] + c * n^2
        T(n) = 7^2 * T(n/4) + c * n^2 * (7/4) + c * n^2
Step 3: Substitute T(n/4) with (7 * T(n/8) + c * (n/4)^2):
        T(n) = 7^2 * [7 * T(n/8) + c * (n^2 / 16)] + c * n^2 * (7/4) + c * n^2
        T(n) = 7^3 * T(n/8) + c * n^2 * (7/16) + c * n^2 * (7/4) + c * n^2

Generalizing for k recursive steps:
T(n) = 7^k * T(n / 2^k) + c * n^2 * [1 + (7/4) + (7/4)^2 + ... + (7/4)^(k-1)]

Base Case: The recursion stops when the matrix size becomes 1 x 1.
n / 2^k = 1  =>  n = 2^k
Applying log base 2: k = log_2(n)

First Term Analysis:
7^k = 7^(log_2(n)) 
Using logarithm properties (a^(log_b(c)) = c^(log_b(a))), this is equal to:
n^(log_2(7)) ≈ n^2.8074

Second Term Analysis (Geometric Series):
The sum of the geometric series [1 + (7/4) + ... + (7/4)^(k-1)] evaluates to a constant factor bounded by the largest term (7/4)^k. 
n^2 * (7/4)^k = n^2 * (7^k / 4^k) = n^2 * (n^log_2(7) / n^2) = n^log_2(7).

Combining both terms, the dominant factor is n^log_2(7).

**Time Complexity:** O(n^log_2(7)) ≈ O(n^2.81)

---

## Space Complexity Derivation

Strassen's algorithm is notorious for its high memory footprint because it requires allocating new sub-matrices at every step of the recursion tree.

At any level of recursion for a matrix of size n, we allocate space for 18 sub-matrices (A11...B22, M1...M7, temps) of size (n/2) x (n/2). 
Space at current level: S_level = 18 * (n/2)^2 = 4.5 * n^2

Since these matrices are dynamically allocated and pushed onto the recursion stack, the total space S(n) is the sum of space across all recursive depths down to the leaf nodes.
S(n) = O(n^2) + O((n/2)^2) + O((n/4)^2) + ...
S(n) = n^2 * (1 + 1/4 + 1/16 + ...)

This is a convergent geometric series summing to exactly 4/3. 
Therefore, S(n) = (4/3) * n^2.

**Space Complexity:** O(n^2)

---

## Sample Output

Compile the code using gcc:

    gcc q4.c -o a.out

Run the executable and provide the matrix inputs:

    ./a.out

**Execution Session:**

    Enter the size of the square matrix (n): 2
    
    Enter the elements of Matrix A (2 x 2):
    1 2
    3 4
    
    Enter the elements of Matrix B (2 x 2):
    5 6
    7 8
    
    Resultant Matrix C (A * B):
    19 22 
    43 50