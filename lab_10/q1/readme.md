# Online Graph Bipartiteness Validation

## 1. Problem Statement
 [Online Graph-Bipartiteness Testing] A graph is bipartite if and only if it contains
no odd-length cycles. Given an undirected graph with V vertices, edges arrive online one
by one. Maintain whether the graph remains bipartite. If adding an edge (u, v) does not
introduce an odd cycle, add it; otherwise, report that it violates bipartiteness and skip
it. By choosing the proper input representation, write a program in C to validate your
algorithm and derive the complexity analysis of your algorithm.

## 2. Approach
The problem can be solved efficiently using an augmented **Disjoint Set Union (DSU)** data structure, commonly referred to as a "Bipartite DSU". 

Standard DSU keeps track of connected components. To check for bipartiteness, we augment it by assigning a "parity" (or color relation) to each node relative to its DSU parent. We introduce a `parity` array where `parity[v]` stores $0$ if node $v$ has the same color as its parent, and $1$ if it has the opposite color. 

When evaluating a new edge $(u, v)$:
*   **Same Component:** We find the roots of $u$ and $v$. If they share the same root, they are already in the same connected component. We then check their parities relative to the root. If `parity[u] == parity[v]`, adding the edge would connect two nodes of the same color, creating an odd cycle (Rejected). Otherwise, it creates an even cycle (Accepted).
*   **Different Components:** If they have different roots, we merge the two components (Union by rank). We then update the parity of the merged root to ensure $u$ and $v$ end up with opposite colors, preserving bipartiteness across the newly connected components.

## 3. Algorithm
1.  Initialize a DSU with $V$ vertices. Create three arrays: `parent`, `rank`, and `parity`. 
2.  Set `parent[i] = i`, `rank[i] = 0`, and `parity[i] = 0` for all $0 \le i < V$.
3.  For each incoming edge $(u, v)$ in the stream:
    *   **Find:** Compute `root_u` and `root_v` using a recursive find function with path compression. During recursion, update the parity of a node by applying a bitwise XOR (`^`) with the parity of its original parent.
    *   **Check:** If `root_u == root_v`:
        *   If `parity[u] == parity[v]`, return `EDGE_REJECTED_ODD_CYCLE`.
        *   If `parity[u] != parity[v]`, return `EDGE_ACCEPTED_EVEN_CYCLE`.
    *   **Union:** If `root_u != root_v`:
        *   Attach the component with the smaller rank to the one with the larger rank.
        *   Calculate the parity of the newly attached root. To ensure $u$ and $v$ have different parities (meaning an edge can exist between them), set the parity of the new root to `parity[u] ^ parity[v] ^ 1`.
        *   Return `EDGE_ACCEPTED_TREE`.

## 4. Pseudocode

```text
function create_DSU(N):
    parent = array(0 to N-1) initialized to index
    rank = array(0 to N-1) initialized to 0
    parity = array(0 to N-1) initialized to 0

function find(v):
    if v != parent[v]:
        original_parent = parent[v]
        parent[v] = find(original_parent)
        // Path compression parity update
        parity[v] = parity[v] XOR parity[original_parent] 
    return parent[v]

function add_edge(u, v):
    root_u = find(u)
    root_v = find(v)

    if root_u == root_v:
        if parity[u] == parity[v]:
            return REJECT_ODD_CYCLE
        else:
            return ACCEPT_EVEN_CYCLE

    // Union by Rank
    if rank[root_u] < rank[root_v]:
        parent[root_u] = root_v
        parity[root_u] = parity[u] XOR parity[v] XOR 1
    else:
        parent[root_v] = root_u
        parity[root_v] = parity[u] XOR parity[v] XOR 1
        if rank[root_u] == rank[root_v]:
            rank[root_u] = rank[root_u] + 1
            
    return ACCEPT_TREE_EDGE
```

## 5. Complexity Analysis

*   **Time Complexity:** 
    *   Initializing the DSU takes $O(V)$ time.
    *   Processing a single edge requires two `find` operations and at most one `union` operation. Thanks to path compression and union by rank, the amortized time complexity per edge is $O(\alpha(V))$, where $\alpha$ is the inverse Ackermann function (which grows so slowly it is effectively constant for all reasonable values of $V$).
    *   For a stream of $E$ edges, the total time complexity is $O(V + E \cdot \alpha(V))$.
*   **Space Complexity:** 
    *   The algorithm requires three arrays (`parent`, `rank`, `parity`), each of size $V$. Therefore, the overall space complexity is $O(V)$.

## 6. Sample Output
Running the provided C code with the predefined stream of 9 edges will yield the following terminal output:

```text
Online Graph Bipartiteness Validation (V = 6):
--------------------------------------------------
Edge (0, 1): [ACCEPTED] Added spanning forest edge.
Edge (1, 2): [ACCEPTED] Added spanning forest edge.
Edge (2, 3): [ACCEPTED] Added spanning forest edge.
Edge (3, 0): [ACCEPTED] Forms an even cycle (bipartiteness preserved).
Edge (0, 2): [REJECTED] Violates bipartiteness (introduces odd cycle).
Edge (4, 5): [ACCEPTED] Added spanning forest edge.
Edge (3, 4): [ACCEPTED] Added spanning forest edge.
Edge (0, 5): [ACCEPTED] Forms an even cycle (bipartiteness preserved).
Edge (1, 5): [REJECTED] Violates bipartiteness (introduces odd cycle).
```