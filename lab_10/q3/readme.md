# Problem 3: Maximum Weight Component with Size Constraints

## 1. Problem Statement
Given a graph where each vertex $v$ has weight $w_v$, edges are added sequentially with weights. At any point, compute the maximum total vertex weight of any connected component whose size does not exceed a threshold $K$. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 2. Approach

When edges arrive online, disjoint components merge dynamically, changing both their total vertex weights and their component sizes. A static re-scan over all components after every edge addition requires $\mathcal{O}(V)$ time, leading to $\mathcal{O}(E \cdot V)$ total time, which is inefficient. 

To solve this problem efficiently:
1. **Augmented Disjoint Set Union (DSU):**
   * Maintain standard DSU structures (`parent` and `rank`) with **Path Compression** and **Union by Rank**.
   * Augment each root representative with two metadata fields:
     * `comp_size[root]`: Number of vertices in the component.
     * `comp_weight[root]`: Total sum of vertex weights in the component.
   * When two distinct components rooted at $\text{root}_u$ and $\text{root}_v$ merge into $\text{merged\_root}$:
     $$\text{comp\_size}[\text{merged\_root}] = \text{comp\_size}[\text{root}_u] + \text{comp\_size}[\text{root}_v]$$
     $$\text{comp\_weight}[\text{merged\_root}] = \text{comp\_weight}[\text{root}_u] + \text{comp\_weight}[\text{root}_v]$$

2. **Lazy Max-Heap for Dynamic Candidate Tracking:**
   * Direct removal of obsolete components from a standard binary heap takes $\mathcal{O}(V)$ without index-tracking overhead. Instead, we use a **Lazy Deletion** strategy in a binary **Max-Heap**.
   * Initially, push all single-vertex components having size $1 \le K$ into the heap.
   * Upon an edge addition, if the newly merged component satisfies $\text{comp\_size}[\text{merged\_root}] \le K$, push $(\text{comp\_weight}[\text{merged\_root}], \text{merged\_root})$ into the heap.
   * If its size exceeds $K$, it is simply not pushed.

3. **Querying via Lazy Invalidation:**
   * To find the maximum weight component with size $\le K$, inspect the root of the heap (`heap.top()`).
   * A heap entry `(weight, root_id)` is **valid** if and only if:
     1. `parent[root_id] == root_id` (the node is still an active root representative).
     2. `comp_size[root_id] <= K` (its size currently satisfies the threshold).
     3. `comp_weight[root_id] == weight` (the weight is up-to-date and has not merged further).
   * If any condition fails, the entry is stale; pop it and repeat.
   * The first valid entry extracted is guaranteed to be the maximum valid component weight. If the heap empties, no component satisfies the threshold.

---

## 3. Algorithm

1. **Initialization:**
   * Allocate `parent`, `rank`, `comp_size`, and `comp_weight` arrays of size $V$.
   * Initialize a Max-Heap of capacity $2V$.
   * For each vertex $i \in [0, V - 1]$:
     * Set `parent[i] = i`, `rank[i] = 0`, `comp_size[i] = 1`, and `comp_weight[i] = vertex_weights[i]`.
     * If $1 \le K$, push `(vertex_weights[i], i)` into the Max-Heap.

2. **Find (`dsu_find(dsu, v)`):**
   * If $\text{parent}[v] \neq v$, set $\text{parent}[v] \leftarrow \text{dsu\_find}(\text{dsu}, \text{parent}[v])$ (Path Compression).
   * Return $\text{parent}[v]$.

3. **Add Edge (`dsu_add_edge(dsu, u, v, w_edge)`):**
   * Identify $\text{root}_u \leftarrow \text{dsu\_find}(\text{dsu}, u)$ and $\text{root}_v \leftarrow \text{dsu\_find}(\text{dsu}, v)$.
   * If $\text{root}_u == \text{root}_v$, return (the edge forms a cycle within an existing component; sizes and weights do not change).
   * Merge by rank:
     * Make the root with higher rank the parent (`merged_root`), and the other root the child (`child_root`).
     * If ranks are equal, increment `rank[merged_root]`.
   * Update component metadata:
     * $\text{comp\_size}[\text{merged\_root}] \mathrel{+}= \text{comp\_size}[\text{child\_root}]$
     * $\text{comp\_weight}[\text{merged\_root}] \mathrel{+}= \text{comp\_weight}[\text{child\_root}]$
   * If $\text{comp\_size}[\text{merged\_root}] \le K$:
     * Push $(\text{comp\_weight}[\text{merged\_root}], \text{merged\_root})$ into the Max-Heap.

4. **Query Max Weight (`dsu_get_max_weight(dsu, max_weight)`):**
   * While the heap is non-empty:
     * Inspect top element `top = heap.data[0]`.
     * Check if `parent[top.root_id] == top.root_id` AND `comp_size[top.root_id] <= K` AND `comp_weight[top.root_id] == top.weight`.
     * If valid, set `*max_weight = top.weight` and return `true`.
     * Otherwise, call `heap_pop()` to discard the stale entry.
   * If the heap becomes empty, return `false` (no component has size $\le K$).

---

## 4. Pseudocode

```text
Structure HeapNode:
    weight: 64-bit Integer
    root_id: Integer

Structure MaxHeap:
    data: Array of HeapNode
    size: Integer
    capacity: Integer

Structure ConstrainedGraphDSU:
    V: Integer
    K: Integer
    parent: Array of Integer
    rank: Array of Integer
    comp_size: Array of Integer
    comp_weight: Array of 64-bit Integer
    heap: MaxHeap

Function InitializeDSU(V, K, vertex_weights):
    dsu = Allocate ConstrainedGraphDSU
    dsu.V = V
    dsu.K = K
    dsu.heap = CreateHeap(2 * V)
    For i from 0 to V - 1:
        dsu.parent[i] = i
        dsu.rank[i] = 0
        dsu.comp_size[i] = 1
        dsu.comp_weight[i] = vertex_weights[i]
        If 1 <= K:
            HeapPush(dsu.heap, vertex_weights[i], i)
    Return dsu

Function Find(dsu, v):
    If dsu.parent[v] != v:
        dsu.parent[v] = Find(dsu, dsu.parent[v])
    Return dsu.parent[v]

Function AddEdge(dsu, u, v, w_edge):
    root_u = Find(dsu, u)
    root_v = Find(dsu, v)
    If root_u == root_v:
        Return

    If dsu.rank[root_u] < dsu.rank[root_v]:
        merged_root = root_v
        child_root = root_u
    Else:
        merged_root = root_u
        child_root = root_v
        If dsu.rank[root_u] == dsu.rank[root_v]:
            dsu.rank[root_u] = dsu.rank[root_u] + 1

    dsu.parent[child_root] = merged_root
    dsu.comp_size[merged_root] = dsu.comp_size[merged_root] + dsu.comp_size[child_root]
    dsu.comp_weight[merged_root] = dsu.comp_weight[merged_root] + dsu.comp_weight[child_root]

    If dsu.comp_size[merged_root] <= dsu.K:
        HeapPush(dsu.heap, dsu.comp_weight[merged_root], merged_root)

Function GetMaxWeight(dsu, max_weight):
    While dsu.heap.size > 0:
        top = dsu.heap.data[0]
        If dsu.parent[top.root_id] == top.root_id and
           dsu.comp_size[top.root_id] <= dsu.K and
           dsu.comp_weight[top.root_id] == top.weight:
            *max_weight = top.weight
            Return True
        HeapPop(dsu.heap)
    Return False
```

---

## 5. Complexity Analysis

### Time Complexity
* **Initialization:** $\mathcal{O}(V \log V)$ to push all initial $V$ vertices into the heap (or $\mathcal{O}(V)$ using bottom-up heap construction).
* **Adding an Edge:**
  * Finding roots: $\mathcal{O}(\alpha(V))$ using path compression and union by rank.
  * Heap push (if size $\le K$): $\mathcal{O}(\log |H|)$, where $|H| \le 2V$.
  * Hence, processing an edge takes $\mathcal{O}(\alpha(V) + \log V)$.
* **Querying Maximum Weight:**
  * Validating top element is $\mathcal{O}(1)$.
  * Popping a stale entry takes $\mathcal{O}(\log V)$.
  * Over the entire execution, at most $V$ initial elements and at most $V - 1$ successful merge elements are ever pushed into the heap (total pushes $\le 2V - 1$). Thus, the total number of stale heap pops across all queries is bounded by $\mathcal{O}(V)$.
* **Amortized Query Time:** $\mathcal{O}(1)$ amortized per query (excluding stale deletions that aggregate to $\mathcal{O}(V \log V)$ across the entire program lifetime).
* **Total Time for $E$ Edge Additions and Queries:** $\mathcal{O}(V \log V + E(\alpha(V) + \log V))$.

### Space Complexity
* **DSU Storage:** Arrays `parent`, `rank`, `comp_size`, and `comp_weight` require $4 \times \mathcal{O}(V) = \mathcal{O}(V)$ space.
* **Max-Heap Storage:** At most $V$ initial single-vertex nodes and at most $V - 1$ merged component nodes are pushed, requiring capacity $2V$, which is $\mathcal{O}(V)$ space.
* **Total Space Complexity:** $\mathcal{O}(V)$.

---

## 6. Sample Output

### Input Configuration & Stream
```text
Vertices: 5 (indices 0 to 4)
Vertex Weights: [0]: 10, [1]: 20, [2]: 5, [3]: 40, [4]: 15
Size Threshold (K): 2

Edges Added:
1. (0, 1, wt=2.5) -> Component {0, 1}: size = 2 <= 2, weight = 10 + 20 = 30
2. (2, 3, wt=1.0) -> Component {2, 3}: size = 2 <= 2, weight = 5 + 40 = 45
3. (0, 2, wt=4.0) -> Component {0, 1, 2, 3}: size = 4 > 2 (disqualified from <= K)
4. (3, 1, wt=0.5) -> Redundant cycle edge
5. (3, 4, wt=3.2) -> Component {0, 1, 2, 3, 4}: size = 5 > 2
```

### Execution Output
```text
Online Component Weight Maintenance (V = 5, K = 2)
Initial vertex weights: [0]:10, [1]:20, [2]:5, [3]:40, [4]:15
-------------------------------------------------------------
Initial state: Max weight component (size <= 2) = 40
After adding edge (0, 1, wt=2.5) -> Max component weight: 40
After adding edge (2, 3, wt=1.0) -> Max component weight: 45
After adding edge (0, 2, wt=4.0) -> Max component weight: 15
After adding edge (3, 1, wt=0.5) -> Max component weight: 15
After adding edge (3, 4, wt=3.2) -> No component with size <= 2
```