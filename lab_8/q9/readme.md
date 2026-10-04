# Question 9: Collatz Conjecture Analysis

## 1. Problem Statement
The Collatz Conjecture (also known as the 3n+1 problem) defines a recurrence relation for any strictly positive integer $n$:
- If $n$ is even: $T(n) = \frac{n}{2}$
- If $n$ is odd: $T(n) = 3n + 1$

The sequence repeatedly applies this function until $n = 1$. Write a modular C program to analyze the trajectory of a user-provided starting value $n \ge 1$ and across an interval $[a, b]$. The objective is to implement iterative control structures, functional decomposition, dynamic memory allocation/pointers, and integer overflow handling in C.

## 2. Approach
The solution is divided into two main functional components to ensure modularity:

1. **Single Trajectory (`get_collatz_path`):** We simulate the sequence for a single integer $n$. Because the stopping time (number of steps to reach 1) is unpredictable, we use dynamic memory allocation. We start with a base capacity using `malloc` and use `realloc` to double the array size whenever the sequence length exceeds current capacity. We also implement a safety check before calculating $3n + 1$ to prevent integer overflow.
2. **Interval Analysis (`analyze_interval`):** We iterate through every integer in the range $[a, b]$. For each integer, we compute its Collatz sequence length (without storing the full path to save memory) and keep track of the number that produces the longest sequence.

## 3. Algorithm
1. Prompt the user for a starting integer $n$.
2. Call the trajectory function passing $n$:
   - Initialize an array `path` with a default capacity using `malloc`.
   - Set `count = 0` and add $n$ to `path`.
   - While $n \neq 1$:
     - Check for overflow: If $n > \frac{\text{ULLONG\_MAX} - 1}{3}$ and $n$ is odd, abort to prevent overflow.
     - If $n$ is even, update $n = n / 2$.
     - Else, update $n = 3n + 1$.
     - If `count` reaches `capacity`, double `capacity` and `realloc` the `path` array.
     - Append the new $n$ to `path` and increment `count`.
   - Return the dynamically allocated `path` and its length.
3. Print the sequence and free the dynamically allocated memory.
4. Prompt the user for an interval $[a, b]$.
5. Initialize `max_steps = 0` and `max_start = a`.
6. Loop `i` from $a$ to $b$:
   - Set `curr = i` and `steps = 0`.
   - While `curr \neq 1`:
     - Apply the Collatz rules to `curr` and increment `steps`.
   - If `steps > max_steps`, update `max_steps = steps` and `max_start = i`.
7. Print the integer `max_start` and its `max_steps`.

## 4. Pseudocode
```text
function get_collatz_path(n, pointer length):
    capacity = 100
    path = allocate_memory(capacity)
    count = 0
    path[count++] = n
    
    while n != 1:
        if n is odd and n > (MAX_INT - 1) / 3:
            print "Overflow risk"
            break
            
        if n % 2 == 0:
            n = n / 2
        else:
            n = 3 * n + 1
            
        if count >= capacity:
            capacity = capacity * 2
            path = reallocate_memory(path, capacity)
            
        path[count++] = n
        
    *length = count
    return path

function analyze_interval(a, b):
    max_steps = 0
    max_start = a
    
    for i from a to b:
        curr = i
        steps = 0
        while curr != 1:
            if curr % 2 == 0: curr = curr / 2
            else: curr = 3 * curr + 1
            steps = steps + 1
            
        if steps > max_steps:
            max_steps = steps
            max_start = i
            
    print "Longest sequence starts at ", max_start, " with ", max_steps, " steps."
```

## 5. Complexity Analysis

### Time Complexity Derivation
The Collatz Conjecture is an open mathematical problem, meaning there is no proven analytical function $S(n)$ that defines the exact number of steps required to reach 1 for any given $n$.

1. **Single Trajectory:** Let $S(n)$ be the stopping time for $n$. The loop runs exactly $S(n)$ times. Arithmetic operations inside the loop take constant time $O(1)$. Memory reallocation takes amortized $O(1)$ time. 
   Therefore, the exact time complexity is:
   $$O(S(n))$$
   *Empirically, for most numbers, $S(n)$ behaves roughly proportionally to $\log(n)$, but maximum values can spike unpredictably.*

2. **Interval Analysis:** For an interval of size $K = (b - a + 1)$, we compute the sequence for every number. 
   $$\text{Total Time} = \sum_{i=a}^{b} O(S(i))$$
   If we denote $S_{max}$ as the maximum stopping time in this interval, a safe worst-case upper bound is:
   $$O(K \times S_{max})$$

### Space Complexity Derivation
1. **Single Trajectory (`get_collatz_path`):** We dynamically allocate an array to store the entire sequence of length $S(n) + 1$. Memory is doubled geometrically, meaning the allocated space never exceeds $2 \times S(n)$.
   $$O(S(n))$$
2. **Interval Analysis (`analyze_interval`):** We do not store the sequences during the interval check to save memory. We only track three integer variables (`curr`, `steps`, `max_steps`, `max_start`).
   Thus, the auxiliary space used is constant:
   $$O(1)$$

## 6. Sample Outputs

**Test Case 1:**
```text
--- Collatz Conjecture Explorer ---
Enter a starting integer (n >= 1) to view its trajectory: 6

Trajectory for 6:
6 3 10 5 16 8 4 2 1 

Total steps to reach 1: 8

-----------------------------------
Now, let's analyze an interval [a, b].
Enter start of interval (a): 1
Enter end of interval (b): 10

Analyzing interval [1, 10]...
Longest sequence in this interval starts at 9, which takes 19 steps to reach 1.
```