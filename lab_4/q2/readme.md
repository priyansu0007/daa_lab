# Two Sum Across Two Sets

## Overview
This program finds a pair of elements—one from a first set (`s1`) and one from a second set (`s2`)—that add up to a specified target value, `x`. 

## Approach
A brute-force approach checking every possible pair would take quadratic time. To optimize this, the algorithm utilizes a combination of sorting and searching:
1. **Sorting:** The second set (`s2`) is sorted using the **Merge Sort** algorithm.
2. **Searching:** We iterate through each element in the first set (`s1`). For each element, we calculate the difference needed to reach the target `x`. We then use **Binary Search** to efficiently check if this required difference exists in the sorted `s2`.

## Algorithm
1. Read the array size `n` and dynamically allocate memory for `s1` and `s2`.
2. Populate `s1` and `s2` with user input.
3. Read the target sum `x`.
4. Pass both arrays and the target to the matching function.
5. **Sort:** Apply Merge Sort to `s2` in ascending order.
6. **Iterate and Search:** For each element `s1[i]` in `s1`:
   * Calculate `target = x - s1[i]`.
   * Perform a Binary Search for `target` in `s2`.
   * If found, print the resulting pair and terminate the search.
7. If the loop completes without finding a match, print a failure message.
8. Free the dynamically allocated memory before exiting.

## Pseudocode
```text
function setTwoSum(s1, s2, n, x):
    mergeSort(s2, 0, n - 1)
    
    found = false
    for i from 0 to n - 1:
        target = x - s1[i]
        idx = bSearch(s2, n, target)
        
        if idx != -1:
            print("Elements found: " + s1[i] + " + " + s2[idx] + " = " + x)
            found = true
            break
            
    if found is false:
        print("No such elements found!")

function bSearch(arr, n, target):
    left = 0
    right = n - 1
    
    while left <= right:
        mid = left + (right - left) / 2
        if arr[mid] == target:
            return mid
        else if arr[mid] > target:
            right = mid - 1
        else:
            left = mid + 1
            
    return -1
```

## Complexity Analysis
* **Time Complexity:** $O(N \log N)$
  * Sorting `s2` using Merge Sort takes $O(N \log N)$ time. Iterating through `s1` takes $N$ steps, and performing a Binary Search in each step takes $O(\log N)$ time, resulting in an additional $O(N \log N)$ operations. The overall time complexity remains $O(N \log N)$.
* **Space Complexity:** $O(N)$
  * The Merge Sort implementation allocates temporary subarrays (`leftArr` and `rightArr`) during the merging phase. The size of these subarrays adds up to $N$, leading to an auxiliary space complexity of $O(N)$.

## Sample Output
```text
Enter the number of elements: 4
Enter the element 1 of set 1: 1
Enter the element 2 of set 1: 5
Enter the element 3 of set 1: 10
Enter the element 4 of set 1: 20
Enter the element 1 of set 2: 8
Enter the element 2 of set 2: 9
Enter the element 3 of set 2: 12
Enter the element 4 of set 2: 2
Enter the value of x: 17
Elements found: 5 (from Set 1) + 12 (from Set 2) = 17
```
