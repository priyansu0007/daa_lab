# Super Egg Testing Experiment

## 1. Problem Statement
A firm wants to determine the highest floor in a 100-storey building from which a newly invented super-strong egg can fall without breaking. The tester is given identical eggs to experiment with, and an unbroken egg can be reused. The objective is to find the minimum number of droppings guaranteed to determine the highest safe floor in the worst-case scenario. We need to design a generalized dynamic programming solution for $E$ eggs and $F$ floors.

## 2. Approach
We solve this using Dynamic Programming. Let `DP[e][f]` represent the minimum number of trials required to find the critical floor using `e` eggs and `f` floors.

When we drop an egg from an intermediate floor `k` (where $1 \le k \le f$), two outcomes are possible:
1. **The egg breaks:** The critical floor must be below `k`. We now have `e - 1` eggs and `k - 1` floors to test. The number of remaining trials is `DP[e-1][k-1]`.
2. **The egg survives:** The critical floor must be above `k`. We still have `e` eggs and `f - k` floors left to test. The number of remaining trials is `DP[e][f-k]`.

Since we need the *guaranteed* minimum trials in the worst case, we take the maximum of these two outcomes (worst-case scenario for a specific floor `k`), add 1 (for the current drop), and then find the minimum of this value across all possible floors `k`.

**State Equation:**
`DP[e][f] = 1 + min(max(DP[e-1][k-1], DP[e][f-k]))` for $1 \le k \le f$.

**Base Cases:**
* If `f = 0` or `f = 1`: `DP[e][0] = 0` and `DP[e][1] = 1` for any `e`.
* If `e = 1`: `DP[1][f] = f` (we must test each floor one by one starting from the bottom).

## 3. Algorithm/ Pseudocode
```text
Algorithm EGG_DROP(E, F)
// Input: E (number of eggs), F (number of floors)
// Output: Minimum number of trials guaranteed to find the critical floor

START
    1. Create a 2D array DP[E+1][F+1]
    2. FOR i = 1 to E:
           DP[i][0] = 0
           DP[i][1] = 1
    3. FOR j = 1 to F:
           DP[1][j] = j
    4. FOR i = 2 to E:
           FOR j = 2 to F:
               DP[i][j] = INFINITY
               FOR k = 1 to j:
                   res = 1 + max(DP[i-1][k-1], DP[i][j-k])
                   IF res < DP[i][j]:
                       DP[i][j] = res
    5. RETURN DP[E][F]
END
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** The algorithm uses three nested loops.
    * The outer loop iterates over the number of eggs from $2$ to $E$ (runs $O(E)$ times).
    * The middle loop iterates over the number of floors from $2$ to $F$ (runs $O(F)$ times).
    * The inner loop checks every possible floor $k$ from $1$ to the current floor $j$, taking up to $O(F)$ iterations.
    * Multiplying these together: $O(E) \times O(F) \times O(F) = O(E \cdot F^2)$.
* **Result:** **O(E * F^2)**.

### ii) Space Complexity
* **Derivation:** The dynamic programming approach requires a 2D matrix (or table) of size $(E + 1) \times (F + 1)$ to store the minimum trials for every subproblem of eggs and floors. 
* **Result:** **O(E * F)**.

## 5. Sample Output
If we run the C program with 2 eggs and 100 floors:
```text
Minimum droppings for 2 eggs and 100 floors is: 14
```
*(Explanation: With 2 eggs and 100 floors, the optimal strategy requires at most 14 drops to guarantee finding the highest safe floor.)*
