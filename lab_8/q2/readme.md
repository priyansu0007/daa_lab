# Question 2: Coin Change - Total Number of Ways

## Directory Structure Context

This solution is located in the `q2` directory:

```
q2/
├── a.out
└── q2.c
```

## Problem Statement

Given an array of distinct positive integers representing coin denominations $C = \{c_1, c_2, \dots, c_n\}$ and a target amount $V$, find the total number of distinct combinations of coins that sum up to $V$. You may assume an infinite supply of each coin denomination. The order of coins does not matter (e.g., `1 + 2` and `2 + 1` are considered the same combination).

## Approach

This problem is solved using **Dynamic Programming (DP)**. We want to find combinations, which means the order in which we pick the coins does not matter. To avoid overcounting permutations (like counting `1+2` and `2+1` as separate ways), we must process the coins one by one.

We use a 1D array `dp` of size $V + 1$, where `dp[i]` represents the total number of ways to make the amount $i$. 

1. **Base Case:** There is exactly $1$ way to make the amount $0$, which is by choosing zero coins. Thus, `dp[0] = 1`.
2. We iterate through each coin denomination one at a time.
3. For a given coin, we iterate through all amounts from the coin's value up to the target amount $V$.
4. For each amount $i$, we add the number of ways to make the amount $(i - \text{coin})$ to our current `dp[i]`.

## Algorithm

1. Initialize an array `dp` of size $V + 1$ with all elements set to $0$.
2. Set the base case: `dp[0] = 1`.
3. Loop for each `coin` in the array $C$:
   * Loop for each amount `i` from `coin` up to $V$:
     * Update the number of ways: `dp[i] = dp[i] + dp[i - coin]`
4. The final answer for the target amount $V$ will be stored in `dp[V]`.

## Pseudocode

```
function totalWays(coins, n, V):
    dp = array of size V + 1, initialized to 0
    dp[0] = 1
    
    for i from 0 to n - 1:
        current_coin = coins[i]
        for j from current_coin to V:
            dp[j] = dp[j] + dp[j - current_coin]
            
    return dp[V]
```

## Complexity Analysis

### Time Complexity Derivation

* **Initialization:** Initializing the `dp` array takes $O(V)$ time.
* **Nested Loops:**
  * The outer loop iterates over each of the $n$ coin denominations.
  * The inner loop iterates from the value of the current coin up to the target amount $V$. In the worst-case scenario (if a coin value is $1$), this inner loop runs $V$ times.
  * The operation inside the inner loop is a basic arithmetic addition, which takes constant $O(1)$ time.
  * Therefore, the nested loops execute a maximum of $n \times V$ times.
* **Overall Time Complexity:** Combining the steps, $O(V) + O(n \times V)$ simplifies to $O(n \times V)$.

### Space Complexity Derivation

* **Auxiliary Space:** We allocate a single 1-dimensional array `dp` of size $V + 1$ to store the number of ways to make each intermediate amount. We must use a sufficiently large data type (like `long long` in C) as the number of combinations can grow exponentially large, but the array size remains directly proportional to $V$.
* **Overall Space Complexity:** $O(V)$.

## Sample Outputs

### Example 1 (Multiple Combinations)

```
Enter number of coins: 3
Enter the coins: 1 2 5
Enter target amount: 5
Total number of ways: 4
```

*(Explanation: The 4 distinct ways are: `5`, `2+2+1`, `2+1+1+1`, and `1+1+1+1+1`)*

### Example 2 (No Combinations)

```
Enter number of coins: 1
Enter the coins: 2
Enter target amount: 3
Total number of ways: 0
```

*(Explanation: It is impossible to make an odd amount using only coins of value 2.)*