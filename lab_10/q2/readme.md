# Problem 2: Dynamic Connected Components in a Grid (Number of Islands II)

## 1. Problem Statement

Given an $R \times C$ grid initially completely filled with water, land cells are added one by one at positions $(r_1, c_1), (r_2, c_2), \dots, (r_k, c_k)$. After each operation, output the current number of 4-directionally connected land components (islands). By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm.

---

## 2. Approach

A naive search approach (such as Breadth-First Search or Depth-First Search) would require scanning the entire grid in $\mathcal{O}(R \cdot C)$ time per update, leading to an overall complexity of $\mathcal{O}(k \cdot R \cdot C)$. We optimize this using an incremental **Disjoint Set Union (DSU / Union-Find)** data structure with coordinate flattening:

1. **2D to 1D Coordinate Flattening:**
   * A 2D cell coordinate $(r, c)$ is mapped to a unique 1D linear index:
     $$\text{index} = r \times C + c$$
     where $0 \le r < R$ and $0 \le c < C$.

2. **Water vs. Land Representation:**
   * Cells initially contain water, marked by setting `parent[index] = -1`.
   * When land is added at $(r, c)$:
     * If `parent[index] != -1`, the cell is already land; skip processing to keep island counts idempotent.
     * Otherwise, set `parent[index] = index` and increment `num_islands` by 1.

3. **Incremental 4-Directional Merging:**
   * Inspect the 4 orthogonal neighboring cells: Up $(r-1, c)$, Down $(r+1, c)$, Left $(r, c-1)$, and Right $(r, c+1)$.
   * For each valid neighbor that is already land (`parent[n_idx] != -1`), perform a `Union` between the new land cell and the neighbor.
   * If they belong to distinct connected components, merge them and decrement `num_islands` by 1.

4. **DSU Optimizations:**
   * **Path Compression:** Flattens tree hierarchies during recursive `Find` calls.
   * **Union by Rank:** Attaches shallower trees under deeper trees to maintain logarithmic depth bounds.

---

## 3. Algorithm

1. **Initialization:**
   * Allocate `parent` and `rank` arrays of size $R \times C$.
   * Initialize all entries in `parent` to `-1` (indicating water) and `rank` to `0`.
   * Initialize `num_islands = 0`.

2. **Index Flattening (`get_index(r, c)`):**
   * Compute and return $r \times C + c$.

3. **Find Operation (`dsu_find(i)`):**
   * If $\text{parent}[i] == i$, return $i$.
   * Recursively set $\text{parent}[i] = \text{dsu\_find}(\text{parent}[i])$ and return $\text{parent}[i]$.

4. **Union Operation (`dsu_union(i, j)`):**
   * Find representatives $\text{root}_i = \text{dsu\_find}(i)$ and $\text{root}_j = \text{dsu\_find}(j)$.
   * If $\text{root}_i == \text{root}_j$, return `false`.
   * Compare ranks:
     * Attach smaller rank root under higher rank root.
     * If ranks are identical, attach one root to the other and increment the surviving root's rank by 1.
   * Return `true`.

5. **Adding Land (`add_land(r, c)`):**
   * Validate boundary conditions: ensure $0 \le r < R$ and $0 \le c < C$.
   * Compute $\text{idx} = \text{get\_index}(r, c)$.
   * If $\text{parent}[\text{idx}] \neq -1$, return `num_islands` (cell already land).
   * Set $\text{parent}[\text{idx}] = \text{idx}$ and increment `num_islands` by 1.
   * Check all 4 directions $(\Delta r, \Delta c) \in \{(-1, 0), (1, 0), (0, -1), (0, 1)\}$:
     * Compute neighbor coordinates $(nr, nc) = (r + \Delta r, c + \Delta c)$.
     * If within bounds and $\text{parent}[\text{get\_index}(nr, nc)] \neq -1$:
       * If $\text{dsu\_union}(\text{idx}, \text{get\_index}(nr, nc))$ succeeds, decrement `num_islands` by 1.
   * Return `num_islands`.

---

## 4. Pseudocode

```text
Structure GridDSU:
    rows: Integer
    cols: Integer
    total_cells: Integer
    num_islands: Integer
    parent: Array of integers
    rank: Array of integers

Function CreateGridDSU(R, C):
    grid = Allocate GridDSU
    grid.rows = R
    grid.cols = C
    grid.total_cells = R * C
    grid.num_islands = 0
    grid.parent = Array of size R * C initialized to -1
    grid.rank = Array of size R * C initialized to 0
    Return grid

Function GetIndex(grid, r, c):
    Return r * grid.cols + c

Function Find(grid, i):
    If grid.parent[i] == i:
        Return i
    grid.parent[i] = Find(grid, grid.parent[i])
    Return grid.parent[i]

Function Union(grid, i, j):
    root_i = Find(grid, i)
    root_j = Find(grid, j)
    If root_i == root_j:
        Return False

    If grid.rank[root_i] < grid.rank[root_j]:
        grid.parent[root_i] = root_j
    Else If grid.rank[root_i] > grid.rank[root_j]:
        grid.parent[root_j] = root_i
    Else:
        grid.parent[root_j] = root_i
        grid.rank[root_i] = grid.rank[root_i] + 1
    Return True

Function AddLand(grid, r, c):
    If r < 0 or r >= grid.rows or c < 0 or c >= grid.cols:
        Return grid.num_islands

    idx = GetIndex(grid, r, c)
    If grid.parent[idx] != -1:
        Return grid.num_islands

    grid.parent[idx] = idx
    grid.num_islands = grid.num_islands + 1

    Directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    For each (dr, dc) in Directions:
        nr = r + dr
        nc = c + dc
        If 0 <= nr < grid.rows and 0 <= nc < grid.cols:
            n_idx = GetIndex(grid, nr, nc)
            If grid.parent[n_idx] != -1:
                If Union(grid, idx, n_idx) == True:
                    grid.num_islands = grid.num_islands - 1

    Return grid.num_islands
```

---

## 5. Complexity Analysis

### Time Complexity
* **Per Land Arrival Operation:** $\mathcal{O}(\alpha(R \cdot C))$, where $\alpha$ is the Inverse Ackermann function.
  * Adding a land cell checks 4 adjacent neighbors.
  * Each neighbor check performs at most one `Union` and two `Find` operations.
  * With path compression and union by rank, each operation executes in nearly constant time $\mathcal{O}(\alpha(R \cdot C))$.
* **Total Time Complexity for $k$ Operations:** $\mathcal{O}(k \cdot \alpha(R \cdot C))$. For all practical grid sizes, $\alpha(R \cdot C) \le 4$, making the total runtime linear with respect to operations: $\mathcal{O}(k)$.

### Space Complexity
* **Auxiliary Memory:** $\mathcal{O}(R \cdot C)$
  * Storing the 1D flattened `parent` array takes $\mathcal{O}(R \cdot C)$ space.
  * Storing the `rank` array takes $\mathcal{O}(R \cdot C)$ space.
* **Query Space:** $\mathcal{O}(1)$ additional memory overhead per update operation.

---

## 6. Sample Output

### Input Configuration & Stream
```text
Grid Dimensions: 3 x 3
Stream Operations:
1. Add (0, 0)
2. Add (0, 1)
3. Add (1, 2)
4. Add (2, 1)
5. Add (0, 1)  [Duplicate query]
6. Add (1, 1)  [Bridges components]
7. Add (2, 2)
```

### Execution Output
```text
Dynamic Connected Components on 3x3 Grid:
-------------------------------------------------
Operation 1: Added (0, 0) -> Active Islands: 1
Operation 2: Added (0, 1) -> Active Islands: 1
Operation 3: Added (1, 2) -> Active Islands: 2
Operation 4: Added (2, 1) -> Active Islands: 3
Operation 5: Added (0, 1) -> Active Islands: 3
Operation 6: Added (1, 1) -> Active Islands: 1
Operation 7: Added (2, 2) -> Active Islands: 1
```