# k-Sum Target Finder

## Overview
This program solves the **k-Sum problem**: determining if there is a combination of exactly $k$ elements within an array that add up to a specific target sum, $T$. It leverages a recursive reduction strategy combined with efficient searching to answer the query.

## Approach
To avoid deeply nested loops that are rigid and hard to write dynamically for an arbitrary $k$, this algorithm relies on recursion:
1. **Sorting:** The array is first sorted in ascending order using **Merge Sort**. Sorting is critical as it sets up the array for efficient searching at the final step.
2. **Recursive Reduction:** The core logic reduces the $k$-Sum problem to a $(k-1)$-Sum problem. By iterating through the array and subtracting the current element's value from the target, we look for $k-1$ elements that sum to the new reduced target.
3. **Base Case (Binary Search):** When $k$ is reduced to $1$, the problem simplifies to finding a single specific value in the remaining subarray. Since the array is already sorted, we can use **Binary Search** to find it efficiently.

## Algorithm
1. Read the array size $n$ and dynamically allocate memory for it.
2. Populate the array with user input, then read the target sum $T$ and the number of elements $k$.
3. Sort the array using Merge Sort.
4. Call the recursive function `kSum(arr, n, k, start_index, target)`.
5. **Inside `kSum`:**
   * If $k = 1$, execute Binary Search to find the `target` in the subarray from `start_index` to $n-1$. Return `true` if found.
   * If $k > 1$, loop `i` from `start_index` to $n - k$.
   * Make a recursive call: `kSum(arr, n, k - 1, i + 1, target - arr[i])`.
   * If any recursive call returns `true`, propagate `true` upwards.
6. Print the final result (YES/NO) and free allocated memory.

## Pseudocode
```text
function kSum(arr, n, k, start_index, target):
    if k == 1:
        return binarySearch(arr, start_index, n - 1, target)

    for i from start_index to n - k:
        new_target = target - arr[i]
        if kSum(arr, n, k - 1, i + 1, new_target) is true:
            return true
            
    return false
```

## Complexity Analysis
* **Time Complexity:** $O(N^{k-1} \log N)$
  * The recursive function creates a branching tree of depth $k-1$. In the worst case, iterating through the elements forms roughly $O(N^{k-1})$ paths. At the leaf nodes (when $k=1$), a Binary Search takes $O(\log N)$ time.
* **Space Complexity:** $O(N + k)$
  * Merge Sort requires $O(N)$ auxiliary space for merging. The recursive call stack for the `kSum` function reaches a maximum depth of $k$, taking $O(k)$ space. Overall, this simplifies to $O(N)$ since $k$ is generally less than or equal to $N$.

## Sample Output
```text
Enter the value of n: 5
Enter element 1: 3
Enter element 2: 7
Enter element 3: 1
Enter element 4: 9
Enter element 5: 4
Enter the value of target sum (T): 14
Enter the value of elements to sum (k): 3

Sorted Array: 1 3 4 7 9 

Result: YES, there are 3 elements that sum up to 14.
```
