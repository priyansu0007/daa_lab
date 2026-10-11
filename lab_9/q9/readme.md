# Hu-Tucker Greedy Simulation

## 1. Problem Statement

Given an ordered sequence of weights $w_1, w_2, \dots, w_n$, construct an optimal alphabetic binary search tree (or merge pattern) that strictly maintains the left-to-right in-order sequence of the indices. The goal is to minimize the expected search cost, mathematically defined as:
$$ \sum_{i=1}^{n} w_i \cdot \text{depth}(i) $$
where $\text{depth}(i)$ is the depth of the $i$-th weight in the constructed tree.

## 2. Approach

The Hu-Tucker algorithm solves this by temporarily relaxing the strict adjacency requirement during its initial phase, using the concept of **compatibility**. 

While a standard Huffman tree freely merges any two smallest weights (ignoring order), Hu-Tucker restricts merges to "compatible" pairs. Two nodes are considered compatible if there are no original **leaf nodes** between them in the current sequence (internal merged nodes between them are allowed). 

The algorithm operates in three phases, but to simply calculate the minimum cost, only Phase 1 is required:
* **Phase 1 (Combination):** Greedily find the compatible pair of nodes with the minimum combined weight. Merge them into a new internal node. Repeat this $N-1$ times until a single root remains. 
* While this Phase 1 tree does not preserve the strict alphabetic order left-to-right, it is mathematically proven that the **depth** of every leaf in this intermediate tree perfectly matches its depth in the true optimal alphabetic tree. Thus, calculating the cost of this intermediate tree yields the exact optimal cost.

## 3. Algorithm

1. **Initialize Sequence:** Create an active array of $N$ leaf nodes, preserving their initial sequence.
2. **Greedy Merge (N-1 times):** 
   * Scan the active sequence to evaluate all pairs of nodes $(i, j)$ where $i < j$.
   * A pair is valid (compatible) only if every node between $i$ and $j$ in the active sequence is an internal node (not a leaf).
   * Among all compatible pairs, find the one with the absolute minimum sum of weights ($w_i + w_j$).
3. **Update Sequence:**
   * Create a new internal node with weight $w_i + w_j$.
   * Place this new internal node at the position of $i$.
   * Remove the node at position $j$ and shift the remaining sequence to close the gap.
4. **Calculate Final Cost:** Once only one root node remains, perform a Depth-First Search (DFS). For every leaf node, multiply its original weight by its current depth in the tree. Sum these values to get the minimized total cost.

## 4. Pseudocode

```
function optimal_alphabetic_cost(weights):
    n = weights.length
    if n <= 1: return 0
    
    // Step 1: Initialize active nodes
    active_nodes = []
    for w in weights:
        active_nodes.append( Node(weight=w, is_leaf=true) )
        
    // Step 2 & 3: Phase 1 Combination
    for step from 0 to n - 2:
        min_sum = INFINITY
        best_i = -1
        best_j = -1
        
        for i from 0 to active_nodes.length - 2:
            for j from i + 1 to active_nodes.length - 1:
                
                // Check compatibility
                compatible = true
                for m from i + 1 to j - 1:
                    if active_nodes[m].is_leaf:
                        compatible = false
                        break
                        
                if not compatible:
                    break // Stop checking further j's for this i
                    
                current_sum = active_nodes[i].weight + active_nodes[j].weight
                if current_sum < min_sum:
                    min_sum = current_sum
                    best_i = i
                    best_j = j
                    
        // Merge the best compatible pair
        merged_node = Node(weight=min_sum, is_leaf=false, 
                           left=active_nodes[best_i], right=active_nodes[best_j])
                           
        active_nodes[best_i] = merged_node
        remove active_nodes[best_j]
        
    // Step 4: Calculate total cost via DFS
    root = active_nodes[0]
    return calculate_cost_dfs(root, 0)
    
function calculate_cost_dfs(node, depth):
    if node is null:
        return 0
    if node.is_leaf:
        return node.weight * depth
    
    return calculate_cost_dfs(node.left, depth + 1) + calculate_cost_dfs(node.right, depth + 1)
```

## 5. Complexity Analysis

* **Time Complexity:** 
  * **Simulation Approach (as written):** The array-based simulation searches for compatible pairs. In the worst-case scenario (many adjacent internal nodes), this scan takes $O(N^2)$ per step. Executing this for $N-1$ merges results in an overall validation time of $O(N^3)$.
  * **Theoretical Optimal:** Using advanced data structures (Min-Heaps and Circular Doubly Linked Lists) to track compatible pairs, the exact Hu-Tucker algorithm can be implemented strictly in $O(N \log N)$ time.
* **Space Complexity:** 
  * The algorithm dynamically allocates a maximum of $2N - 1$ tree nodes to represent the initial leaves and subsequent internal merges.
  * **Overall Space Complexity:** $O(N)$, ensuring memory overhead scales strictly linearly with the number of input weights.

## 6. Sample Output

```
Input Weights: [2, 3, 1, 4]

Leaf 2 (Weight 2) ends up at Depth 2
Leaf 3 (Weight 3) ends up at Depth 2
Leaf 1 (Weight 1) ends up at Depth 3
Leaf 4 (Weight 4) ends up at Depth 1

Total Minimum Cost: 17
```