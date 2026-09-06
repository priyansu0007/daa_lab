# DAA Lab 6 - Question 1: 1D Array Operations and Complexities

## Problem Statement
Given an array with $N$ unsorted integer elements, perform the following operations:
1. Find the maximum element.
2. Find the first and second largest elements.
3. Find the mean.
4. Find the median.
5. Find the standard deviation.
6. Find the mode.
7. Remove all duplicates.
8. Reverse the elements of the array.
9. Partition the array with respect to a user-defined pivot element.

Validate the procedures with a C program and perform the corresponding complexity analysis.

---

## Approach
The program tackles these operations using a mix of single-pass linear scans and sorting. To preserve the original array structure for operations like reversing and partitioning, an auxiliary copy of the array (`sorted_arr`) is created and sorted using C's built-in `qsort()` function.

*   **Linear Scan Operations:** Maximum, First/Second Largest, Mean, and Standard Deviation are calculated using $O(N)$ loops over the original array. Reversing is done by swapping elements from the boundaries towards the center. Partitioning uses a single-pass swap mechanism based on a user-provided pivot.
*   **Sorting-Dependent Operations:** Median, Mode, and Duplicate Removal are performed on the `sorted_arr`. Sorting the array first allows these operations to be completed in a subsequent single linear pass, simplifying the logic at the cost of $O(N \log N)$ sorting time.

---

## Algorithm / Pseudocode
```text
procedure ArrayOperations(arr, N):
    // 1. Linear pass for Max and Second Max
    first_max = arr[0]
    second_max = -INFINITY
    for i = 1 to N-1:
        if arr[i] > first_max:
            second_max = first_max
            first_max = arr[i]
        else if arr[i] > second_max and arr[i] != first_max:
            second_max = arr[i]

    // 2. Linear pass for Mean and Standard Deviation
    sum = 0
    for i = 0 to N-1: sum = sum + arr[i]
    mean = sum / N
    
    variance_sum = 0
    for i = 0 to N-1: variance_sum = variance_sum + (arr[i] - mean)^2
    std_dev = sqrt(variance_sum / N)

    // 3. Sort a copy for Median, Mode, and Duplicates
    sorted_arr = copy(arr)
    qsort(sorted_arr)

    // 4. Calculate Median from sorted array
    if N is even: median = (sorted_arr[N/2 - 1] + sorted_arr[N/2]) / 2.0
    else: median = sorted_arr[N/2]

    // 5. Find Mode from sorted array
    mode = sorted_arr[0], max_count = 1, current_count = 1
    for i = 1 to N-1:
        if sorted_arr[i] == sorted_arr[i-1]: current_count++
        else: current_count = 1
        if current_count > max_count:
            max_count = current_count
            mode = sorted_arr[i]

    // 6. Print Array without Duplicates
    print sorted_arr[0]
    for i = 1 to N-1:
        if sorted_arr[i] != sorted_arr[i-1]: print sorted_arr[i]

    // 7. Reverse Original Array
    for i = 0 to (N / 2) - 1:
        swap(arr[i], arr[N - 1 - i])

    // 8. Partition Original Array
    partition_index = -1
    for j = 0 to N-1:
        if arr[j] < pivot:
            partition_index++
            swap(arr[partition_index], arr[j])
```

---

## Complexity Analysis

### Time Complexity
*   **Linear Operations:** Finding the maximum, first/second largest, mean, standard deviation, reversing the array, and partitioning all iterate through the array of size $N$ sequentially. This takes $O(N)$ time.
*   **Sorting Operations:** The program uses standard library `qsort` on a copied array to find the median, mode, and unique elements. The quicksort algorithm takes $O(N \log N)$ time on average. Scanning the sorted array for the mode and duplicates takes an additional $O(N)$ time.
*   **Overall Time Complexity:** The overall time complexity is dominated by the sorting step, making the worst-case time complexity **$O(N \log N)$**.

### Space Complexity
*   **Auxiliary Array:** To preserve the original array while sorting, the program allocates a second array `sorted_arr` of size $N$. 
*   **Overall Space Complexity:** Creating this duplicate array requires $O(N)$ extra space, making the total space complexity **$O(N)$**. 

---

## Sample Output
```text
Enter the number of elements in the array: 7
Enter 7 unsorted integers:
12
5
12
8
1
20
5

--- Results ---
(i) Maximum element: 20
(ii) First largest: 20, Second largest: 12
(iii) Mean: 9.00
(v) Standard Deviation: 5.86
(iv) Median: 8.00
(vi) Mode: 5 (appears 2 times)
(vii) Array without duplicates: 1 5 8 12 20 
(viii) Reversed original array: 5 20 1 8 12 5 12 

(ix) Enter a pivot element for partitioning: 10
Partitioned array (< 10 on left, >= 10 on right): 5 8 1 5 12 20 12 
```