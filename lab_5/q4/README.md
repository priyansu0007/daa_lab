# DAA Lab 5 - Question 4: Heap Sort with File I/O

## Problem Statement
Implement Heap Sort to sort N randomly generated elements stored in a file. Do the complexity analysis of your algorithm.

## Approach
This program integrates File I/O operations with the **Heap Sort** algorithm. The workflow involves:
1.  **Data Generation:** Generate $N$ random integers and store them in an output text file (`unsorted.txt`).
2.  **Data Loading:** Allocate memory dynamically for an array of size $N$ and read the unsorted numbers from the file into this array.
3.  **Sorting (Heap Sort):** 
    - **Build Max Heap:** Rearrange the array into a binary max-heap, where every parent node is greater than or equal to its child nodes.
    - **Extract Elements:** Swap the root of the max-heap (the largest element) with the last element of the heap. Reduce the heap size by 1 and call `heapify` on the root to restore the max-heap property. Repeat this until the array is fully sorted.
4.  **Data Persistence:** Write the sorted elements into a new text file (`sorted.txt`) and free the allocated memory.

## Algorithm
1. Prompt the user for the number of elements, $N$.
2. Open `unsorted.txt` in write mode, generate $N$ random integers, and write them to the file.
3. Allocate memory for an integer array of size $N$ using `malloc`.
4. Open `unsorted.txt` in read mode and load the integers into the array.
5. Invoke `HeapSort(arr, N)`:
   - Call `Heapify` starting from the last non-leaf node down to the root node to build the initial Max Heap.
   - Loop from the end of the array down to 1:
     - Swap the root `arr[0]` with the current last element `arr[i]`.
     - Call `Heapify(arr, i, 0)` on the reduced heap to reposition the new root.
6. Open `sorted.txt` in write mode and write the sorted array line by line.
7. Free the dynamically allocated array.

## Pseudocode
```text
procedure Heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    
    if left < n and arr[left] > arr[largest]:
        largest = left
        
    if right < n and arr[right] > arr[largest]:
        largest = right
        
    if largest != i:
        swap arr[i] and arr[largest]
        Heapify(arr, n, largest)

procedure HeapSort(arr, n):
    // Build Max Heap
    for i = (n / 2) - 1 down to 0:
        Heapify(arr, n, i)
        
    // Extract elements from heap one by one
    for i = n - 1 down to 1:
        swap arr[0] and arr[i]
        Heapify(arr, i, 0)

procedure Main():
    Read N from user
    
    // File Generation
    Open "unsorted.txt" for writing
    for i = 0 to N - 1:
        write random_number to "unsorted.txt"
    Close "unsorted.txt"
    
    // File Loading
    Allocate array arr of size N
    Open "unsorted.txt" for reading
    for i = 0 to N - 1:
        read value into arr[i]
    Close "unsorted.txt"
    
    // Sort
    HeapSort(arr, N)
    
    // File Persistence
    Open "sorted.txt" for writing
    for i = 0 to N - 1:
        write arr[i] to "sorted.txt"
    Close "sorted.txt"
    
    Free arr
```

## Complexity Analysis

### Time Complexity
*   **Building the Heap:** $O(N)$
    Although `Heapify` takes $O(\log N)$ time, a tighter mathematical bound for building the entire heap from the bottom up yields $O(N)$.
*   **Extracting Elements:** $O(N \log N)$
    We extract the maximum element $N-1$ times. Each extraction requires a call to `Heapify` to restore the heap property, taking $O(\log N)$ time.
*   **Total Time Complexity (Best, Average, and Worst Case):** $O(N \log N)$
    Unlike Quick Sort, Heap Sort provides a strictly guaranteed $O(N \log N)$ runtime regardless of the initial arrangement of the data.
*   **File I/O:** $O(N)$ for reading and writing files.

### Space Complexity
*   **Array Space:** $O(N)$
    Dynamic heap memory is needed to hold the $N$ integers read from the file.
*   **Sorting Auxiliary Space:** $O(\log N)$
    The algorithm sorts the array in-place. However, because this implementation uses a recursive `Heapify` function, it takes $O(\log N)$ space on the call stack due to the depth of the binary tree. (This could be reduced to $O(1)$ if `Heapify` was implemented iteratively).

## Sample Output

### Console Interaction
```text
Enter the number of elements to generate and sort: 200
Successfully generated and wrote 200 random numbers to 'unsorted.txt'.
Array sorted successfully using Heap Sort in memory.
Sorted numbers have been written to 'sorted.txt'.
```

*(Note: The randomly generated elements and their sorted counterparts will be stored in `unsorted.txt` and `sorted.txt` respectively).*
