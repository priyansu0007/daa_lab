# Problem 4: Reverse Time-Step DSU Application

## 1. Problem Statement

Given a vertex-weighted undirected graph where each vertex $v$ has weight $w_v$, vertices are sequentially deleted one by one in a specified permutation order $P = [p_1, p_2, \dots, p_V]$. After each vertex deletion, compute the maximum sum of vertex values among all remaining connected components. Note that deleting a vertex in a graph means removing that specific vertex and all edges incident to it from the graph structure. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 2. Approach

### Decremental vs. Incremental Connectivity
* In an online setting, deleting vertices and their incident edges breaks connected components into smaller fragments (**decremental dynamic connectivity**). 
* Handling decremental component tracking and maintaining maximum vertex sums directly is computationally prohibitive (requiring expensive dynamic graph data structures or repeated re-traversals costing $\mathcal{O}(V(V + E))$ overall).

### Offline Processing & Reverse Time-Step Strategy
* Because the entire deletion sequence $P = [p_1, p_2, \dots, p_V]$ is known in advance, we invert the timeline:
  * Instead of sequentially **deleting** vertices from $t = 1$ to $V$, we run time in reverse from $t = V$ down to $1$, sequentially **inserting (activating)** vertices.
  * Adding vertices and joining incident edges converts a hard decremental problem into an **incremental connectivity** problem.
  * Incremental connectivity can be solved efficiently using **Disjoint Set Union (DSU / Union-Find)** with path compression and union by rank.

### Monotonic Max Component Weight Tracking
* Maintain an array `is_active` of boolean flags marking which vertices currently exist in the reconstructed graph.
* When activating vertex $u = p_k$:
  1. Mark $u$ as active (`is_active[u] = true`).
  2. Consider $u$'s individual weight against `current_max`.
  3. Inspect all neighbors $v$ adjacent to $u$ in the original graph:
     * If $v$ is already active (`is_active[v] == true`), union the component of $u$ with the component of $v$.
     * Combine their component sums:
       $$\text{comp\_sum}[\text{root}] = \text{comp\_sum}[\text{root}_u] + \text{comp\_sum}[\text{root}_v]$$
     * Update the running global maximum:
       $$\text{current\_max} = \max(\text{current\_max}, \text{comp\_sum}[\text{root}])$$
* Since components only grow or stay the same during edge additions, `current_max` is monotonically non-decreasing in reverse time.
* The state of the graph after deleting $p_1, \dots, p_k$ in forward time is identical to the graph state after inserting $p_V, p_{V-1}, \dots, p_{k+1}$ in reverse time.
* After deleting all vertices ($k = V$), the maximum remaining sum is trivially $0$.

---

## 3. Algorithm

1. **Adjacency Representation:**
   * Construct the original graph using a forward-star (head-to-next array) adjacency list to iterate efficiently over incident edges without large memory overhead.

2. **DSU Initialization:**
   * Allocate `parent`, `rank`, `comp_sum`, and `is_active` arrays of size $V$.
   * Initialize `parent[i] = i`, `rank[i] = 0`, `comp_sum[i] = weights[i]`, and `is_active[i] = false` for all $0 \le i < V$.

3. **Reverse Simulation:**
   * Set `out_answers[V - 1] = 0` (after all vertices are removed, remaining max sum is $0$).
   * Initialize `current_max = 0`.
   * Loop index $k$ backwards from $V - 1$ down to $1$:
     * Let $u = P[k]$.
     * Set `is_active[u] = true`.
     * Update $\text{current\_max} \leftarrow \max(\text{current\_max}, \text{comp\_sum}[u])$.
     * For each edge $(u, v)$ incident to $u$:
       * If `is_active[v]` is `true`:
         * Find roots $\text{root}_u = \text{dsu\_find}(u)$ and $\text{root}_v = \text{dsu\_find}(v)$.
         * If $\text{root}_u \neq \text{root}_v$, unite them via Union by Rank, summing their component weights into the resulting parent root.
         * Update $\text{current\_max} \leftarrow \max(\text{current\_max}, \text{comp\_sum}[\text{merged\_root}])$.
     * Store the result for the forward step: $\text{out\_answers}[k - 1] \leftarrow \text{current\_max}$.

4. **Output:**
   * Print or return `out_answers[0 \dots V - 1]` representing the maximum component sum after each deletion step.

---

## 4. Pseudocode

```text
Structure Graph:
    head: Array of integers
    to: Array of integers
    next: Array of integers
    edge_count: Integer

Structure DSU:
    parent: Array of integers
    rank: Array of integers
    comp_sum: Array of 64-bit integers
    is_active: Array of booleans

Function Find(dsu, v):
    If dsu.parent[v] != v:
        dsu.parent[v] = Find(dsu, dsu.parent[v])
    Return dsu.parent[v]

Function Union(dsu, u, v):
    root_u = Find(dsu, u)
    root_v = Find(dsu, v)
    If root_u == root_v:
        Return root_u

    If dsu.rank[root_u] < dsu.rank[root_v]:
        dsu.parent[root_u] = root_v
        dsu.comp_sum[root_v] = dsu.comp_sum[root_v] + dsu.comp_sum[root_u]
        Return root_v
    Else If dsu.rank[root_u] > dsu.rank[root_v]:
        dsu.parent[root_v] = root_u
        dsu.comp_sum[root_u] = dsu.comp_sum[root_u] + dsu.comp_sum[root_v]
        Return root_u
    Else:
        dsu.parent[root_v] = root_u
        dsu.comp_sum[root_u] = dsu.comp_sum[root_u] + dsu.comp_sum[root_v]
        dsu.rank[root_u] = dsu.rank[root_u] + 1
        Return root_u

Function SolveReverseDeletions(V, E, weights, edges, P):
    graph = CreateGraph(V, edges)
    dsu = CreateDSU(V, weights)
    out_answers = Array of size V

    current_max = 0
    out_answers[V - 1] = 0

    For k from V - 1 down to 1:
        u = P[k]
        dsu.is_active[u] = True
        If dsu.comp_sum[u] > current_max:
            current_max = dsu.comp_sum[u]

        For each neighbor v of u in graph:
            If dsu.is_active[v] is True:
                merged_root = Union(dsu, u, v)
                If dsu.comp_sum[merged_root] > current_max:
                    current_max = dsu.comp_sum[merged_root]

        out_answers[k - 1] = current_max

    Return out_answers
```

---

## 5. Complexity Analysis

### Time Complexity
* **Graph Construction:** Building the forward star adjacency structure takes $\mathcal{O}(V + E)$ time.
* **DSU Initialization:** Setting up parent pointers, weights, and ranks takes $\mathcal{O}(V)$ time.
* **Reverse Edge Traversal & DSU Operations:**
  * Each vertex is activated exactly once.
  * Each undirected edge $(u, v)$ is inspected at most twice (once from $u$ and once from $v$).
  * For each active incident edge, `Union` and `Find` are called. With Path Compression and Union by Rank, each DSU operation takes amortized $\mathcal{O}(\alpha(V))$ time, where $\alpha$ is the Inverse Ackermann Function.
* **Total Time Complexity:** $\mathcal{O}(V + E \cdot \alpha(V))$. For all practical values of $V$, $\alpha(V) \le 4$, making the running time essentially **linear**, $\mathcal{O}(V + E)$.

### Space Complexity
* **Graph Storage:** The forward-star arrays `head` ($\mathcal{O}(V)$), `to` ($\mathcal{O}(E)$), and `next` ($\mathcal{O}(E)$) require $\mathcal{O}(V + E)$ space.
* **DSU Storage:** Arrays `parent`, `rank`, `comp_sum`, and `is_active` require $4 \times \mathcal{O}(V) = \mathcal{O}(V)$ space.
* **Output Buffer:** Array `out_answers` requires $\mathcal{O}(V)$ space.
* **Total Space Complexity:** $\mathcal{O}(V + E)$.

---

## 6. Sample Output

### Input Configuration
```text
Vertices (V): 5
Vertex Weights: [0]: 10, [1]: 20, [2]: 30, [3]: 40, [4]: 50
Edges (E = 5):
(0, 1), (1, 2), (2, 3), (3, 4), (0, 4)  [Forms a 5-cycle]

Deletion Sequence P (0-indexed):
Step 1: Delete vertex 2 (weight 30)
Step 2: Delete vertex 0 (weight 10)
Step 3: Delete vertex 3 (weight 40)
Step 4: Delete vertex 4 (weight 50)
Step 5: Delete vertex 1 (weight 20)
```

### Execution Output
```text
Sequential Vertex Deletions and Max Remaining Component Sum:
------------------------------------------------------------
After deleting vertex p_1 (vertex 2): Max Component Sum = 120
After deleting vertex p_2 (vertex 0): Max Component Sum = 90
After deleting vertex p_3 (vertex 3): Max Component Sum = 50
After deleting vertex p_4 (vertex 4): Max Component Sum = 20
After deleting vertex p_5 (vertex 1): Max Component Sum = 0
```