# Question 5: Maximum Sum Increasing Subsequence

## Directory Structure Context

This solution is located in the `q5` directory:

```
q5/
├── a.out
└── q5.c
```

## Problem Statement

Given an array of $n$ positive integers $A = [a_0, a_1, \dots, a_{n-1}]$, find the maximum possible sum of a strictly increasing subsequence. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

## Approach

This problem is a variation of the Longest Increasing Subsequence (LIS) problem and can be solved efficiently using **Dynamic Programming**. 

Instead of keeping track of the maximum length of an increasing subsequence, we keep track of the maximum *sum* of an increasing subsequence ending at each index. We create a `dp` array where `dp[i]` stores the maximum sum of an increasing subsequence that strictly ends with the element $a_i$. 

For every element $a_i$, we look back at all previous elements $a_j$ (where $j < i$). If $a_i$ is strictly greater than $a_j$, it means $a_i$ can extend the increasing subsequence ending at $a_j$. We then update `dp[i]` to be the maximum of its current value or `dp[j] + a_i`.

## Algorithm

1. Read the number of elements $n$.
2. If $n \le 0$, the maximum sum is $0$.
3. Read the elements into an array `arr`.
4. Create a dynamic programming array `dp` of size $n$.
5. Initialize `dp[i] = arr[i]` for all $0 \le i < n$. This is the base case, as every single element forms an increasing subsequence of its own sum.
6. Loop `i` from 1 to $n-1$:
   * Loop `j` from 0 to $i-1$:
     * If `arr[i] > arr[j]` AND `dp[i] < dp[j] + arr[i]`:
       * Update `dp[i] = dp[j] + arr[i]`.
7. Initialize `max_sum = 0`.
8. Loop through the `dp` array to find the maximum value.
9. Return `max_sum`.

## Pseudocode

```
function max_sum_increasing_subsequence(arr, n):
    if n <= 0:
        return 0
        
    let dp be an array of size n
    
    // Base case initialization
    for i from 0 to n-1:
        dp[i] = arr[i]
        
    // DP transition
    for i from 1 to n-1:
        for j from 0 to i-1:
            if arr[i] > arr[j] and dp[i] < dp[j] + arr[i]:
                dp[i] = dp[j] + arr[i]
                
    // Find the global maximum
    max_sum = 0
    for i from 0 to n-1:
        if dp[i] > max_sum:
            max_sum = dp[i]
            
    return max_sum
```

## Complexity Analysis

### Time Complexity Derivation

* The algorithm utilizes two nested loops. 
* The outer loop runs from $1$ to $n-1$.
* The inner loop runs from $0$ to $i-1$. 
* Total number of iterations for the inner loop is $1 + 2 + 3 + \dots + (n-1)$, which is an arithmetic progression summing to $\frac{n(n-1)}{2}$. 
* Dropping the constants and lower-order terms, the derived time complexity is **$O(n^2)$**.

### Space Complexity Derivation

* The algorithm requires a 1-dimensional dynamic programming array (`dp`) of size $n$ to store the maximum sums of increasing subsequences ending at each index. 
* Therefore, the overall space complexity is **$O(n)$**.

## Sample Outputs

### Example 1

```
Enter number of elements: 7
Enter the elements: 1 101 2 3 100 4 5
Maximum sum of increasing subsequence: 106
```
*(Explanation: The subsequence is 1, 2, 3, 100 which sums to 106)*

### Example 2

```
Enter number of elements: 5
Enter the elements: 10 5 4 3 2
Maximum sum of increasing subsequence: 10
```
*(Explanation: The array is strictly decreasing, so the max sum is just the largest single element, 10)*