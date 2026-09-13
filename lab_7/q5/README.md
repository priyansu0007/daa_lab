# Hitting a Moving Target

## 1. Problem Statement
A computer game features a shooter and a moving target. There are $n > 1$ hiding spots located along a straight line. The shooter cannot see the target but knows that the target strictly moves to an adjacent hiding spot (either left or right) between every two consecutive shots. The objective is to design an algorithm that guarantees hitting the target, or prove that no such algorithm exists. If it exists, determine the time and space complexity.

## 2. Approach
An algorithm to guarantee a hit definitely exists. The solution relies on the mathematical concept of parity (even and odd numbering). 

Because the target must move to an adjacent spot after every shot, its position alternates between an even-numbered spot and an odd-numbered spot with each turn. 
1. **First Sweep:** We assume the target starts on an **even**-numbered spot. If we shoot sequentially at spots $2, 3, 4, \dots, n-1$, our shot's position increases by 1 each turn (changing parity). If the target started on an even spot, it will also be on an even spot when we shoot at an even spot, and an odd spot when we shoot at an odd spot. Because the target cannot "jump" over our line of fire without landing on the spot we are shooting at, we are guaranteed to hit it during this sweep.
2. **Second Sweep:** If we reach $n-1$ and haven't hit the target, our initial assumption was wrong—the target must have started on an **odd**-numbered spot. To catch it, we simply reverse our direction and shoot at $n-1, n-2, \dots, 2$. By the time we start this second sweep, the parity aligns with our shots, guaranteeing a hit on the way back.

## 3. Algorithm/ Pseudocode
```text
Algorithm SHOOT_TARGET(n)
// Input: n, the number of hiding spots (n > 1)
// Output: A guaranteed sequence of shots to hit the target

START
    1. IF n <= 1 THEN 
           PRINT "No valid sequence"
           RETURN

    2. PRINT "Shoot sequence: "
    
    3. // First sweep (catches target if initially on an even spot)
       FOR i = 2 TO n - 1 DO:
           PRINT i
           
    4. // Second sweep (catches target if initially on an odd spot)
       FOR i = n - 1 DOWN TO 2 DO:
           PRINT i
END
```

## 4. Complexity Analysis (Derived)

### i) Time Complexity
* **Derivation:** The algorithm consists of two separate, non-nested `FOR` loops. The first loop runs from $2$ to $n-1$, which is $n-2$ iterations. The second loop runs from $n-1$ down to $2$, which is also $n-2$ iterations. The total number of operations is $2(n - 2) = 2n - 4$. Since constants are dropped in Big-O notation, the time scales linearly with the number of hiding spots $n$.
* **Result:** **O(n)** (Linear Time Complexity).

### ii) Space Complexity
* **Derivation:** The algorithm only requires a few integer variables (like the loop counter `i` and the input `n`) to keep track of the current shot position. No dynamic arrays, lists, or matrices are allocated that scale with the input size $n$. The sequence is printed directly to the output stream.
* **Result:** **O(1)** (Constant Space Complexity).

## 5. Sample Output
If we run the program with `n = 5` hiding spots:
```text
Shoot sequence: 2 3 4 4 3 2 
```
*(Explanation: Sweeping spots 2, 3, and 4 guarantees a hit if the target started on an even spot. Sweeping 4, 3, and 2 guarantees a hit if the target started on an odd spot. The maximum number of shots needed is 6.)*
