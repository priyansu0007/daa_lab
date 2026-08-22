# Merge Overlapping Intervals

## Overview
This program takes a collection of intervals and merges any that overlap. It transforms a potentially fragmented set of timeframes or ranges into a consolidated list of mutually exclusive, continuous intervals.

## Approach
The most efficient way to solve this problem is by sorting the intervals first. 
1. **Sorting:** We sort the intervals based on their starting points using the **Merge Sort** algorithm. This ensures that any overlapping intervals will be adjacent to each other in the array.
2. **In-Place Merging:** We maintain a pointer (`index`) to track the last finalized interval in our array. As we iterate through the sorted intervals, we compare the current interval's start time with the end time of the interval at our `index`. 
   - If they overlap, we extend the end time of the interval at `index` to encompass both.
   - If they do not overlap, we advance our `index` and place the current interval there.

## Algorithm
1. Read the number of intervals, `n`.
2. Dynamically allocate an array of `Interval` structures (each containing an `x` start and `y` end value).
3. Populate the array with user input. If a user enters a start time greater than the end time, swap them to ensure validity.
4. Sort the array of intervals in ascending order based on the starting value (`x`) using Merge Sort.
5. If the array is empty, return 0.
6. Initialize an `index = 0` to track the position of the last merged interval.
7. Loop `i` from `1` to `n - 1`:
   * If `arr[index].y >= arr[i].x` (Overlap condition): 
     * Update the end time: `arr[index].y = max(arr[index].y, arr[i].y)`.
   * Else (No overlap):
     * Increment `index`.
     * Copy the current interval: `arr[index] = arr[i]`.
8. Return `index + 1`, which is the total count of merged intervals.
9. Print the merged intervals up to the new count and free the allocated memory.

## Pseudocode
```text
function mergeIntervals(arr, n):
    if n <= 0: return 0
    
    mergeSort(arr, 0, n - 1)
    
    index = 0
    for i from 1 to n - 1:
        // Check for overlap
        if arr[index].y >= arr[i].x:
            // Merge by updating the end time
            if arr[i].y > arr[index].y:
                arr[index].y = arr[i].y
        else:
            // No overlap, move to next slot and store
            index = index + 1
            arr[index] = arr[i]
            
    return index + 1
```

## Complexity Analysis
* **Time Complexity:** $O(N \log N)$
  * The Merge Sort step dominates the time complexity, requiring $O(N \log N)$ operations. The subsequent merging step only requires a single linear pass $O(N)$ through the array. Thus, the overall time complexity is $O(N \log N)$.
* **Space Complexity:** $O(N)$
  * The algorithm merges the intervals in-place, modifying the original array. However, the Merge Sort implementation requires dynamically allocated temporary arrays (`L` and `R`) during the merge phase, which takes $O(N)$ auxiliary space.

## Sample Output
```text
Enter the number of intervals: 4
Enter the intervals (x y):
Interval 1: 1 3
Interval 2: 2 6
Interval 3: 8 10
Interval 4: 15 18

Merged Intervals: {(1, 6), (8, 10), (15, 18)}
```
