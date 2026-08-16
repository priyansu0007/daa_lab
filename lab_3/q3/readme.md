# Min and Max using Divide and Conquer

This repository contains a C program (`q3.c`) that implements a Divide and Conquer algorithm to find the minimum and maximum elements in an array. The primary objective of this approach is to minimize the total number of comparisons, theoretically bounding them to at most 3n/2.

## Approach

The algorithm recursively divides the array into two halves until it reaches small base cases where the minimum and maximum can be determined with minimal comparisons. 

1. **Divide:** Find the middle index `mid` and recursively process the left half and right half of the array.
2. **Base Cases:**
   * **1 element (low == high):** Both min and max are this single element. (0 comparisons)
   * **2 elements (high == low + 1):** Compare the two elements. The smaller becomes min, the larger becomes max. (1 comparison)
3. **Combine:** After receiving the `minmax` structure from both halves:
   * Compare the `min` of the left half with the `min` of the right half to find the overall minimum. (1 comparison)
   * Compare the `max` of the left half with the `max` of the right half to find the overall maximum. (1 comparison)

By pairing elements and processing halves, we save comparisons compared to a linear scan, where each element is compared against both the current min and max.

---

## Comparison Bound Derivation (Step-by-Step)

We want to prove that the number of comparisons is bounded by 3n/2. Let T(n) be the number of comparisons made for an array of size n. Assume n is a power of 2 for simplicity.

The recurrence relation for the number of comparisons is:
T(n) = 2 * T(n/2) + 2  (for n > 2)

Base cases:
T(1) = 0
T(2) = 1

Step-by-step substitution:
Step 1: T(n) = 2 * T(n/2) + 2
Step 2: Substitute T(n/2) with (2 * T(n/4) + 2):
        T(n) = 2 * [2 * T(n/4) + 2] + 2
        T(n) = 4 * T(n/4) + 4 + 2
Step 3: Substitute T(n/4) with (2 * T(n/8) + 2):
        T(n) = 4 * [2 * T(n/8) + 2] + 4 + 2
        T(n) = 8 * T(n/8) + 8 + 4 + 2

Generalizing for k-1 steps (until we reach subsets of size 2):
T(n) = 2^(k-1) * T(n / 2^(k-1)) + [2^(k-1) + 2^(k-2) + ... + 8 + 4 + 2]

Since we want to reach the base case of 2 elements, we set n / 2^(k-1) = 2, which means 2^(k-1) = n/2.

Substitute 2^(k-1) = n/2 and T(2) = 1 into the equation:
First term: (n/2) * T(2) = (n/2) * 1 = n/2

Second term is a geometric series sum: 2 + 4 + 8 + ... + n/2
Sum of geometric series = a(r^m - 1) / (r - 1)
Here a=2, r=2, and the last term is n/2. The sum equals 2 * (n/2) - 2 = n - 2.

Adding both terms together:
T(n) = (n/2) + (n - 2)
T(n) = 3n/2 - 2

**Conclusion:** The maximum number of comparisons is (3n/2 - 2), which is strictly less than 3n/2. The bound holds.

---

## Time and Space Complexity

* **Time Complexity:** 
  The recurrence relation for time is identical to the one for comparisons: T(n) = 2T(n/2) + O(1).
  Using the Master Theorem (a=2, b=2, k=0), log_b(a) = 1 > k, so Time Complexity is O(n^log_2(2)) = O(n).
  **Time Complexity:** O(n)

* **Space Complexity:** 
  The algorithm is recursive. The recursion tree has a maximum depth of log_2(n). No auxiliary arrays are created, only a few variables per stack frame.
  **Space Complexity:** O(log_2 n) auxiliary stack space.

---

## Sample Output

Compile the code using gcc:

    gcc q3.c -o a.out

Run the executable and provide the input array size and elements:

    ./a.out
    Enter the number of elements: 6
    Enter the element: 45
    Enter the element: 12
    Enter the element: 9
    Enter the element: 88
    Enter the element: 3
    Enter the element: 67

**Execution Output:**

    Array elements: 45 12 9 88 3 67 
    Minimum element: 3
    Maximum element: 88