# Selection Sort Analysis (Loop Invariants & Complexity)

This repository contains a C program (`q6.c`) that implements Selection Sort. It validates the theoretical time complexity of the algorithm by empirically tracking the number of comparisons made in both the best-case and worst-case scenarios.

## 1. Pseudocode

The algorithm described in the problem is **Selection Sort**. Here is its pseudocode (using 1-based indexing as given in the problem statement):

    SELECTION-SORT(A)
    1. n = length[A]
    2. for i = 1 to n - 1
    3.     minIndex = i
    4.     for j = i + 1 to n
    5.         if A[j] < A[minIndex]
    6.             minIndex = j
    7.     swap A[i] with A[minIndex]

---

## 2. Loop Invariant

**The Loop Invariant:** 
At the start of each iteration of the outer `for` loop (indexed by `i`), the subarray `A[1 ... i-1]` consists of the `i-1` smallest elements in the array `A`, and they are in strictly sorted order. Furthermore, all elements in the remaining subarray `A[i ... n]` are greater than or equal to the elements in `A[1 ... i-1]`.

To validate the proof of correctness, we must show three things:
*   **Initialization:** Before the first iteration (`i = 1`), the subarray `A[1 ... 0]` is empty. An empty array trivially contains the 0 smallest elements in sorted order, and the invariant holds.
*   **Maintenance:** During iteration `i`, the inner loop scans the remaining elements `A[i ... n]` to find the absolute smallest element among them. This element is then swapped with `A[i]`. Because this element is smaller than or equal to everything else in `A[i ... n]` but larger than or equal to everything in `A[1 ... i-1]`, appending it to the sorted subarray preserves the sorted order. The invariant is maintained for the next iteration (`i + 1`).
*   **Termination:** The loop terminates when `i = n`. At this point, the subarray `A[1 ... n-1]` contains the `n-1` smallest elements in sorted order.

---

## 3. Why does it run for only the first (n - 1) elements?

The algorithm only needs to iterate up to `n - 1` because of the termination property of our loop invariant. 

When the loop finishes after `i = n - 1`, the subarray `A[1 ... n-1]` contains the `n - 1` smallest elements of the original array, in sorted order. By process of elimination, the only element left at index `n` *must* be the largest element in the entire array. Since it is greater than or equal to all preceding elements, it is already in its correct, final position. Running a final loop iteration for the `n`-th element is mathematically redundant.

---

## 4. Time Complexity Derivation

### Worst-Case Running Time
Let's count the number of comparisons (the `if A[j] < A[minIndex]` step) made by the algorithm for an array of size `n`.
* For `i = 1`, the inner loop runs from `2` to `n` (makes `n - 1` comparisons).
* For `i = 2`, the inner loop runs from `3` to `n` (makes `n - 2` comparisons).
* ...
* For `i = n - 1`, the inner loop evaluates only `n` (makes `1` comparison).

The total number of comparisons `C(n)` is the sum of the first `n-1` integers:
    C(n) = (n - 1) + (n - 2) + ... + 2 + 1
    C(n) = n * (n - 1) / 2
    C(n) = (n^2 / 2) - (n / 2)

Dropping lower-order terms and constants, the worst-case time complexity is asymptotically bounded by the square of `n`.
**Worst-Case Running Time:** Theta(n^2)

### Is the Best-Case Running Time any better?
**No, it is not better.** 
Even if the array is already perfectly sorted (the best-case scenario), the algorithm has no way of knowing this. The inner loop must still blindly scan the entire remaining unsorted portion `A[i ... n]` to verify that `A[i]` is indeed the minimum element. 

The `if` condition is executed exactly the same number of times regardless of the input array's initial arrangement. Thus, the total number of comparisons remains exactly `n(n-1)/2`.
**Best-Case Running Time:** Theta(n^2)

---

## 5. Sample Output

Compile the code using gcc:

    gcc q6.c -o a.out

Run the executable and provide an array size (e.g., 100):

    ./a.out
    Enter the number of elements: 100

**Execution Output:**

    --- Best Case (Already Sorted) ---
    Comparisons made: 4950
    
    --- Worst Case (Reverse Sorted) ---
    Comparisons made: 4950
    
    --- Validation ---
    Theoretical n(n-1)/2 comparisons: 4950
    Claim Validated: Best-case and Worst-case time complexity are both Theta(n^2).

*(Notice how both the Best-Case and Worst-Case execute exactly 4,950 comparisons for an array of 100 elements, completely matching the derived mathematical formula of `100 * 99 / 2`, proving that the best case is not any better than the worst case.)*