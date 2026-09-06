# DAA Lab 6 - Question 4: Sorting via Reversal

## Problem Statement
Suppose you are given a permutation $p$ of the integers 1 to $n$, and seek to sort them in increasing order using only the `reverse(p, i, j)` operation. The cost of `reverse(p, i, j)` is equal to its length: $|j - i| + 1$. 

Design an algorithm that sorts $p$ with a total cost of $O(n \log^2 n)$, analyze its running time and cost, prove its correctness, and validate it using a C program.

---

## Approach
To achieve an $O(n \log^2 n)$ cost without allocating auxiliary arrays, the program implements a **Divide and Conquer** strategy using an **In-Place Merge Sort**.

Instead of standard merging, it merges two adjacent sorted blocks ($A$ and $B$) using rotations:
1.  **Find Pivot:** Find the middle element of the first block, $val_A$, at index $mid_A$.
2.  **Binary Search:** Use binary search on the second block to find the split point ($split_B$) where elements transition from being $< val_A$ to $\ge val_A$.
3.  **Rotate:** Perform a block swap (rotation) to move the elements of $B$ that are smaller than $val_A$ ahead of the elements of $A$ that are larger than $val_A$. A rotation of two adjacent contiguous blocks can be achieved using exactly **3 reversals**.
4.  **Recurse:** The element $val_A$ is now in its absolute final sorted position. The algorithm recursively merges the remaining left partitions and right partitions.

---

## Algorithm / Pseudocode
```text
procedure Reverse(arr, i, j):
    if i >= j: return
    total_cost = total_cost + (j - i + 1)
    while i < j:
        swap(arr[i], arr[j])
        i++, j--

procedure Rotate(arr, start, mid, end):
    if start >= mid or mid > end: return
    Reverse(arr, start, mid - 1)
    Reverse(arr, mid, end)
    Reverse(arr, start, end)

procedure BinarySearch(arr, low, high, key):
    while low <= high:
        mid = low + (high - low) / 2
        if arr[mid] < key: low = mid + 1
        else: high = mid - 1
    return low

procedure Merge(arr, start, mid, end):
    if start >= mid or mid > end: return

    mid_A = start + (mid - 1 - start) / 2
    val_A = arr[mid_A]
    
    split_B = BinarySearch(arr, mid, end, val_A)
    
    // Rotate the second half of A and the first half of B
    Rotate(arr, mid_A, mid, split_B - 1)
    
    elements_B1 = split_B - mid
    new_mid = mid_A + elements_B1
    
    // Recursively merge the left and right sides
    Merge(arr, start, mid_A, new_mid - 1)
    Merge(arr, new_mid + 1, split_B, end)

procedure MergeSort(arr, start, end):
    if start < end:
        mid = start + (end - start) / 2
        MergeSort(arr, start, mid)
        MergeSort(arr, mid + 1, end)
        Merge(arr, start, mid + 1, end)
```

---

## Complexity Analysis

### Time (Cost) Complexity
*   **Merge Cost $M(n)$:** In the merge step, the rotation costs at most $O(n)$ because it reverses segments of the array. The merge algorithm splits block $A$ in half at each recursive level. Therefore, the recursion tree for the merge function has a depth of $\log n$, and the total cost of rotations across all nodes at one level is bounded by $n$. This gives the merge step a total cost of $M(n) = O(n \log n)$.
*   **Total Cost $T(n)$:** The overall Merge Sort breaks the array into two halves. The recurrence relation is $T(n) = 2T(n/2) + M(n)$. Substituting the merge cost yields $T(n) = 2T(n/2) + O(n \log n)$. By the Master Theorem, this evaluates to a worst-case total cost of **$O(n \log^2 n)$**.

### Space Complexity
*   **Auxiliary Space:** The sorting and merging processes are performed strictly in-place using array index manipulations and mathematical reversals. No temporary arrays are allocated.
*   **Call Stack:** The only extra space consumed is by the recursive call stack for `MergeSort` and `Merge`. The maximum depth of the stack is bounded by **$O(\log n)$**. 

---

## Sample Output
```text
Enter the number of elements for the permutation: 5
Enter the permutation (integers separated by space):
1 4 3 2 5

Sorted Permutation: 1 2 3 4 5 
Total Reversal Cost: 11
```