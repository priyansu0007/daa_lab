# Binary vs Ternary Search Analysis

This repository contains a C program (`q1.c`) that implements and compares iterative Binary Search and Ternary Search algorithms. The program tracks the number of element comparisons made by each algorithm to empirically validate their performance differences.

## Approach

The code implements two distinct search algorithms on a randomly generated, sorted array of integers:

1. **Binary Search:** 
   * Divides the search space into **two** nearly equal halves.
   * Calculates one mid-point: `mid = l + (r - l) / 2`.
   * Requires up to 2 comparisons per iteration (one to check for equality at `mid`, and one to check if the target is less than the `mid` element).

2. **Ternary Search:** 
   * Divides the search space into **three** nearly equal intervals.
   * Calculates two mid-points: `mid1 = l + (r - l) / 3` and `mid2 = r - (r - l) / 3`.
   * Requires up to 4 comparisons per iteration (checking equality at `mid1` and `mid2`, and routing the search space into one of the three intervals).

Both algorithms update an external `comparisons` counter passed by reference to track exactly how many times array elements are compared against the key.

---

## Time Complexity Derivation (Step-by-Step)

### 1. Binary Search
In Binary Search, the array of size n is divided into half in each step. Let T(n) be the time taken to search an array of size n. 
The recurrence relation is:
T(n) = T(n/2) + c  (where c is the constant time for comparisons)

Step-by-step substitution method:
Step 1: T(n) = T(n/2) + c
Step 2: Substitute T(n/2) with (T(n/4) + c):
        T(n) = [T(n/4) + c] + c 
        T(n) = T(n/4) + 2c
Step 3: Substitute T(n/4) with (T(n/8) + c):
        T(n) = [T(n/8) + c] + 2c 
        T(n) = T(n/8) + 3c

Generalizing for k steps:
T(n) = T(n / 2^k) + k*c

Base Case: The recursion stops when the array size becomes 1.
n / 2^k = 1
n = 2^k
Applying log base 2 on both sides:
k = log_2(n)

Substitute k back into the generalized equation:
T(n) = T(1) + c * log_2(n)
**Time Complexity:** O(log_2 n)

### 2. Ternary Search
In Ternary Search, the array is divided into three equal parts. 
The recurrence relation is:
T(n) = T(n/3) + c

Step-by-step substitution method:
Step 1: T(n) = T(n/3) + c
Step 2: Substitute T(n/3) with (T(n/9) + c):
        T(n) = [T(n/9) + c] + c 
        T(n) = T(n/9) + 2c
Step 3: Substitute T(n/9) with (T(n/27) + c):
        T(n) = [T(n/27) + c] + 2c 
        T(n) = T(n/27) + 3c

Generalizing for k steps:
T(n) = T(n / 3^k) + k*c

Base Case: The recursion stops when the array size becomes 1.
n / 3^k = 1
n = 3^k
Applying log base 3 on both sides:
k = log_3(n)

Substitute k back into the generalized equation:
T(n) = T(1) + c * log_3(n)
**Time Complexity:** O(log_3 n)

---

## Space Complexity

* **Binary Search:** The implementation is iterative and only uses a few variable pointers (`l`, `r`, `mid`). It requires constant auxiliary space. **Space Complexity:** O(1)
* **Ternary Search:** Like binary search, the iterative implementation strictly uses local pointer variables (`l`, `r`, `mid1`, `mid2`). **Space Complexity:** O(1)

---

## Why is Binary Search Better? (Justification)

At first glance, Ternary Search appears faster because O(log_3 n) represents a shallower tree depth than O(log_2 n). However, Big-O notation drops constant factors, which is where Ternary Search loses its efficiency. 

We must evaluate the **worst-case number of comparisons**, not just the number of splits:

1. **Binary Search Comparisons:** At most 2 comparisons per level.
   C_binary = 2 * log_2(n)
   
2. **Ternary Search Comparisons:** At most 4 comparisons per level.
   C_ternary = 4 * log_3(n)

To compare them directly, we can evaluate the ratio of their worst-case comparisons using the change-of-base formula for logarithms (log_b(n) = ln(n) / ln(b)):

C_ternary / C_binary = (4 * log_3(n)) / (2 * log_2(n))
                     = (4 * (ln(n) / ln(3))) / (2 * (ln(n) / ln(2)))
                     = 2 * (ln(2) / ln(3))

Plugging in the natural logarithm values (ln(2) = 0.693, ln(3) = 1.098):

C_ternary / C_binary = 2 * (0.693 / 1.098) = 1.262

**Conclusion:** In the worst-case scenario, Ternary Search makes approximately **26.2% more comparisons** than Binary Search. The cost of making extra comparisons per iteration outweighs the benefit of reducing the number of iterations. Our C implementation empirically validates this by printing a consistently higher total comparison count for Ternary Search.

---

## Sample Output

Compile the code using gcc:

    gcc q1.c -o a.out

Run the executable and provide an array size (e.g., 10000):

    ./a.out
    10000

**Execution Output:**

    Array Size: 10000
    Target Element: 24518 (Index 7150)

    --- Binary Search ---
    Result Index: 7150
    Total Comparisons: 26

    --- Ternary Search ---
    Result Index: 7150
    Total Comparisons: 34

*(Notice how Binary Search found the element in fewer comparisons, confirming the theoretical derivation above.)*