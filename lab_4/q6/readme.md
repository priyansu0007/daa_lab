# Maximum Interval Overlap Point

## Overview
This program identifies a specific point on a number line that is covered by the highest number of given overlapping intervals. This is particularly useful in scenarios like finding the time of maximum server load or maximum concurrent resource usage.

## Approach
Instead of iterating through every possible point between the minimum and maximum interval values (which would be too slow if the ranges are large), this algorithm uses a highly efficient **Line Sweep (Two-Pointer)** technique:
1. **Endpoint Separation:** The start points (left) and end points (right) of all intervals are separated into two distinct arrays.
2. **Sorting:** Both arrays are sorted independently in ascending order using **Merge Sort**. This creates an ordered sequence of "start" and "end" events.
3. **Sweeping:** We sweep through the sorted events using two pointers. When we encounter a start point, the number of active overlapping intervals increases. When we encounter an end point, the number decreases. We track the peak overlap and the coordinate where it occurs.

## Algorithm
1. Read the number of intervals, `n`.
2. Dynamically allocate two arrays of size `n`: `L` (for left endpoints) and `R` (for right endpoints).
3. Populate `L` and `R` with user input. Swap `L[k]` and `R[k]` if the start is greater than the end to maintain valid intervals.
4. Sort array `L` using Merge Sort.
5. Sort array `R` using Merge Sort.
6. Initialize pointers `i = 0` (for `L`), `j = 0` (for `R`), and variables `max_overlap`, `current_overlap`, and `best_point` to `0`.
7. Loop while `i < n` and `j < n`:
   * If `L[i] <= R[j]`: An interval has started. Increment `current_overlap`. 
     * If `current_overlap > max_overlap`, update `max_overlap` and record `best_point = L[i]`.
     * Increment `i`.
   * Else: An interval has ended. Decrement `current_overlap` and increment `j`.
8. Print the `best_point` and its corresponding `max_overlap`.
9. Free the dynamically allocated memory.

## Pseudocode
```text
function findMaxOverlapPoint(L, R, n):
    mergeSort(L, 0, n - 1)
    mergeSort(R, 0, n - 1)
    
    i = 0
    j = 0
    max_overlap = 0
    current_overlap = 0
    best_point = 0
    
    while i < n and j < n:
        if L[i] <= R[j]:
            current_overlap = current_overlap + 1
            if current_overlap > max_overlap:
                max_overlap = current_overlap
                best_point = L[i]
            i = i + 1
        else:
            current_overlap = current_overlap - 1
            j = j + 1
            
    print("Point " + best_point + " is in the largest number of intervals (" + max_overlap + ").")
```

## Complexity Analysis
* **Time Complexity:** $O(N \log N)$
  * Sorting both the `L` and `R` arrays takes $O(N \log N)$ time using Merge Sort. The subsequent while loop traverses the arrays using two pointers, which takes $O(N)$ operations. The sorting step dictates the overall time complexity of $O(N \log N)$.
* **Space Complexity:** $O(N)$
  * The algorithm requires $O(N)$ space to store the `L` and `R` arrays. Additionally, the Merge Sort implementation dynamically allocates temporary arrays during the merge phase, which requires an additional $O(N)$ auxiliary space.

## Sample Output
```text
Enter number of intervals: 5
Enter intervals (l r):
1 4
2 5
9 12
5 9
5 12
Point 5 is in the largest number of intervals (3).
```
