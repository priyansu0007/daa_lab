# Question 8: Optimal Binary Search Trees (OBST)

## 1. Problem Statement
Given a set of $n$ distinct sorted keys $K = [k_1, k_2, \dots, k_n]$ with search probabilities $p_1, p_2, \dots, p_n$, and $n+1$ dummy keys $d_0, d_1, \dots, d_n$ representing searches not in $K$ with probabilities $q_0, q_1, \dots, q_n$, find the minimum expected search cost of a binary search tree. By choosing the proper input representation, write a program in C to validate your procedures and derive the complexity analysis of your algorithm.

## 2. Approach
The problem is solved using **Dynamic Programming**. We construct the optimal binary search tree bottom-up by solving subproblems for smaller sequences of keys and combining them.

1. **State Definition:** 
   - `e[i][j]` stores the minimum expected cost of a BST containing real keys $k_i \dots k_j$ and dummy keys $d_{i-1} \dots d_j$.
   - `w[i][j]` stores the sum of all probabilities in the subtree containing keys $k_i \dots k_j$ and dummy keys $d_{i-1} \dots d_j$.
2. **Base Cases:** 
   - When a subtree contains no real keys (only a dummy key $d_{i-1}$), the expected cost is just the probability of searching for that dummy key: `e[i][i-1] = q[i-1]`.
   - The weight is also just the dummy key's probability: `w[i][i-1] = q[i-1]`.
3. **Recurrence Relation:** 
   - For a sequence of keys $k_i \dots k_j$, we calculate the weight as:
     $$w[i][j] = w[i][j-1] + p[j] + q[j]$$
   - We try making every key $k_r$ (where $i \le r \le j$) the root. When $k_r$ becomes the root, the expected cost is the cost of the left subtree, plus the right subtree, plus the weight of the entire current tree (because pushing subtrees down one level adds their total weight to the expected cost):
     $$e[i][j] = \min_{i \le r \le j} ( e[i][r-1] + e[r+1][j] + w[i][j] )$$

## 3. Algorithm
1. Read the number of keys $n$.
2. Read the successful search probabilities array $p$ (1-indexed, $p_1$ to $p_n$).
3. Read the unsuccessful search probabilities array $q$ (0-indexed, $q_0$ to $q_n$).
4. Initialize 2D DP arrays `e` and `w` of size $(n+2) \times (n+2)$.
5. Set the base cases: Loop `i` from 1 to $n+1$, setting `e[i][i-1] = q[i-1]` and `w[i][i-1] = q[i-1]`.
6. Loop `len` from 1 to $n$ (representing the number of keys in the current sequence):
   - Loop `i` from 1 to $n - len + 1$ (the starting index):
     - Calculate ending index: `j = i + len - 1`.
     - Initialize `e[i][j]` to infinity (a very large number).
     - Calculate `w[i][j] = w[i][j-1] + p[j] + q[j]`.
     - Loop `r` from $i$ to $j$ (trying every root):
       - Calculate `cost = e[i][r-1] + e[r+1][j] + w[i][j]`.
       - If `cost < e[i][j]`, update `e[i][j] = cost`.
7. Output `e[1][n]` as the total minimum expected search cost.

## 4. Pseudocode
```text
function obst(p, q, n):
    create tables e[1..n+2][0..n+1], w[1..n+2][0..n+1]
    
    // Base cases
    for i from 1 to n+1:
        e[i][i-1] = q[i-1]
        w[i][i-1] = q[i-1]
        
    // DP transitions
    for len from 1 to n:
        for i from 1 to n - len + 1:
            j = i + len - 1
            e[i][j] = infinity
            w[i][j] = w[i][j-1] + p[j] + q[j]
            
            for r from i to j:
                cost = e[i][r-1] + e[r+1][j] + w[i][j]
                if cost < e[i][j]:
                    e[i][j] = cost
                    
    print "Minimum Expected Cost: ", e[1][n]
```

## 5. Complexity Analysis

### Time Complexity Derivation
The time complexity is determined by the three nested loops used to fill the DP tables.
1. The outer loop (`len`) runs $n$ times.
2. The middle loop (`i`) runs $n - len + 1$ times.
3. The innermost loop (`r`) iterates from $i$ to $i + len - 1$, meaning it runs $len$ times.

The total number of iterations can be expressed as:
$$\text{Total Operations} = \sum_{len=1}^{n} \sum_{i=1}^{n - len + 1} len$$

Since the innermost loop runs $len$ times, and the middle loop runs approximately $n$ times, the sum roughly evaluates to:
$$\sum_{len=1}^{n} (n - len + 1) \cdot len \approx \int_{0}^{n} (n - x)x \, dx = \left[ \frac{nx^2}{2} - \frac{x^3}{3} \right]_0^n = \frac{n^3}{2} - \frac{n^3}{3} = \frac{n^3}{6}$$

Dropping the constant fraction, the resulting time complexity is:
$$O(n^3)$$

*(Note: This can be optimized to $O(n^2)$ using Knuth's Optimization, but the standard DP formulation yields $O(n^3)$).*

### Space Complexity Derivation
The space complexity is defined by the memory required to store the dynamic programming tables.
1. `e` table: A 2D array of size $(n+2) \times (n+2)$.
2. `w` table: A 2D array of size $(n+2) \times (n+2)$.

Total memory cells allocated:
$$2 \times (n+2)^2 = 2(n^2 + 4n + 4)$$

Dropping the constants and lower-order terms, the space complexity scales quadratically with $n$:
$$O(n^2)$$

## 6. Sample Outputs

**Test Case 1:**
```text
Enter number of distinct keys (n): 2
Enter the 2 successful search probabilities (p1 to pn): 0.15 0.10
Enter the 3 unsuccessful search probabilities (q0 to qn): 0.05 0.10 0.05

Minimum Expected Search Cost: 1.2000
```