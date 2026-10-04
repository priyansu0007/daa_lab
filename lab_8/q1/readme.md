# Question 1: Minimum Coin Change

## Directory Structure Context
This solution is located in the `q1` directory:
```text
q1/
├── a.out
└── q1.c
```

## Problem Statement
Given an integer array of coin denominations $C = \{c_1, c_2, \dots, c_n\}$ representing coins of different values, and an integer target amount $V$, find the minimum number of coins needed to make up that amount. You may assume an infinite supply of each coin denomination. If that amount of money cannot be made up by any combination of the coins, return `-1`.

## Approach
This problem can be optimally solved using **Dynamic Programming (DP)**. A greedy approach (picking the largest coin first) does not always yield the minimum number of coins for arbitrary denominations. 

We can build the solution in a bottom-up manner. We will define an array `dp` of size $V + 1$, where `dp[i]` stores the minimum number of coins needed to make the amount $i$. 
1. We know the base case: to make an amount of `0`, we need `0` coins. Thus, `dp[0] = 0`.
2. For all other amounts from `1` to $V$, we initially set the required coins to a very large number (acting as infinity).
3. We then iterate through each amount up to $V$. For each amount, we check every available coin denomination. If the coin is smaller than or equal to the current amount, we check if using this coin gives us a smaller coin count than what we currently have recorded.

## Algorithm
1. Initialize an array `dp` of size $V + 1$.
2. Set `dp[0] = 0`.
3. Set all other elements in `dp` from index `1` to $V$ to a large value (e.g., $V + 1$ or infinity).
4. Loop `i` from `1` to $V$:
   - Loop `j` from `0` to $n - 1$ (where $n$ is the number of coins):
     - If `coins[j] <= i`:
       - `dp[i] = min(dp[i], dp[i - coins[j]] + 1)`
5. After the loops, check if `dp[V]` is still the large initialized value.
   - If yes, it means the amount cannot be formed, so return `-1`.
   - If no, return `dp[V]`.

## Pseudocode
```text
function minCoins(coins, n, V):
    dp = array of size V + 1
    dp[0] = 0
    
    for i from 1 to V:
        dp[i] = V + 1  // Initialize to "infinity"
        
    for i from 1 to V:
        for j from 0 to n - 1:
            if coins[j] <= i:
                sub_res = dp[i - coins[j]]
                if sub_res != V + 1 and sub_res + 1 < dp[i]:
                    dp[i] = sub_res + 1
                    
    if dp[V] > V:
        return -1
    else:
        return dp[V]
```

## Complexity Analysis

### Time Complexity Derivation
*   **Initialization:** Initializing the `dp` array takes $O(V)$ time.
*   **Nested Loops:** 
    *   The outer loop runs from $1$ to $V$, which is exactly $V$ iterations.
    *   For each iteration of the outer loop, the inner loop iterates through all the coin denominations, which is $n$ iterations.
    *   Inside the inner loop, we perform constant time $O(1)$ operations (comparisons and additions).
    *   Therefore, the nested loops take $V \times n$ operations.
*   **Overall Time Complexity:** Adding it up, $O(V) + O(n \times V)$ simplifies strictly to **$O(n \times V)$**.

### Space Complexity Derivation
*   **Auxiliary Space:** We allocate a 1-dimensional integer array `dp` of size $V + 1$ to store the subproblem results. 
*   **Overall Space Complexity:** The memory used scales linearly with the target amount, resulting in a space complexity of **$O(V)$**.

## Sample Outputs

### Example 1 (Success)
```text
Enter number of coins: 3
Enter the coins: 1 2 5
Enter target amount: 11
Min coins needed: 3
```
*(Explanation: 11 = 5 + 5 + 1. 3 coins total.)*

### Example 2 (Failure)
```text
Enter number of coins: 1
Enter the coins: 2
Enter target amount: 3
Output: -1
```
*(Explanation: You cannot make 3 using only coins of value 2.)*