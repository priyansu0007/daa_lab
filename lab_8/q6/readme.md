# Question 6: Edit Distance with Traceback Information

## 1. Problem Statement
Given two strings A of length $m$ and B of length $n$, compute the minimum number of operations (insertions, deletions, or substitutions) required to transform A into B, and print the traceback result. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## 2. Approach
The problem is solved using **Dynamic Programming (DP)**. We construct a 2D table `dp` where `dp[i][j]` represents the minimum edit distance to transform the prefix of string A of length $i$ into the prefix of string B of length $j$.

1. **Base Cases:** 
   - Transforming any string of length $i$ to an empty string requires $i$ deletions.
   - Transforming an empty string to a string of length $j$ requires $j$ insertions.
2. **Recurrence Relation:**
   - If the current characters match (`A[i-1] == B[j-1]`), no new operation is needed. The cost is the same as the prefixes before these characters: `dp[i-1][j-1]`.
   - If they do not match, we take the minimum cost among three possible operations and add 1:
     - **Replace:** `dp[i-1][j-1] + 1`
     - **Delete (from A):** `dp[i-1][j] + 1`
     - **Insert (into A):** `dp[i][j-1] + 1`
3. **Traceback:** Once the table is filled, the minimum edit distance is found at `dp[m][n]`. To reconstruct the exact operations, we trace our path back from `dp[m][n]` to `dp[0][0]` by checking which neighbor cell (diagonal, top, or left) produced the optimal value for the current cell.

## 3. Algorithm
1. Read the input strings `A` and `B`, and calculate their lengths $m$ and $n$.
2. Initialize a 2D DP array of size $(m+1) \times (n+1)$.
3. Initialize the first column: `dp[i][0] = i` for all $0 \le i \le m$.
4. Initialize the first row: `dp[0][j] = j` for all $0 \le j \le n$.
5. Iterate `i` from $1$ to $m$:
   - Iterate `j` from $1$ to $n$:
     - If `A[i-1] == B[j-1]`, set `dp[i][j] = dp[i-1][j-1]`.
     - Else, set `dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])`.
6. Output `dp[m][n]` as the total minimum operations.
7. To traceback, initialize an empty operations array and set pointers $i = m, j = n$.
8. While $i > 0$ or $j > 0$:
   - If `A[i-1] == B[j-1]`, record "Match", decrement both $i$ and $j$.
   - Else if `dp[i][j] == dp[i-1][j-1] + 1`, record "Replace", decrement both $i$ and $j$.
   - Else if `dp[i][j] == dp[i-1][j] + 1`, record "Delete", decrement $i$.
   - Else, record "Insert", decrement $j$.
9. Print the recorded operations in reverse order (from start to finish).

## 4. Pseudocode
```text
function edit_distance(A, B):
    m = length(A)
    n = length(B)
    create table dp[m+1][n+1]

    for i from 0 to m: dp[i][0] = i
    for j from 0 to n: dp[0][j] = j

    for i from 1 to m:
        for j from 1 to n:
            if A[i-1] == B[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                dp[i][j] = 1 + min(
                    dp[i-1][j-1], // Replace
                    dp[i-1][j],   // Delete
                    dp[i][j-1]    // Insert
                )

    print "Distance: ", dp[m][n]

    i = m, j = n
    operations = []
    
    while i > 0 or j > 0:
        if i > 0 and j > 0 and A[i-1] == B[j-1]:
            operations.append("Match " + A[i-1])
            i = i - 1; j = j - 1
        else if i > 0 and j > 0 and dp[i][j] == dp[i-1][j-1] + 1:
            operations.append("Replace " + A[i-1] + " with " + B[j-1])
            i = i - 1; j = j - 1
        else if i > 0 and dp[i][j] == dp[i-1][j] + 1:
            operations.append("Delete " + A[i-1])
            i = i - 1
        else:
            operations.append("Insert " + B[j-1])
            j = j - 1

    reverse(operations)
    for op in operations: print op
```

## 5. Complexity Analysis

### Time Complexity Derivation
The total time complexity is the sum of the time required to initialize the base cases, fill the DP table, and perform the traceback.

1. **Base Cases Initialization:** Setting up the first row and column takes $O(m) + O(n)$ time.
2. **DP Table Construction:** We use two nested loops. The outer loop runs $m$ times, and the inner loop runs $n$ times. The work done inside the inner loop (comparisons and minimum calculations) takes constant time $O(1)$. 
   $$\text{Time for table} = \sum_{i=1}^{m} \sum_{j=1}^{n} O(1) = O(m \times n)$$
3. **Traceback:** The traceback starts at cell $(m, n)$. In each step, we either decrement $i$, decrement $j$, or decrement both. In the absolute worst case (e.g., all insertions or all deletions), we move along the edges of the grid, taking a maximum of $m + n$ steps. Thus, traceback takes $O(m + n)$ time.

Total Time Complexity:
$$O(m) + O(n) + O(m \times n) + O(m + n) = O(m \times n)$$

### Space Complexity Derivation
The total space complexity is the sum of the memory required for the 2D DP array and the auxiliary array used to store the traceback string.

1. **DP Table:** We allocate a 2D matrix of dimensions $(m+1) \times (n+1)$.
   $$\text{Total cells} = (m+1)(n+1) = mn + m + n + 1$$
   The memory scales proportionally with $m \times n$, resulting in $O(m \times n)$ space.
2. **Traceback Storage:** We store the sequence of operations before printing. As derived above, the maximum number of operations is $m + n$, meaning this auxiliary array takes $O(m + n)$ space.

Total Space Complexity:
$$O(mn + m + n + 1) + O(m + n) = O(m \times n)$$

## 6. Sample Outputs

**Test Case 1: Standard Transformation**
```text
Enter first string (A): kitten
Enter second string (B): sitting

Minimum Edit Distance: 3
Traceback Operations:
- Replace 'k' with 's'
- Match 'i'
- Match 't'
- Match 't'
- Replace 'e' with 'i'
- Match 'n'
- Insert 'g'
```

**Test Case 2: Complete Deletion**
```text
Enter first string (A): hello
Enter second string (B): 

Minimum Edit Distance: 5
Traceback Operations:
- Delete 'h'
- Delete 'e'
- Delete 'l'
- Delete 'l'
- Delete 'o'
```