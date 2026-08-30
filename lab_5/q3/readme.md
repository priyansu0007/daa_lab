# DAA Lab 5 - Question 3: Quick Sort with File I/O

## Problem Statement
Implement Quick sort of N random elements stored in a file.

## Approach
This program combines file I/O operations with the standard **Quick Sort** algorithm. The overall workflow is as follows:
1.  **Data Generation:** Generate $N$ random integers and write them to a text file (`unsorted.txt`).
2.  **Data Loading:** Dynamically allocate memory for an array of size $N$ and read the data from the text file into memory.
3.  **Sorting:** Apply the in-place Quick Sort algorithm. Quick Sort is a divide-and-conquer algorithm that selects a 'pivot' element and partitions the array such that all elements smaller than the pivot are placed before it, and all elements larger are placed after it. It then recursively sorts the sub-arrays.
4.  **Data Persistence:** Write the sorted array into a new text file (`sorted.txt`) and free the dynamically allocated memory.

## Algorithm
1. Prompt the user for the number of elements, $N$.
2. Open `unsorted.txt` in write mode. Generate $N$ random numbers (using `rand()`) and write them to the file. Close the file.
3. Allocate dynamic memory for an array of $N$ integers using `malloc`.
4. Open `unsorted.txt` in read mode. Parse the $N$ integers into the array. Close the file.
5. Invoke `QuickSort(arr, 0, N - 1)`:
   - **Partition Step:** Choose the last element as the pivot. Use two pointers to swap elements so that smaller elements move to the left of the pivot and larger elements to the right. Place the pivot in its correct sorted position and return its index.
   - **Recursive Step:** Recursively call `QuickSort` on the left sub-array and the right sub-array.
6. Open `sorted.txt` in write mode. Write the sorted array elements into this file line by line. Close the file.
7. Free the dynamically allocated memory.

## Pseudocode
```text
procedure QuickSort(arr, low, high):
    if low < high:
        pi = Partition(arr, low, high)
        QuickSort(arr, low, pi - 1)
        QuickSort(arr, pi + 1, high)

procedure Partition(arr, low, high):
    pivot = arr[high]
    i = low - 1
    
    for j = low to high - 1:
        if arr[j] < pivot:
            i = i + 1
            swap arr[i] and arr[j]
            
    swap arr[i + 1] and arr[high]
    return i + 1

procedure Main():
    Read N from user
    
    // Step 1: Generate and Write
    Open "unsorted.txt" for writing
    for i = 0 to N - 1:
        write random_number to "unsorted.txt"
    Close "unsorted.txt"
    
    // Step 2: Read into Memory
    Allocate array arr of size N
    Open "unsorted.txt" for reading
    for i = 0 to N - 1:
        read value into arr[i]
    Close "unsorted.txt"
    
    // Step 3: Sort
    QuickSort(arr, 0, N - 1)
    
    // Step 4: Write Sorted Output
    Open "sorted.txt" for writing
    for i = 0 to N - 1:
        write arr[i] to "sorted.txt"
    Close "sorted.txt"
    
    Free arr
```

## Complexity Analysis

### Time Complexity
*   **File I/O Overhead:** Generating, reading, and writing the files takes $O(N)$ time.
*   **Best Case (Sorting):** $O(N \log N)$
    The best case occurs when the partition process always picks the middle element as the pivot, dividing the array into two nearly equal halves. 
*   **Average Case (Sorting):** $O(N \log N)$
    For randomly generated numbers, the standard Quick Sort algorithm (with the last element as pivot) performs well, as the pivot will, on average, divide the array proportionally.
*   **Worst Case (Sorting):** $O(N^2)$
    The worst-case occurs if the chosen pivot is always the maximum or minimum element. While unlikely with purely random data, this happens if the data is already sorted or reverse-sorted, leading to highly unbalanced partitions.

### Space Complexity
*   **Array Space:** $O(N)$
    Dynamic memory is allocated to hold the $N$ integers in RAM while sorting.
*   **Recursive Stack Space:** 
    *   **Best / Average Case:** $O(\log N)$ for a balanced recursion tree.
    *   **Worst Case:** $O(N)$ if the recursion tree becomes a skewed line (e.g., highly unbalanced partitions).
*   **Total Auxiliary Space:** The in-place sorting uses $O(\log N)$ stack space on average, but the algorithm explicitly requires $O(N)$ heap space for the array storage.

## Sample Output

### Console Interaction
```text
Enter the number of elements to generate and sort: 400
Successfully generated and wrote 400 random numbers to 'unsorted.txt'.
Array sorted successfully using Quick Sort in memory.
Sorted numbers have been written to 'sorted.txt'.
```

*(Note: The actual numbers will be found in the respective text files generated in the working directory).*
