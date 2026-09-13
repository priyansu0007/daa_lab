# Reve's Puzzle (4-Peg Tower of Hanoi)

## 1. Problem Statement
Reve's puzzle is a variation of the classic Tower of Hanoi problem. There are $n$ disks of different sizes and four pegs instead of three. Initially, all disks are placed on the first peg in order of size, with the largest at the bottom and the smallest at the top. The objective is to transfer all disks to a destination peg by a sequence of moves such that only one disk is moved at a time, and a larger disk is never placed on top of a smaller one. The specific challenge is to prove that 8 disks take exactly 33 moves, and to generalize the algorithm for $n$ disks.

## 2. Approach
The problem is solved using the **Frame-Stewart algorithm**, a dynamic programming approach. The general strategy to move $n$ disks using 4 pegs is as follows:
1. Choose an intermediate number of disks, $k$ (where $1 \le k < n$).
2. Recursively move the top $k$ disks to an intermediate peg using all 4 pegs. This takes $M(k)$ moves.
3. Move the remaining $n - k$ disks to the destination peg using only the remaining 3 pegs. Since the intermediate peg is occupied by the $k$ smallest disks (which cannot be moved upon by larger disks), this step reduces to the classic 3-peg Tower of Hanoi problem, which takes exactly $2^{n-k} - 1$ moves.
4. Recursively move the $k$ disks from the intermediate peg to the destination peg using all 4 pegs. This again takes $M(k)$ moves.

The total moves for a chosen $k$ will be: $2 \cdot M(k) + 2^{n-k} - 1$.
To find the optimal solution, we must calculate this value for all possible valid partitions $k$ and select the one that yields the absolute minimum number of total moves. We store previously calculated values of $M(i)$ in an array to avoid redundant computations (Dynamic Programming).

## 3. Algorithm/ Pseudocode
```text
Algorithm REVES_PUZZLE(n)
// Input: n, the number of disks
// Output: Minimum number of moves to solve the 4-peg Tower of Hanoi

START
    1. IF n == 0 THEN RETURN 0
    2. IF n == 1 THEN RETURN 1
    
    3. CREATE an array DP of size n + 1
    4. INITIALIZE DP[0] = 0, DP[1] = 1, DP[2] = 3
    
    5. FOR i = 3 TO n DO:
           DP[i] = INFINITY
           FOR k = 1 TO i - 1 DO:
               // 2 * moves for top k (4 pegs) + moves for bottom i-k (3 pegs)
               moves = 2 * DP[k] + (2^(i - k)) - 1
               IF moves < DP[i] THEN:
                   DP[i] = moves
               END IF
           END FOR
       END FOR
       
    6. RETURN DP[n]
END
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** The algorithm utilizes two nested loops to build the dynamic programming table from size $3$ up to $n$.
    * The outer loop iterates over the number of disks `i` from $3$ to $n$.
    * The inner loop iterates to find the optimal split point `k`, running from $1$ to `i-1`.
    * The total number of operations is proportional to the sum of the first $n$ integers: $\sum_{i=1}^{n} i \approx \frac{n(n+1)}{2}$.
* **Result:** **O(n^2)**. *(Note: While calculating $2^{i-k}$ can theoretically add complexity, using bitwise shift operators `1 << (i - k)` makes it an $O(1)$ operation, preserving the quadratic overall bound.)*

### ii) Space Complexity
* **Derivation:** We maintain a 1-dimensional array (`DP`) of size $n+1$ to memoize the minimum moves required for each subproblem from $0$ up to $n$ disks. There are no deeply nested recursive call stacks since we are using an iterative bottom-up DP approach.
* **Result:** **O(n)**.

## 5. Sample Output
If we run the C program with `n = 8` disks:
```text
Minimum moves for 8 disks is: 33
```
*(Explanation: The optimal split for 8 disks is when $k = 4$. Moving 4 disks takes 9 moves on 4 pegs. The bottom 4 disks take $2^4 - 1 = 15$ moves on 3 pegs. Total: $2(9) + 15 = 18 + 15 = 33$ moves.)*
