# Fractional Knapsack with Deterioration Rate

## 1. Problem Statement
You are given $n$ items, each with a base value $v_i$, weight $w_i$, and a constant decay rate $\lambda_i > 0$. As time progresses (measured by the accumulated weight $t$ in the knapsack), the effective value density of an item degrades. Specifically, if an item is consumed at time $t$, its effective value density becomes $(v_i / w_i) - \lambda_i \cdot t$. Given a knapsack of maximum capacity $W$, determine the optimal order to pack the items and the exact fractional amounts of each item to include to maximize the overall total value.

## 2. Approach
Solving this problem requires addressing two distinct mathematical challenges: the sequence of the items (scheduling) and the amount of each item to take (allocation).

*   **Optimal Scheduling (Smith's Rule):** If we swap any two adjacent items in the knapsack, the item placed earlier subjects the item placed later to more decay. To minimize the overall loss of value, items that decay the fastest must be packed first. Therefore, the optimal scheduling order is strictly descending by their decay rates ($\lambda$).
*   **Fractional Allocation (Marginal Benefit):** Once the items are sorted, the problem becomes a quadratic knapsack problem. We simulate a continuous greedy algorithm. We calculate the Marginal Benefit (MB) of adding an infinitesimally small amount ($\epsilon$) of each item. The MB accounts for the item's base density, the decay it has already suffered, and the future decay it will inflict on all subsequent items. We repeatedly take $\epsilon$ of the item with the highest positive MB until the knapsack is full or no item provides positive value.

## 3. Algorithm
1.  **Initialize Data:** Create a list of items with their base density, weight, and decay rate.
2.  **Sort:** Sort the list of items in descending order based on their decay rate $\lambda_i$. 
3.  **Iterative Allocation:** Set the current knapsack weight to 0. Choose a small step size $\epsilon$.
4.  **Calculate Marginal Benefit (MB):** For each item that has not yet reached its weight limit, calculate:
    $$MB_i = \text{Base Density}_i - (\lambda_i \times \text{Prefix Sum of } x_j \text{ for } j \le i) - (\text{Sum of } \lambda_k \times x_k \text{ for } k > i)$$
5.  **Greedy Choice:** Find the item $i$ with the maximum $MB_i$. If this maximum $MB_i \le 0$, terminate the loop (adding more weight destroys total value).
6.  **Update:** Add $\epsilon$ to the chosen item's allocated fraction $x_i$ and to the current knapsack weight. Repeat from step 4 until capacity $W$ is reached.
7.  **Calculate Total:** Integrate the value function for the chosen fractions over their scheduled times to output the final maximized value.

## 4. Pseudocode
```text
function solve_decay_knapsack(items, W, epsilon):
    // Step 1 & 2: Sort items by decay rate descending
    sort(items, key=lambda x: x.decay, reverse=True)
    
    current_weight = 0
    
    // Step 3: Iterative Allocation
    while current_weight < W:
        max_mb = -INFINITY
        best_item_index = -1
        
        for i from 0 to items.length - 1:
            if items[i].allocated_weight + epsilon > items[i].max_weight:
                continue
                
            // Calculate prefix sum (current accumulated weight for item i)
            prefix_sum = sum(items[j].allocated_weight for j in 0...i)
            
            // Calculate future decay impact on items packed after i
            future_decay = sum(items[k].decay * items[k].allocated_weight for k in i+1...n-1)
            
            // Marginal Benefit formula
            mb = items[i].base_density - (items[i].decay * prefix_sum) - future_decay
            
            if mb > max_mb:
                max_mb = mb
                best_item_index = i
                
        // Terminate if knapsack is full or no item adds positive value
        if best_item_index == -1 or max_mb <= 0:
            break
            
        items[best_item_index].allocated_weight += epsilon
        current_weight += epsilon
        
    return items
```

## 5. Complexity Analysis
*   **Time Complexity:** 
    *   Sorting the $n$ items takes $O(n \log n)$. 
    *   The `while` loop executes $\frac{W}{\epsilon}$ times. 
    *   Inside the loop, calculating the Marginal Benefit for $n$ items takes $O(n)$ time. 
    *   **Overall Time Complexity:** $O(n \log n + n \cdot \frac{W}{\epsilon})$. This is a pseudopolynomial validation approach. *(Note: An exact mathematical solver using the Pool Adjacent Violators Algorithm drops the $\epsilon$ dependency, achieving an exact $O(n^2)$ time).*
*   **Space Complexity:** 
    *   The algorithm requires an array to store the $n$ item structures and their allocated fractions. 
    *   **Overall Space Complexity:** $O(n)$, scaling strictly linearly with the number of input items.

## 6. Sample Output
```text
Optimal Fractional Choices & Schedule:
Item 1: Take 2.0000 units
Item 2: Take 1.5000 units
Total Maximized Value: 12.3750
```