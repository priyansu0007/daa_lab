# DAA Lab 5 - Question 1: Find Median Without Sorting

## Problem Statement
Find the median of a list of N numbers without sorting the list. Do the complexity analysis of your algorithm.

## Approach
To find the median without fully sorting the array, we can use the **QuickSelect** algorithm. QuickSelect is a selection algorithm to find the $k$-th smallest element in an unordered list. It operates similarly to QuickSort, choosing a pivot and partitioning the array. However, instead of recursing into both sides of the partition, QuickSelect only recurses into the side that contains the $k$-th element. This approach reduces the average time complexity from $O(N \log N)$ (for full sorting) to $O(N)$.

For finding the median:
- If $N$ is odd, the median is the $(N/2)$-th smallest element (using 0-based indexing).
- If $N$ is even, the median is the average of the $((N-1)/2)$-th and $(N/2)$-th smallest elements.

## Algorithm
1. **Partitioning**: Choose a pivot (the rightmost element in this implementation). Rearrange the array such that all elements less than the pivot are placed before it, and all elements greater are placed after it. Return the final index of the pivot (`part`).
2. **QuickSelect**:
   - If the desired index `k` equals `part`, the pivot is the $k$-th smallest element. Return it.
   - If `k < part`, the $k$-th smallest element lies in the left partition. Recursively call QuickSelect on the left subarray.
   - If `k > part`, the $k$-th smallest element lies in the right partition. Recursively call QuickSelect on the right subarray.
3. **Find Median**:
   - If $N$ is odd, return `QuickSelect(arr, 0, N-1, N/2)`.
   - If $N$ is even, compute `mid1 = QuickSelect(arr, 0, N-1, N/2)` and `mid2 = QuickSelect(arr, 0, N/2 - 1, (N-1)/2)`, and return their average.

## Pseudocode
```text
procedure QuickSelect(arr, left, right, k):
    if left == right:
        return arr[left]
        
    part = Partition(arr, left, right)
    
    if part == k:
        return arr[part]
    else if k < part:
        return QuickSelect(arr, left, part - 1, k)
    else:
        return QuickSelect(arr, part + 1, right, k)

procedure Partition(arr, left, right):
    pivot = arr[right]
    i = left
    for j = left to right - 1:
        if arr[j] < pivot:
            swap arr[i] and arr[j]
            i = i + 1
    swap arr[i] and arr[right]
    return i

procedure FindMedian(arr, n):
    if n is odd:
        return QuickSelect(arr, 0, n - 1, n / 2)
    else:
        mid1 = QuickSelect(arr, 0, n - 1, n / 2)
        mid2 = QuickSelect(arr, 0, n / 2 - 1, (n - 1) / 2)
        return (mid1 + mid2) / 2.0
```

## Complexity Analysis

### Time Complexity
*   **Best Case:** $O(N)$
    In the best-case scenario, the chosen pivot always partitions the array exactly in half. 
    The recurrence relation is $T(N) = T(N/2) + O(N)$. 
    By the Master Theorem, this evaluates to $T(N) = O(N)$.
*   **Average Case:** $O(N)$
    On average, assuming elements are random, the partition will be reasonably balanced. The expected time taken by QuickSelect is mathematically bounded by $O(N)$.
*   **Worst Case:** $O(N^2)$
    The worst-case occurs when the pivot chosen is always the maximum or minimum element (e.g., if the array is already sorted and we always pick the last element). 
    The recurrence relation becomes $T(N) = T(N-1) + O(N)$, leading to an arithmetic progression sum which is $O(N^2)$. *(Note: This can be mitigated to $O(N)$ worst-case by using the Median of Medians algorithm to select the pivot).*

### Space Complexity
*   **Best / Average Case:** $O(\log N)$
    The algorithm works in-place (no auxiliary array), but the recursive calls use space on the call stack. A balanced partition tree has a depth of $\log N$.
*   **Worst Case:** $O(N)$
    If the partitions are highly unbalanced (worst-case time complexity), the maximum depth of the recursion tree becomes $N$, requiring $O(N)$ stack space.

## Sample Output

### Test Case 1 (Odd Number of Elements)
```text
Enter the value of n: 5
Enter the element: 9
Enter the element: 2
Enter the element: 7
Enter the element: 4
Enter the element: 5
Median: 5.00
```

### Test Case 2 (Even Number of Elements)
```text
Enter the value of n: 6
Enter the element: 10
Enter the element: 40
Enter the element: 20
Enter the element: 60
Enter the element: 30
Enter the element: 50
Median: 35.00
```
