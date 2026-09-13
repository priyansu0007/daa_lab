# Invert the Coin-Triangle

## 1. Problem Statement
Consider an equilateral triangle formed by closely packed pennies (or other identical coins). The centers of the coins are assumed to be at the points of an equilateral triangular lattice. The objective is to design an algorithm to flip the triangle upside down in the minimum number of moves, where on each move, you can slide one coin at a time to its new position. The goal is to provide a compact formula for the minimum number of moves required and write a program to validate the procedure.

## 2. Approach
To invert the triangle with the minimum number of moves, we need to maximize the overlap between the original upright triangle and the final inverted triangle. By superimposing the target inverted shape over the original shape, we find that the most efficient method is to leave the central, roughly hexagonal core of coins untouched. We only need to move the coins located at the three extreme corners (the "tips" of the original triangle) and shift them to the opposite flat edge to form the new inverted corners. 

For a triangle with a base of $n$ coins, the total number of coins is given by the sum of the first $n$ natural numbers: $T = n(n+1)/2$. Through geometric overlap analysis, the number of coins that need to be moved to invert the triangle scales by a factor of 1/3 of the total coins. Thus, the exact compact formula for the minimum number of moves is $\lfloor n(n+1)/6 \rfloor$.

## 3. Algorithm/ Pseudocode
```text
Algorithm INVERT_COIN_TRIANGLE(n)
// Input: n, an integer representing the number of coins at the base of the triangle
// Output: Minimum number of moves to invert the triangle

START
    1. Read the input value 'n' (base of the triangle).
    2. Compute the minimum moves using the formula: moves = floor((n * (n + 1)) / 6).
    3. Print the computed 'moves'.
END
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** The algorithm evaluates a direct mathematical formula `(n * (n + 1)) / 6`. This evaluation consists of exactly one addition, one multiplication, and one integer division. There are no loops or recursive calls dependent on the size of the input $n$.
* **Result:** **O(1)** (Constant Time Complexity).

### ii) Space Complexity
* **Derivation:** The algorithm only requires a fixed amount of memory to store the integer input $n$ and the computed output for the number of moves. No arrays, matrices, or dynamic data structures are allocated that scale with $n$.
* **Result:** **O(1)** (Constant Space Complexity).

## 5. Sample Output
If we run the C program with a base size of `n = 4`:
```text
Minimum moves for a triangle of base 4 is: 3
```
*(Explanation: For a base of 4, there are 10 coins in total. The formula gives floor(4*5/6) = floor(20/6) = 3. Moving the 3 corner coins to the opposite side correctly inverts the triangle.)*
