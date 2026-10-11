# Minimum Cost to Connect Sticks

## 1. Problem Statement

You are given an array of positive integers representing the lengths of $n$ sticks. You can connect any two sticks of lengths $x$ and $y$ into a single stick by paying a cost of $x + y$. The resulting stick will have a length of $x + y$. This process is repeated until there is only one stick remaining. Find the minimum total cost required to connect all the sticks into a single stick.

## 2. Approach

The problem can be modeled mathematically identically to building a Huffman Tree. The total cost of connecting all sticks is the sum of the intermediate stick lengths created at each step. This implies that sticks combined earlier will have their lengths added to the total cost multiple times (once for their initial combination, and again every time their resulting compound stick is combined with another).

To minimize this total cost, we must ensure that the longest sticks are combined as late as possible, and the shortest sticks are combined as early as possible. This dictates a **Greedy Algorithm** managed by a **Min-Priority Queue (Min-Heap)**. At any given step, we simply extract the two shortest available sticks, connect them, add their sum to our ongoing total cost, and insert the newly combined stick back into the heap.

## 3. Algorithm

1. **Edge Case Check:** If the array contains 0 or 1 stick, no connections are needed, and the cost is 0.
2. **Initialize Min-Heap:** Insert all the initial stick lengths into a Min-Heap so that the smallest values are always at the root.
3. **Initialize Tracking:** Set a `total_cost` variable to 0.
4. **Greedy Combination Loop:** While there is more than 1 stick remaining in the Min-Heap:
   * Extract the smallest stick (`stick1`).
   * Extract the second smallest stick (`stick2`).
   * Calculate the cost to connect them: `combined = stick1 + stick2`.
   * Add this cost to `total_cost`.
   * Push the `combined` stick back into the Min-Heap.
5. **Return Result:** Once only one stick remains in the heap, the loop terminates, and `total_cost` holds the absolute minimum cost.

## 4. Pseudocode

```
function min_cost_to_connect_sticks(sticks):
    if sticks.length <= 1:
        return 0
        
    // Step 2: Initialize Min-Heap
    min_heap = new MinHeap()
    for length in sticks:
        min_heap.push(length)
        
    total_cost = 0
    
    // Step 4: Greedy Combination Loop
    while min_heap.size() > 1:
        stick1 = min_heap.pop()
        stick2 = min_heap.pop()
        
        combined = stick1 + stick2
        total_cost += combined
        
        min_heap.push(combined)
        
    return total_cost
```

## 5. Complexity Analysis

* **Time Complexity:**
  * Initializing the Min-Heap with $N$ elements takes $O(N \log N)$ time (or $O(N)$ if an optimized bottom-up `heapify` is used).
  * The `while` loop runs exactly $N - 1$ times, because each iteration removes two elements and adds one back (a net reduction of 1).
  * Inside the loop, two `pop` operations and one `push` operation take $O(\log N)$ time each.
  * **Overall Time Complexity:** $O(N \log N)$, completely dominated by the priority queue extraction and insertion phases.

* **Space Complexity:**
  * The algorithm dynamically allocates a contiguous array to simulate the Min-Heap, which at its peak holds exactly $N$ elements.
  * **Overall Space Complexity:** $O(N)$, which scales strictly linearly with the number of input sticks.

## 6. Sample Output

```
Lengths: 2 4 3 
Minimum cost to connect all sticks: 14

Lengths: 1 8 3 5 
Minimum cost to connect all sticks: 30
```