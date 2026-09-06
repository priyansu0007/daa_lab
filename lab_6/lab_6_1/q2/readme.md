# DAA Lab 6 - Question 2: 0/1 Knapsack Problem

## Problem Statement
Implement the 0/1 Knapsack problem using Dynamic Programming. Given $n$ items with their weights and profits and a knapsack of capacity $W$, determine the maximum profit that can be obtained. Analyze the time and space complexity of your algorithm.

---

## Approach
The program uses a **Bottom-Up Dynamic Programming** approach to systematically build a solution. It avoids the exponential time complexity of the naive recursive approach (which recalculates overlapping subproblems) by storing intermediate results in a 2D table. 

A 2D array `dp` of size $(n+1) \times (W+1)$ is constructed, where `dp[i][w]` represents the maximum profit that can be achieved using a subset of the first `i` items with a maximum weight capacity of `w`. 
For each item, the algorithm makes a choice:
1.  **Exclude the item:** The profit remains the same as it was for the previous `i - 1` items at the current capacity `w`.
2.  **Include the item:** The profit becomes the item's profit plus the maximum profit achievable with the remaining capacity `w - weights[i - 1]`.
The algorithm takes the maximum of these two choices to populate the table.

---

## Algorithm / Pseudocode
```text
procedure Knapsack(W, weights[], profits[], n):
    // Create a 2D DP table of size (n + 1) x (W + 1)
    Let dp[n + 1][W + 1] be a new 2D array
    
    for i = 0 to n:
        for w = 0 to W:
            // Base case: 0 items or 0 capacity yields 0 profit
            if i == 0 or w == 0:
                dp[i][w] = 0
                
            // If the current item's weight fits in the current capacity
            else if weights[i - 1] <= w:
                include_profit = profits[i - 1] + dp[i - 1][w - weights[i - 1]]
                exclude_profit = dp[i - 1][w]
                dp[i][w] = max(include_profit, exclude_profit)
                
            // If the current item is too heavy, exclude it
            else:
                dp[i][w] = dp[i - 1][w]
                
    // The bottom-right cell contains the maximum profit
    return dp[n][W]
```

---

## Complexity Analysis

### Time Complexity
*   **$O(n \times W)$**: The algorithm utilizes two nested loops. The outer loop iterates $n + 1$ times (for each item), and the inner loop iterates $W + 1$ times (for each capacity unit up to the maximum capacity). The operations inside the loop take constant $O(1)$ time. Thus, the overall time complexity is strictly proportional to the number of items multiplied by the knapsack capacity.

### Space Complexity
*   **$O(n \times W)$**: The dynamic programming implementation requires allocating a 2D array `dp` of dimensions $(n + 1)$ by $(W + 1)$ to store the computed profits for all subproblems. 
*   *Optimization Note:* This can theoretically be optimized to $O(W)$ space. Since the current row `dp[i]` only ever requires data from the immediately preceding row `dp[i - 1]`, you only need to store a 1D array of size $W + 1$ and traverse it backwards.

---

## Sample Output
*(Based on the hardcoded inputs: profits = {60, 100, 120}, weights = {10, 20, 30}, W = 50)*

```text
Maximum profit obtained: 220
```