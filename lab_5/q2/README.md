# DAA Lab 5 - Question 2: Find the K'th Smallest Element

## Problem Statement
Find the K'th smallest element in a given list of N numbers without sorting the list. Do the complexity analysis of your algorithm.

## Approach
To efficiently find the K'th smallest element without sorting the entire array, we use the **QuickSelect** algorithm. QuickSelect is a selection algorithm that works similarly to the QuickSort algorithm. 

Instead of recursively sorting both sides of the partitioned array, QuickSelect determines which side of the partition contains the $K$-th smallest element and only recurses into that specific half. This eliminates the need to do extra work on the irrelevant half, reducing the average time complexity from $O(N \log N)$ (required for a full sort) down to $O(N)$. Since array indices are 0-based, the K'th smallest element corresponds to the index `K - 1`.

## Algorithm
1. **Partitioning**: 
   - Choose a pivot element (the rightmost element in this implementation).
   - Rearrange the array so that all elements smaller than the pivot come before it, and all elements greater come after it.
   - Return the final, correct index of this pivot (let's call it `part`).
2. **QuickSelect Recursive Step**:
   - If `part == k - 1`, the pivot is exactly the K'th smallest element. Return the pivot.
   - If `k - 1 < part`, the K'th smallest element must be in the left sub-array. Recursively call QuickSelect on the range `[left, part - 1]`.
   - If `k - 1 > part`, the K'th smallest element must be in the right sub-array. Recursively call QuickSelect on the range `[part + 1, right]`.

## Pseudocode
```text
procedure QuickSelect(arr, left, right, k_index):
    if left == right:
        return arr[left]
        
    part = Partition(arr, left, right)
    
    if part == k_index:
        return arr[part]
    else if k_index < part:
        return QuickSelect(arr, left, part - 1, k_index)
    else:
        return QuickSelect(arr, part + 1, right, k_index)

procedure Partition(arr, left, right):
    pivot = arr[right]
    i = left
    for j = left to right - 1:
        if arr[j] < pivot:
            swap arr[i] and arr[j]
            i = i + 1
    swap arr[i] and arr[right]
    return i

procedure FindKthSmallest(arr, n, k):
    // k is 1-based index, so we look for k-1
    return QuickSelect(arr, 0, n - 1, k - 1)
```

## Complexity Analysis

### Time Complexity
*   **Best Case:** $O(N)$
    In the best-case scenario, the chosen pivot perfectly splits the array into two equal halves at each step. The recurrence relation is $T(N) = T(N/2) + O(N)$. According to the Master Theorem, this results in a time complexity of $O(N)$.
*   **Average Case:** $O(N)$
    On average, for randomly distributed elements, the pivot will partition the array proportionally. The expected number of comparisons is bounded by a linear function, resulting in $O(N)$ average time complexity.
*   **Worst Case:** $O(N^2)$
    The worst-case occurs when the algorithm consistently picks the worst possible pivot (e.g., the largest or smallest element) in every recursive step. This happens if the array is already sorted (or reverse sorted) and the pivot is strictly chosen as the last element. The recurrence relation becomes $T(N) = T(N-1) + O(N)$, leading to $O(N^2)$ operations.

### Space Complexity
*   **Best / Average Case:** $O(\log N)$
    The algorithm is strictly an in-place modification of the array, meaning auxiliary array space is $O(1)$. However, the recursion stack uses memory. In the best and average cases, the recursion tree height is logarithmic, resulting in $O(\log N)$ space.
*   **Worst Case:** $O(N)$
    In the highly unbalanced worst-case scenario (where time complexity degrades to $O(N^2)$), the recursion tree becomes skewed and reaches a depth of $N$, requiring $O(N)$ space on the call stack.

## Sample Output

### Test Case 1 
```text
Enter the value of n: 5
Enter the element: 12
Enter the element: 3
Enter the element: 5
Enter the element: 7
Enter the element: 19
Enter the value of k: 2
Element: 5
```

### Test Case 2
```text
Enter the value of n: 7
Enter the element: 10
Enter the element: 50
Enter the element: 20
Enter the element: 70
Enter the element: 60
Enter the element: 30
Enter the element: 40
Enter the value of k: 5
Element: 50
```
