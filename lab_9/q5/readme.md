# Candy Distribution Problem (Bi-directional Slope Greedy)

## 1. Problem Statement

You are given an array of integers representing the ratings of $n$ children standing in a line. You are tasked with distributing candies to these children according to the following rules:

1. Every child must receive at least one candy.
2. Children with a higher rating than their immediate neighbors must receive more candies than those neighbors.

Find the minimum total number of candies required to satisfy these conditions.

## 2. Approach

Attempting to evaluate both left and right neighbors simultaneously can lead to cascading updates and $O(N^2)$ complexity. Instead, this problem is optimally solved using a **Bi-directional Greedy** approach, which decouples the rules into two independent $O(N)$ sweeps.

* **Left-to-Right Pass:** We ensure that the left-neighbor constraint is satisfied. If a child has a higher rating than the child to their left, they get exactly one more candy than the left child.
* **Right-to-Left Pass:** We ensure that the right-neighbor constraint is satisfied. If a child has a higher rating than the child to their right, they must have more candies than the right child. To avoid breaking the constraint we already solved in the first pass, we take the maximum of their current candy count (from the left pass) and the right child's count plus one.

The minimum total candies needed is simply the sum of the resulting allocations.

## 3. Algorithm

1. **Initialization:** Handle the edge case where the array is empty. Create a `candies` array of size $n$ and initialize all elements to 1 (since every child gets at least one candy).

2. **First Pass (Left-to-Right):** Loop from index $i = 1$ to $n - 1$.
   * If `ratings[i] > ratings[i - 1]`, update `candies[i] = candies[i - 1] + 1`.

3. **Second Pass (Right-to-Left):** Loop from index $i = n - 2$ down to $0$.
   * If `ratings[i] > ratings[i + 1]`, update `candies[i] = \max(\text{candies}[i], \text{candies}[i + 1] + 1)`.

4. **Summation:** Iterate through the `candies` array and compute the sum of all elements.

5. **Return:** Return the calculated sum as the minimum total candies.

## 4. Pseudocode

```
function min_candies(ratings):
    n = ratings.length
    if n == 0:
        return 0
        
    // Step 1: Initialize baseline
    candies = array of size n, filled with 1
    
    // Step 2: Left-to-Right Pass
    for i from 1 to n - 1:
        if ratings[i] > ratings[i - 1]:
            candies[i] = candies[i - 1] + 1
            
    // Step 3: Right-to-Left Pass
    for i from n - 2 down to 0:
        if ratings[i] > ratings[i + 1]:
            candies[i] = max(candies[i], candies[i + 1] + 1)
            
    // Step 4: Sum total candies
    total_candies = 0
    for count in candies:
        total_candies += count
        
    return total_candies
```

## 5. Complexity Analysis

* **Time Complexity:** 
  * Initializing the array takes $O(N)$ time.
  * The left-to-right pass takes $O(N)$ time.
  * The right-to-left pass takes $O(N)$ time.
  * Summing the array takes $O(N)$ time.
  * **Overall Time Complexity:** $O(N)$, because the algorithm performs four non-nested linear sweeps over the input sequence.

* **Space Complexity:**
  * We allocate a single contiguous 1D array (`candies`) of size $N$ to store the allocations before summing.
  * **Overall Space Complexity:** $O(N)$, scaling strictly linearly with the number of children. *(Note: Using a peak-valley approach could optimize this to $O(1)$ space).*

## 6. Sample Output

```
Ratings: [1, 0, 2] -> Min Candies: 5
(Allocations: [2, 1, 2])

Ratings: [1, 2, 2] -> Min Candies: 4
(Allocations: [1, 2, 1])

Ratings: [5, 4, 3, 2, 1] -> Min Candies: 15
(Allocations: [5, 4, 3, 2, 1])
```