# Stable Color Sorter

## Overview
This program sorts an array of key-value pairs (where the key is a color and the value is an integer) based on their color. The sorting order follows a specific color precedence: **Red ('r') -> Blue ('b') -> Yellow ('y')**. 

A key requirement of this implementation is **stability**. Because the original items are pre-sorted by their integer values, the sorting algorithm ensures that the relative ascending order of the integer values is preserved within each color category.

## Approach
The algorithm utilizes a variation of **Counting Sort** (or Bucket Sort). Since there are only three fixed categories (Red, Blue, Yellow), we can group the elements in linear time without needing comparison-based sorting algorithms like QuickSort or MergeSort.

1. **Counting:** First, we count how many Red and Blue items exist in the array.
2. **Index Calculation:** Using these counts, we determine the starting index for each color bucket in a secondary "result" array:
   - Red starts at index `0`.
   - Blue starts at index `redCount`.
   - Yellow starts at index `redCount + blueCount`.
3. **Distribution:** We iterate through the original array and place each element into its corresponding color bucket in the `result` array, incrementing the bucket's index pointer along the way. Because we process the original array from left to right, items of the same color are placed into the bucket in their exact original sequence, guaranteeing stability.
4. **Copy Back:** Finally, the fully sorted auxiliary array is copied back over the original array.

## Algorithm
1. Check if the array is empty or has only one element; if so, return immediately.
2. Allocate a temporary `result` array of the same size as the input array.
3. Initialize `redCount` and `blueCount` to `0`.
4. **Pass 1:** Iterate through the input array. Increment `redCount` if the color is 'r' or 'R'. Increment `blueCount` if the color is 'b' or 'B'.
5. Set bucket starting indices:
   - `rIdx = 0`
   - `bIdx = redCount`
   - `yIdx = redCount + blueCount`
6. **Pass 2:** Iterate through the input array again. 
   - If the color is 'r' or 'R', place the item at `result[rIdx]` and increment `rIdx`.
   - If the color is 'b' or 'B', place the item at `result[bIdx]` and increment `bIdx`.
   - If the color is 'y' or 'Y', place the item at `result[yIdx]` and increment `yIdx`.
7. Iterate through the array size and copy all elements from `result` back to the original `arr`.
8. Free the dynamically allocated `result` array.

## Pseudocode
```text
function sortColorsPreserveValues(arr, size):
    if arr is empty or size <= 1:
        return

    result = allocate_array(size)
    redCount = 0
    blueCount = 0

    // Pass 1: Count
    for i from 0 to size - 1:
        if arr[i].col is 'r' or 'R':
            redCount = redCount + 1
        else if arr[i].col is 'b' or 'B':
            blueCount = blueCount + 1

    // Determine starting indices
    rIdx = 0
    bIdx = redCount
    yIdx = redCount + blueCount

    // Pass 2: Distribute maintaining stability
    for i from 0 to size - 1:
        if arr[i].col is 'r' or 'R':
            result[rIdx] = arr[i]
            rIdx = rIdx + 1
        else if arr[i].col is 'b' or 'B':
            result[bIdx] = arr[i]
            bIdx = bIdx + 1
        else if arr[i].col is 'y' or 'Y':
            result[yIdx] = arr[i]
            yIdx = yIdx + 1

    // Copy back to original
    for i from 0 to size - 1:
        arr[i] = result[i]

    free(result)
```

## Complexity Analysis
- **Time Complexity:** **$O(N)$**
  - The algorithm makes exactly two passes over the array of size $N$ (one pass to count, one pass to distribute), followed by one final pass to copy the elements back. This results in roughly $3N$ operations, which simplifies asymptotically to strictly linear time $O(N)$.
- **Space Complexity:** **$O(N)$ Auxiliary Space**
  - To maintain stability in linear time without complex in-place swapping logic, an auxiliary `result` buffer of size $N$ is dynamically allocated. Thus, the space complexity scales linearly with the input size.

## Sample Output
When the program is executed with the original pre-sorted items array, the items are regrouped by color while their ascending integer values remain ordered within each group:

```text
Original (sorted by val): (2, r) (5, y) (7, r) (10, y) (15, b) (42, b) 
Sorted (Color -> Value):  (2, r) (7, r) (15, b) (42, b) (5, y) (10, y) 
```
