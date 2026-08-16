# Defective Coin Quality Control (Divide and Conquer)

This repository contains a C program (`q2.c`) that implements a Divide and Conquer algorithm to find a potentially lighter defective coin among a set of `n` coins using a balance scale. It satisfies the O(log_2 n) time complexity constraint.

## Approach

The algorithm simulates a balance scale to repeatedly narrow down the search space by half. Since we don't know for certain if a defective coin exists at all, we must be careful when we reach the base case.

1. **Divide:** 
   * Split the current set of coins into two equal halves: Set A and Set B.
   * If the number of coins is odd, one coin is left out of the scale.

2. **Weigh & Conquer:** 
   * Compare the total weight of Set A and Set B.
   * **Case 1: Set A == Set B (Balanced):** The defective coin is in neither set. 
     * If the total number of coins was even, there is no defective coin at all (return -1). 
     * If odd, the defective coin *must* be the left-out coin. We also now know that any coin from Set A is a "perfect" coin. We keep track of this `known_good` coin for final verification.
   * **Case 2: Set A < Set B:** The lighter defective coin is definitively in Set A. We flag that the defect is `confirmed` and recurse on Set A.
   * **Case 3: Set A > Set B:** The lighter defective coin is definitively in Set B. We flag that the defect is `confirmed` and recurse on Set B.

3. **Base Case (1 coin remaining):**
   * If a defect was already `confirmed` (from Case 2 or 3), this remaining coin is definitely the defective one.
   * If no defect was confirmed yet (it was the left-out coin from Case 1), we compare this single coin against a `known_good` coin. If it is lighter, it's defective. If it weighs the same, all coins in the entire batch are perfect.

---

## Time Complexity Derivation (Step-by-Step)

The algorithm divides the search space in half at each recursive step and performs a constant number of operations (one weighing). 

Let T(n) be the maximum number of weighings to find the defective coin out of n coins.
The recurrence relation is:
T(n) = T(n/2) + c  (where c is the constant time to weigh two halves)

Step-by-step substitution method:
Step 1: T(n) = T(n/2) + c
Step 2: Substitute T(n/2) with (T(n/4) + c):
        T(n) = [T(n/4) + c] + c 
        T(n) = T(n/4) + 2c
Step 3: Substitute T(n/4) with (T(n/8) + c):
        T(n) = [T(n/8) + c] + 2c 
        T(n) = T(n/8) + 3c

Generalizing for k recursive steps:
T(n) = T(n / 2^k) + k*c

Base Case: The recursion stops when the subset size becomes 1.
n / 2^k = 1
n = 2^k

Applying log base 2 on both sides:
k = log_2(n)

Substitute k back into the generalized equation:
T(n) = T(1) + c * log_2(n)

At T(1), we might do one final weighing against a known good coin, which takes O(1) time. 
Thus, the total time complexity is bounded by log_2(n) + c.

**Total Time Complexity:** O(log_2 n)

---

## Space Complexity Derivation

The space complexity is determined by the maximum depth of the recursive call stack. 
Since the input size `n` is divided by 2 at each level of the recursion tree, the maximum depth of the tree is log_2(n). 
At each level, only a few primitive integer variables (`len`, `half`, `sumA`, `sumB`) are stored in the stack frame.

**Total Space Complexity:** O(log_2 n) auxiliary space due to the call stack.

---

## Sample Output

Compile the code using gcc:

    gcc q2.c -o a.out -lm

*(Note: The `-lm` flag is required to link the math library for the `ceil` and `log2` functions.)*

Run the executable:

    ./a.out

**Execution Output:**

    ==========================================
       Defective Coin Quality Control Test    
    ==========================================
    
    Total Coins (N): 16
    Scenario: Defective coin is at index 11.
    Algorithm Found: 11
    Weighings Used:  4
    Theoretical max steps (ceil(log2 N) + 1): 5
    Status: SUCCESS
    
    Total Coins (N): 15
    Scenario: Defective coin is at index 4.
    Algorithm Found: 4
    Weighings Used:  3
    Theoretical max steps (ceil(log2 N) + 1): 5
    Status: SUCCESS
    
    Total Coins (N): 15
    Scenario: Defective coin is at index 14.
    Algorithm Found: 14
    Weighings Used:  4
    Theoretical max steps (ceil(log2 N) + 1): 5
    Status: SUCCESS
    
    Total Coins (N): 16
    Scenario: ALL coins are perfect (No defective coin).
    Algorithm Found: -1
    Weighings Used:  4
    Theoretical max steps (ceil(log2 N) + 1): 5
    Status: SUCCESS
    
    Total Coins (N): 15
    Scenario: ALL coins are perfect (No defective coin).
    Algorithm Found: -1
    Weighings Used:  4
    Theoretical max steps (ceil(log2 N) + 1): 5
    Status: SUCCESS
    
    Total Coins (N): 100000
    Scenario: Defective coin is at index 99999.
    Algorithm Found: 99999
    Weighings Used:  18
    Theoretical max steps (ceil(log2 N) + 1): 18
    Status: SUCCESS