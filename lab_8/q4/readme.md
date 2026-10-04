# Question 4: Longest Increasing Subsequence (LIS)

## Directory Structure Context

This solution is located in the `q4` directory:

```
q4/
├── a.out
└── q4.c

```

## Problem Statement

Given an integer array $A = [a_0, a_1, \dots, a_{n-1}]$, find the length of the longest subsequence such that all elements of the subsequence are strictly increasing. A subsequence is derived by deleting zero or more elements from the array without changing the relative order of the remaining elements.

## Approach

We can solve this problem using **Dynamic Programming (DP)**. The core idea is to find the longest increasing subsequence that ends at each specific index in the array, and then find the maximum among all these lengths.

1. **State Definition:** Let `dp[i]` be the length of the longest strictly increasing subsequence that ends exactly at index `i`.

2. **Base Case:** Every single element is trivially an increasing subsequence of length $1$. Therefore, we initialize `dp[i] = 1` for all $i$ from $0$ to $n-1$.

3. **Recursive Step:** To calculate `dp[i]`, we look at all previous elements at indices $j$ (where $0 \le j < i$). If the current element $A[i]$ is strictly greater than a previous element $A[j]$, it means $A[i]$ can extend the increasing subsequence ending at $A[j]$. Thus, we update `dp[i]` to be the maximum of its current value or `dp[j] + 1`.

4. **Final Result:** The longest increasing subsequence could end at any index, so the final answer is the maximum value found in the entire `dp` array.

## Algorithm

1. If the array size $n$ is $0$, return $0$.

2. Initialize an array `dp` of size $n$, setting all elements to $1$.

3. Loop `i` from $1$ to $n - 1$:

   * Loop `j` from $0$ to $i - 1$:

     * If $A[i] > A[j]$ and `dp[i] < dp[j] + 1`:

       * Update `dp[i] = dp[j] + 1`.

4. Initialize `max_len = 0`.

5. Loop `i` from $0$ to $n - 1$:

   * If `dp[i] > max_len`:

     * Update `max_len = dp[i]`.

6. Return `max_len`.

## Pseudocode

```
function LIS(A, n):
    if n == 0:
        return 0
        
    dp = array of size n, initialized to 1
    
    for i from 1 to n - 1:
        for j from 0 to i - 1:
            if A[i] > A[j]:
                dp[i] = max(dp[i], dp[j] + 1)
                
    max_len = 0
    for i from 0 to n - 1:
        if dp[i] > max_len:
            max_len = dp[i]
            
    return max_len

```

## Complexity Analysis

### Time Complexity Derivation

* **Initialization:** Initializing the `dp` array takes $O(n)$ time.

* **Nested Loops:** 
  * The outer loop runs $n-1$ times.
  * For each iteration $i$, the inner loop runs exactly $i$ times. 
  * The total number of inner loop executions is the sum of the first $n-1$ integers: $1 + 2 + 3 + \dots + (n-1) = \frac{n(n-1)}{2}$.
  * The operations inside the inner loop take $O(1)$ constant time.
  * Therefore, the nested loops take $O(n^2)$ time.

* **Finding the Maximum:** The final scan through the `dp` array takes $O(n)$ time.

* **Overall Time Complexity:** $O(n) + O(n^2) + O(n) \implies O(n^2)$. *(Note: A more advanced approach using Binary Search can reduce this to $O(n \log n)$, but DP is $O(n^2)$).*

### Space Complexity Derivation

* **Auxiliary Space:** We allocate a single 1-dimensional array `dp` of size $n$ to store the length of the LIS ending at each respective index.

* **Overall Space Complexity:** The memory required is strictly proportional to the size of the input array, resulting in a space complexity of $O(n)$.

## Sample Outputs

### Example 1 (Standard Input)

```
Enter number of elements: 8
Enter the elements: 10 9 2 5 3 7 101 18
Length of Longest Increasing Subsequence: 4

```

*(Explanation: The longest increasing subsequence is [2, 3, 7, 101] or [2, 5, 7, 101], both of length 4.)*

### Example 2 (Strictly Decreasing Input)

```
Enter number of elements: 5
Enter the elements: 5 4 3 2 1
Length of Longest Increasing Subsequence: 1

```

*(Explanation: No elements can be chained in increasing order, so the longest subsequence is just a single element.)*