# Security Switches (Chinese Rings Variant)

## 1. Problem Statement
There is a row of $n$ security switches protecting a military installation. They follow strict mechanical rules:
(i) The rightmost switch (Switch 1) can be turned on or off at will.
(ii) Any other switch $i$ can be turned on or off only if the switch to its immediate right (Switch $i-1$) is ON and all other switches to its right (Switches $i-2$ down to $1$) are OFF.
(iii) Only one switch may be toggled at a time.
Given that all $n$ switches are initially ON, the objective is to devise an algorithm to turn off all the switches in the minimum number of moves.

## 2. Approach
This problem is isomorphic to the classic "Baguenaudier" or Chinese Rings puzzle. We can solve it using a recursive strategy. 
Let's denote the switches from $1$ (rightmost) to $n$ (leftmost).
To turn OFF switch $n$:
1. We need switch $n-1$ to be ON, and switches $n-2, n-3, \dots, 1$ to be OFF. 
2. Assuming they are initially all ON, we must first recursively turn OFF the first $n-2$ switches.
3. Now the conditions are met, so we can toggle (turn OFF) switch $n$.
4. Next, we must turn switch $n-1$ OFF. But we can't do that yet because switches $n-2 \dots 1$ are OFF, and we need $n-2$ to be ON to turn off $n-1$. So, we must recursively turn ON the first $n-2$ switches.
5. Finally, we recursively turn OFF the first $n-1$ switches.

This requires two mutually recursive functions: `turnOff(n)` and `turnOn(n)`.

## 3. Algorithm/ Pseudocode
```text
Algorithm TurnOff(n)
    IF n <= 0 THEN RETURN
    IF n == 1 THEN 
        PRINT "Toggle 1"
        RETURN
    IF n == 2 THEN
        PRINT "Toggle 2"
        PRINT "Toggle 1"
        RETURN
        
    TurnOff(n - 2)
    PRINT "Toggle n"
    TurnOn(n - 2)
    TurnOff(n - 1)

Algorithm TurnOn(n)
    IF n <= 0 THEN RETURN
    IF n == 1 THEN 
        PRINT "Toggle 1"
        RETURN
    IF n == 2 THEN
        PRINT "Toggle 1"
        PRINT "Toggle 2"
        RETURN
        
    TurnOn(n - 1)
    TurnOff(n - 2)
    PRINT "Toggle n"
    TurnOn(n - 2)
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** Let $T(n)$ be the number of moves to turn off $n$ switches. From the algorithm, to turn off $n$ switches, we need to turn off $n-2$, toggle $1$, turn on $n-2$, and turn off $n-1$. Turning on $k$ switches takes the same number of moves as turning them off.
  Thus, the recurrence relation is:
  $T(n) = T(n-1) + 2T(n-2) + 1$
  The characteristic equation for the homogeneous part is $r^2 - r - 2 = 0$, which factors to $(r-2)(r+1) = 0$. The roots are $2$ and $-1$. 
  Therefore, the closed-form solution is dominated by the $2^n$ term. Specifically, $T(n) = \frac{2^{n+1} - 1}{3}$ if $n$ is even, and $T(n) = \frac{2^{n+1} - 2}{3}$ if $n$ is odd.
* **Result:** **O(2^n)** (Exponential Time Complexity).

### ii) Space Complexity
* **Derivation:** The algorithm is completely recursive and doesn't allocate any dynamic arrays or matrices. The memory overhead comes strictly from the call stack during recursion. The maximum depth of the recursion tree when evaluating `TurnOff(n)` or `TurnOn(n)` is exactly $n$.
* **Result:** **O(n)**.

## 5. Sample Output
If we run the C program with `n = 4` switches (initially all ON), the sequence of toggles required to turn them all OFF is:
```text
Sequence to turn off 4 switches:
Toggle 2
Toggle 1
Toggle 4
Toggle 1
Toggle 2
Toggle 1
Toggle 3
Toggle 1
Toggle 2
Toggle 1
```
*(Explanation: It takes exactly 10 moves to turn off 4 switches following the mechanical rules.)*
