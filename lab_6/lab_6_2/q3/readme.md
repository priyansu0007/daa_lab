# DAA Lab 6 - Question 3: Convolution Operation on Vectors

## Problem Statement
The convolution of two vectors $A$ and $B$ (with lengths $m$ and $n$, respectively) is a new vector $C$ such that:
$C[k] = \sum_{j=0}^{m-1} A[j]B[k-j]$

Assuming $n \ge m$ and 0-based indexing, find an $O(n \log n)$ divide and conquer algorithm for this operation. Validate the algorithm with a C program and perform the corresponding complexity analysis.

---

## Approach
A naive nested-loop implementation of convolution takes $O(n \times m)$ time. To achieve the required $O(n \log n)$ complexity, this program utilizes the **Fast Fourier Transform (FFT)**.

By moving the vectors from the time domain to the frequency domain using the FFT, the complex convolution operation is simplified into a basic element-wise (point-wise) multiplication. The algorithm follows these steps:
1. **Pad:** Increase the size of both vectors with zeros until their length reaches the nearest power of 2 that is $\ge (m + n - 1)$. Let this length be $L$.
2. **Transform:** Apply the recursive Cooley-Tukey FFT algorithm to both vectors.
3. **Multiply:** Perform point-wise multiplication on the transformed vectors to get a new frequency-domain vector $C$.
4. **Inverse Transform:** Apply the Inverse FFT to $C$ to convert it back to the time domain, yielding the final convolution result.

---

## Algorithm / Pseudocode
```text
procedure nextPowerOf2(val):
    p = 1
    while p < val: p = p * 2
    return p

procedure FFT(a, n, invert):
    if n <= 1: return
    
    // Divide phase
    a0 = elements at even indices of a
    a1 = elements at odd indices of a
    
    // Conquer phase
    FFT(a0, n/2, invert)
    FFT(a1, n/2, invert)
    
    // Combine phase
    angle = 2 * PI / n * (if invert then -1 else 1)
    w = 1, wn = cos(angle) + i * sin(angle)
    
    for j = 0 to n/2 - 1:
        a[j] = a0[j] + w * a1[j]
        a[j + n/2] = a0[j] - w * a1[j]
        w = w * wn
        
procedure Convolution(A, m, B, n):
    L = nextPowerOf2(m + n - 1)
    Pad A and B with zeros up to length L
    
    FFT(A, L, false)
    FFT(B, L, false)
    
    for i = 0 to L - 1:
        C[i] = A[i] * B[i]
        
    FFT(C, L, true)
    
    for i = 0 to L - 1:
        C[i] = C[i] / L  // Scale inverse FFT
        
    return C (first m + n - 1 elements)
```

---

## Complexity Analysis

### Time Complexity
*   **Padding Vectors:** $O(L)$, which is proportionally bounded by $O(n)$ since $n \ge m$.
*   **FFT:** The recursive Cooley-Tukey algorithm splits the array in half at each step, resulting in a recurrence relation of $T(n) = 2T(n/2) + O(n)$. By the Master Theorem, this results in a time complexity of $O(L \log L)$. Since $L$ is at most $2(n + m)$ and $n \ge m$, this simplifies to $O(n \log n)$.
*   **Point-wise Multiplication:** Requires a single linear pass taking $O(n)$ time.
*   **Inverse FFT:** Operates with the exact same recurrence and time complexity as the forward FFT: $O(n \log n)$.
*   **Overall Time Complexity:** The bottleneck of the algorithm is the transforms, making the total worst-case time complexity **$O(n \log n)$**.

### Space Complexity
*   **Padded Vectors:** Allocating the zero-padded complex arrays `A`, `B`, and `C` takes $O(n)$ space.
*   **FFT Recursion:** At each level of the recursion tree, the algorithm allocates temporary arrays `a0` and `a1` for the even and odd elements. Across the $\log n$ levels of the tree, this specific non-in-place implementation requires **$O(n \log n)$** auxiliary space. 

---

## Sample Output
```text
Enter the size of vector A (m) and vector B (n) [Note: n >= m]: 3 4
Enter 3 elements for vector A:
1 2 3
Enter 4 elements for vector B:
4 5 6 7

Convolution Vector C (first 6 elements):
4 13 28 34 32 21 
```