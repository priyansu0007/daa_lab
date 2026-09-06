# DAA Lab 6 - Question 1: Nth Fibonacci Number

## Problem Statement
Write a program to find the $n$-th Fibonacci number using Dynamic Programming.

---

## Approach
The program demonstrates the principles of Dynamic Programming (DP) to optimize the naive recursive approach for calculating Fibonacci numbers, which normally has an exponential time complexity. The code explores two DP strategies:

1.  **Memoization (Top-Down):** The `fibTab` function attempts a top-down approach by caching previously calculated Fibonacci values in an array (`mem`). This ensures that each state is computed only once. *(Note: In standard C implementations, this memoization array is typically passed as an argument or declared globally/statically to persist across recursive calls).*
2.  **Space-Optimized Tabulation (Bottom-Up):** The `fibo` function (which is executed in `main`) uses a highly optimized bottom-up iterative approach. Instead of maintaining an entire table (array) of size $n$, it recognizes that calculating the current Fibonacci number only requires the previous two values. It strictly maintains a `prev1` and `prev2` variable, continuously updating them to reach the $n$-th number.

---

## Algorithm / Pseudocode

```text
// Approach 1: Memoization (Top-Down)
procedure FibonacciMemo(n, mem[]):
    if n <= 1: return n
    
    if mem[n] is not empty: 
        return mem[n]
        
    mem[n] = FibonacciMemo(n - 1, mem) + FibonacciMemo(n - 2, mem)
    return mem[n]

// Approach 2: Space-Optimized Tabulation (Bottom-Up)
procedure FibonacciOptimized(n):
    if n <= 1: return n
    
    prev2 = 0
    prev1 = 1
    
    for i = 2 to n:
        curr = prev2 + prev1
        prev2 = prev1
        prev1 = curr
        
    return curr
```

---

## Complexity Analysis

### Time Complexity
*   **Both Approaches:** $O(n)$ - Whether using recursion with memoization or iterative tabulation, the algorithm calculates each Fibonacci number from $2$ to $n$ exactly once.

### Space Complexity
*   **Memoization (`fibTab` conceptual):** $O(n)$ - Requires an array of size $n$ to store the cached values, plus $O(n)$ space on the call stack due to recursion depth.
*   **Space-Optimized Tabulation (`fibo`):** $O(1)$ - The iterative approach only utilizes three integer variables (`prev1`, `prev2`, and `curr`), requiring constant extra space regardless of the input size $n$. This is the optimal space complexity for this problem.

---

## Sample Output

```text
Enter the value of n: 10
Fibo: 55
```