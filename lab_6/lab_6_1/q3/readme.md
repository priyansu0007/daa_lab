# DAA Lab 6 - Question 3: Longest Common Subsequence (LCS)

## Problem Statement
Implement the Longest Common Subsequence (LCS) algorithm using Dynamic Programming. Given two strings, find the length of their longest common subsequence and display the subsequence. Analyze the complexity of the algorithm.

---

## Approach
The program uses a **Bottom-Up Dynamic Programming** approach to find both the length of the LCS and the sequence itself. The solution is divided into two main phases:

1.  **Table Construction:** A 2D array `dp` of size $(m+1) \times (n+1)$ is built, where $m$ and $n$ are the lengths of the two strings, $X$ and $Y$. The cell `dp[i][j]` represents the length of the LCS for the prefixes $X[0 \dots i-1]$ and $Y[0 \dots j-1]$. 
    *   If the characters match ($X[i-1] == Y[j-1]$), the length increases by 1 from the previous diagonal cell: `dp[i-1][j-1] + 1`.
    *   If they do not match, the value is the maximum of excluding the current character from either string: `max(dp[i-1][j], dp[i][j-1])`.
2.  **Backtracking:** To display the actual subsequence, the algorithm starts from the bottom-right corner of the table (`dp[m][n]`) and traces its way back to the top-left. If the characters match, they are added to the result string and the path moves diagonally. If they don't, the path moves in the direction of the larger adjacent value (up or left).

---

## Algorithm / Pseudocode
```text
procedure LCS(X, Y):
    m = length of X
    n = length of Y
    Create 2D array dp of size (m+1) x (n+1)

    // Phase 1: Build the DP Table
    for i = 0 to m:
        for j = 0 to n:
            if i == 0 or j == 0:
                dp[i][j] = 0
            else if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])

    // Phase 2: Backtrack to find the sequence
    index = dp[m][n]
    Create array lcs_str of size index + 1
    lcs_str[index] = '\0'
    
    i = m, j = n
    while i > 0 and j > 0:
        if X[i-1] == Y[j-1]:
            lcs_str[index-1] = X[i-1]
            i--, j--, index--
        else if dp[i-1][j] > dp[i][j-1]:
            i--
        else:
            j--

    print "Length: ", dp[m][n]
    print "Subsequence: ", lcs_str