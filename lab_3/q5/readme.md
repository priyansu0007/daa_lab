# Special Pattern Matrix Multiplication (Divide and Conquer)

This repository contains a C program (`q5.c`) that implements an optimized Divide and Conquer matrix multiplication algorithm for matrices with a specific recursive block structure. By exploiting the mathematical symmetry of the matrices, this algorithm achieves an $O(n^2)$ time complexity, vastly outperforming the standard $O(n^3)$ and Strassen's $O(n^{2.81})$ approaches for this specific use case.

## Approach

The problem specifies that the $n \times n$ matrices (where $n = 2^k$) have the following recursive block structure:
$$M = \begin{pmatrix} M_1 & M_2 \\ M_2 & M_1 \end{pmatrix}$$

When multiplying two such matrices, $A$ and $B$, the resulting matrix $C = A \times B$ will also share this structure:
$$C = \begin{pmatrix} C_1 & C_2 \\ C_2 & C_1 \end{pmatrix}$$

By definition of matrix multiplication:
*   $C_1 = A_1 B_1 + A_2 B_2$
*   $C_2 = A_1 B_2 + A_2 B_1$

Instead of computing the 4 multiplications required above (or even 7 as in Strassen's), we can reduce the problem to exactly **2 recursive multiplications** by computing intermediate matrices $X$ and $Y$:
1.  **Compute X:** $X = (A_1 + A_2) \times (B_1 + B_2)$
    Expanding this: $X = A_1 B_1 + A_1 B_2 + A_2 B_1 + A_2 B_2$
2.  **Compute Y:** $Y = (A_1 - A_2) \times (B_1 - B_2)$
    Expanding this: $Y = A_1 B_1 - A_1 B_2 - A_2 B_1 + A_2 B_2$

By algebraically combining $X$ and $Y$, we can extract $C_1$ and $C_2$:
*   $C_1 = \frac{X + Y}{2} = \frac{2A_1 B_1 + 2A_2 B_2}{2} = A_1 B_1 + A_2 B_2$
*   $C_2 = \frac{X - Y}{2} = \frac{2A_1 B_2 + 2A_2 B_1}{2} = A_1 B_2 + A_2 B_1$

Since we only need to perform 2 multiplications of size $\frac{n}{2} \times \frac{n}{2}$ and a constant number of matrix additions/subtractions (which take $O(n^2)$ time), the time complexity drops significantly.

---

## Time Complexity Derivation (Step-by-Step)

Let $T(n)$ be the time complexity to multiply two matrices of size $n \times n$.
The algorithm performs exactly 2 recursive calls of size $\frac{n}{2}$ and a few block additions/subtractions taking $O(n^2)$ time.

The recurrence relation is:
$$T(n) = 2T\left(\frac{n}{2}\right) + c \cdot n^2$$

Step-by-step substitution method:
**Step 1:** $T(n) = 2T\left(\frac{n}{2}\right) + c n^2$
**Step 2:** Substitute $T\left(\frac{n}{2}\right)$ with $2T\left(\frac{n}{4}\right) + c\left(\frac{n}{2}\right)^2$:
$$T(n) = 2 \left[ 2T\left(\frac{n}{4}\right) + c \frac{n^2}{4} \right] + c n^2$$
$$T(n) = 4T\left(\frac{n}{4}\right) + \frac{1}{2} c n^2 + c n^2$$
**Step 3:** Substitute $T\left(\frac{n}{4}\right)$ with $2T\left(\frac{n}{8}\right) + c\left(\frac{n}{4}\right)^2$:
$$T(n) = 4 \left[ 2T\left(\frac{n}{8}\right) + c \frac{n^2}{16} \right] + \frac{1}{2} c n^2 + c n^2$$
$$T(n) = 8T\left(\frac{n}{8}\right) + \frac{1}{4} c n^2 + \frac{1}{2} c n^2 + c n^2$$

Generalizing for $k$ recursive steps:
$$T(n) = 2^k T\left(\frac{n}{2^k}\right) + c n^2 \left[ 1 + \frac{1}{2} + \frac{1}{4} + \dots + \frac{1}{2^{k-1}} \right]$$

Base Case: The recursion stops when $n = 1$.
$$\frac{n}{2^k} = 1 \implies 2^k = n \implies k = \log_2 n$$

Substitute $k$ back into the generalized equation:
First term: $2^{\log_2 n} T(1) = n \cdot O(1) = O(n)$
Second term: The sum of the geometric series $1 + \frac{1}{2} + \frac{1}{4} + \dots$ approaches 2. Thus, the term becomes $2 c n^2 = O(n^2)$.

Since $O(n^2)$ dominates $O(n)$, the total time complexity is bounded by $n^2$.

**Total Time Complexity:** $O(n^2)$

---

## Space Complexity Derivation

At each level of the recursion tree, we allocate auxiliary matrices for the sub-problems ($SA$, $SB$, $DA$, $DB$, $X$, $Y$) of size $\frac{n}{2} \times \frac{n}{2}$. 
Because the recursion is evaluated depth-first, we only need to keep track of the memory allocated along a single path down the recursion tree.

Space allocated at the current level for a matrix of size $n$:
$$S_{\text{level}}(n) = 6 \cdot \left(\frac{n}{2}\right)^2 = \frac{6}{4} n^2 = 1.5 n^2$$

The total space $S(n)$ on the call stack is the sum of space allocated at all depths down to the leaf nodes:
$$S(n) = S_{\text{level}}(n) + S_{\text{level}}\left(\frac{n}{2}\right) + S_{\text{level}}\left(\frac{n}{4}\right) + \dots$$
$$S(n) = 1.5 n^2 + 1.5 \left(\frac{n}{2}\right)^2 + 1.5 \left(\frac{n}{4}\right)^2 + \dots$$
$$S(n) = 1.5 n^2 \left( 1 + \frac{1}{4} + \frac{1}{16} + \dots \right)$$

This is a convergent geometric series with ratio $r = \frac{1}{4}$.
Sum $= \frac{1}{1 - 1/4} = \frac{4}{3}$

$$S(n) = 1.5 n^2 \cdot \left(\frac{4}{3}\right) = 2 n^2$$

**Total Space Complexity:** $O(n^2)$

---

## Sample Output

Compile the code using gcc:

    gcc q5.c -o a.out

Run the executable and provide the properly structured inputs:

    ./a.out
    Enter the size of the matrix n (must be a power of 2, e.g., 2, 4, 8): 2
    
    Note: Please ensure the inputted matrices follow the special recursive block pattern.
    
    Enter the elements of Matrix A (2 x 2):
    1 2
    2 1
    
    Enter the elements of Matrix B (2 x 2):
    3 4
    4 3

**Execution Result:**

    Matrix A:
       1    2 
       2    1 
    
    Matrix B:
       3    4 
       4    3 
    
    Resultant Matrix C (A * B):
      11   10 
      10   11