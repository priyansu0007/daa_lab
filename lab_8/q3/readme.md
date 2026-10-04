# Question 3: Longest Common Subsequence (LCS)

## Directory Structure Context

This solution is located in the `q3` directory:

```
q3/
├── a.out
└── q3.c

```

## Problem Statement

Given two sequences $X = \langle x_1, x_2, \dots, x_m \rangle$ and $Y = \langle y_1, y_2, \dots, y_n \rangle$, compute the length of their longest common subsequence and reconstruct the actual subsequence string. A subsequence is a sequence that can be derived from another sequence by deleting zero or more elements without changing the order of the remaining elements.

## Approach

This problem is solved optimally using **Dynamic Programming (DP)**. We build a 2D table to store the lengths of the longest common subsequences of all prefixes of $X$ and $Y$.

1. **Table Definition:** We use a 2D array `dp` of size $(m + 1) \times (n + 1)$, where `dp[i][j]` represents the length of the LCS of the prefix $X[0 \dots i-1]$ and the prefix $Y[0 \dots j-1]$.
2. **Base Case:** If either string is empty, the LCS length is $0$. Thus, `dp[i][0] = 0` and `dp[0][j] = 0`.
3. **Recursive Step:** 
   * If the characters match ($X[i-1] == Y[j-1]$), we add $1$ to the LCS length of the strings without these characters: `dp[i][j] = dp[i-1][j-1] + 1`.
   * If they do not match, we take the maximum LCS length by either ignoring the current character of $X$ or the current character of $Y$: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
4. **Reconstruction (Traceback):** Starting from `dp[m][n]`, we trace our steps backward through the table. If $X[i-1] == Y[j-1]$, that character is part of the LCS. Otherwise, we move in the direction of the larger value (`dp[i-1][j]` or `dp[i][j-1]`).

## Algorithm

1. Initialize a 2D array `dp` of dimensions $(m + 1) \times (n + 1)$ with zeros.
2. Loop `i` from $1$ to $m$:
   * Loop `j` from $1$ to $n$:
     * If $X[i-1] == Y[j-1]$, set `dp[i][j] = dp[i-1][j-1] + 1`.
     * Else, set `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
3. The length of the LCS is now stored in `dp[m][n]`.
4. To reconstruct the string, start at `i = m` and `j = n` and create an empty string `lcs_str`.
5. While `i > 0` and `j > 0`:
   * If $X[i-1] == Y[j-1]$, prepend $X[i-1]$ to `lcs_str`, and decrement both `i` and `j`.
   * Else if `dp[i-1][j] > dp[i][j-1]`, decrement `i`.
   * Else, decrement `j`.
6. Return `dp[m][n]` and the reconstructed `lcs_str`.

## Pseudocode

```
function LCS(X, Y, m, n):
    dp = 2D array of size (m+1) by (n+1) initialized to 0
    
    // Fill the DP table
    for i from 1 to m:
        for j from 1 to n:
            if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                
    length = dp[m][n]
    
    // Traceback to find the string
    lcs_str = empty string
    i = m, j = n
    
    while i > 0 and j > 0:
        if X[i-1] == Y[j-1]:
            prepend X[i-1] to lcs_str
            i = i - 1
            j = j - 1
        else if dp[i-1][j] > dp[i][j-1]:
            i = i - 1
        else:
            j = j - 1
            
    return length, lcs_str
```

## Complexity Analysis

### Time Complexity Derivation

* **Table Construction:** We use two nested loops to iterate through all possible prefixes of string $X$ (length $m$) and string $Y$ (length $n$). The operations inside the loop (comparisons and assignments) take $O(1)$ time. This step takes exactly $m \times n$ operations, resulting in $O(m \times n)$ time.
* **Traceback:** In the worst-case scenario, the traceback step moves from the bottom-right corner `(m, n)` to the top-left corner `(0, 0)` by decrementing either $i$ or $j$ or both at each step. The maximum number of steps is $m + n$. This takes $O(m + n)$ time.
* **Overall Time Complexity:** The table construction dominates the traceback phase, making the overall time complexity $O(m \times n) + O(m + n) \implies O(m \times n)$.

### Space Complexity Derivation

* **Auxiliary Space:** We allocate a 2-dimensional array `dp` of size $(m + 1) \times (n + 1)$ to store the subproblem lengths. We also allocate a character array of size $\max(m, n) + 1$ to store the reconstructed string.
* **Overall Space Complexity:** The 2D array is the dominant factor, resulting in a space complexity of $O(m \times n)$. *(Note: If only the length was required, the space complexity could be optimized to $O(\min(m, n))$ by keeping only the previous and current rows).*

## Sample Outputs

### Example 1

```
Enter first string: AGGTAB
Enter second string: GXTXAYB
Length of LCS: 4
The LCS is: GTAB
```

### Example 2

```
Enter first string: ABC
Enter second string: DEF
Length of LCS: 0
The LCS is: (none)
```