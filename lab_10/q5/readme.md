# Problem 5: Lexicographically Smallest Connected Component Permutation

## 1. Problem Statement
Given a permutation $A$ of numbers $1 \dots n$, and a list of allowable pairwise swaps $(u, v)$ forming edges in an undirected graph, find the lexicographically smallest permutation achievable through any number of valid swaps[cite: 1]. By choosing the proper input representation, write a program in C to validate your algorithm and derive the complexity analysis of your algorithm[cite: 1].

---

## 2. Approach
Allowable swaps define an equivalence relation (transitivity) over index positions in the permutation[cite: 1]:

1. **Transitivity of Permutation Swaps:**
   * If an element at index $u$ can be swapped with index $v$, and index $v$ can be swapped with index $w$, any arbitrary reordering of elements among $\{u, v, w\}$ can be generated through a sequence of transpositions[cite: 1].
   * Consequently, every connected component of indices forms an independent symmetric group where elements can be rearranged arbitrarily[cite: 1].

2. **Component Identification via DSU:**
   * Treat indices $0 \dots n-1$ as graph vertices and the allowable pairwise swap pairs as undirected edges[cite: 1].
   * Use **Disjoint Set Union (DSU / Union-Find)** with **Path Compression** and **Union by Rank** to cluster mutually reachable index positions into connected components[cite: 1].

3. **Greedy Lexicographical Placement:**
   * A permutation is lexicographically smallest when smaller numbers occupy earlier (smaller) indices.
   * For each connected component of indices:
     * Identify the sorted sequence of positions: $i_1 < i_2 < \dots < i_k$.
     * Extract the set of values currently at those positions: $\{A[i_1], A[i_2], \dots, A[i_k]\}$.
     * Sort these values in ascending order: $v_1 \le v_2 \le \dots \le v_k$.
     * Place $v_j$ into position $i_j$ for all $1 \le j \le k$.

4. **Linear Index Grouping:**
   * To achieve $\mathcal{O}(n)$ index grouping without sorting indices explicitly, traverse indices backward ($n-1$ down to $0$) and prepend each index to a linked list keyed by its component root representative. Subsequent traversals naturally yield indices in increasing order.

---

## 3. Algorithm

1. **DSU Initialization:**
   * Initialize a DSU of size $n$ where `parent[i] = i` and `rank[i] = 0` for all $0 \le i < n$.

2. **Graph Construction (Index Unions):**
   * For each allowable swap pair $(u, v)$:
     * Convert 1-based indices to 0-based coordinates: $u \leftarrow u - 1, v \leftarrow v - 1$.
     * If valid, perform $\text{dsu\_union}(u, v)$.

3. **Bucket Indices by Component Root:**
   * Allocate arrays `head` (initialized to $-1$), `next`, and `comp_size` (initialized to $0$) of size $n$.
   * Loop index $i$ backward from $n - 1$ down to $0$:
     * Find root $r \leftarrow \text{dsu\_find}(i)$.
     * Insert $i$ at the head of linked list $r$:
       $$\text{next}[i] \leftarrow \text{head}[r], \quad \text{head}[r] \leftarrow i, \quad \text{comp\_size}[r] \leftarrow \text{comp\_size}[r] + 1$$

4. **Component Sorting and Assignment:**
   * Allocate a temporary buffer `val_buffer` of size $n$.
   * For each component root $r \in [0, n - 1]$ where $\text{head}[r] \neq -1$:
     * Traverse the linked list starting at $\text{head}[r]$ and collect all values $A[\text{index}]$ into `val_buffer`.
     * Sort `val_buffer[0 \dots \text{comp\_size}[r] - 1]` in ascending order using standard comparison (`qsort`).
     * Traverse the linked list starting at $\text{head}[r]$ a second time, writing back the sorted values into $A[\text{index}]$ in sequential order.

5. **Cleanup:**
   * Free dynamically allocated memory structures and return the modified permutation $A$.

---

## 4. Pseudocode

```text
Structure DSU:
    parent: Array of integers
    rank: Array of integers
    n: Integer

Function InitializeDSU(n):
    dsu = Allocate DSU
    dsu.parent = Array of size n with dsu.parent[i] = i
    dsu.rank = Array of size n initialized to 0
    Return dsu

Function Find(dsu, i):
    If dsu.parent[i] == i:
        Return i
    dsu.parent[i] = Find(dsu, dsu.parent[i])
    Return dsu.parent[i]

Function Union(dsu, u, v):
    root_u = Find(dsu, u)
    root_v = Find(dsu, v)
    If root_u != root_v:
        If dsu.rank[root_u] < dsu.rank[root_v]:
            dsu.parent[root_u] = root_v
        Else If dsu.rank[root_u] > dsu.rank[root_v]:
            dsu.parent[root_v] = root_u
        Else:
            dsu.parent[root_v] = root_u
            dsu.rank[root_u] = dsu.rank[root_u] + 1

Function LexicographicallySmallestPermutation(n, A, m, edges):
    dsu = InitializeDSU(n)

    // Unify connected indices
    For i from 0 to m - 1:
        u = edges[i][0] - 1
        v = edges[i][1] - 1
        If 0 <= u < n and 0 <= v < n:
            Union(dsu, u, v)

    // Group indices in ascending order using linked lists
    head = Array of size n initialized to -1
    next = Array of size n
    comp_size = Array of size n initialized to 0

    For i from n - 1 down to 0:
        root = Find(dsu, i)
        next[i] = head[root]
        head[root] = i
        comp_size[root] = comp_size[root] + 1

    // Extract, sort, and write back values per component
    val_buffer = Array of size n

    For r from 0 to n - 1:
        If head[r] == -1:
            Continue

        size = comp_size[r]
        idx = 0
        curr = head[r]
        While curr != -1:
            val_buffer[idx] = A[curr]
            idx = idx + 1
            curr = next[curr]

        Sort(val_buffer, 0, size - 1)

        idx = 0
        curr = head[r]
        While curr != -1:
            A[curr] = val_buffer[idx]
            idx = idx + 1
            curr = next[curr]
```

---

## 5. Complexity Analysis

### Time Complexity
* **DSU Operations:** Processing $m$ swap edges requires $m$ unions and up to $2m$ find operations:
  $$\mathcal{O}(m \cdot \alpha(n))$$
  where $\alpha$ is the Inverse Ackermann Function.
* **Component Grouping:** Traversing all $n$ indices backward and querying their roots takes $\mathcal{O}(n \cdot \alpha(n))$.
* **Sorting Within Components:** Let the components have sizes $s_1, s_2, \dots, s_c$ such that $\sum_{k=1}^c s_k = n$. Sorting values in each component takes:
  $$\sum_{k=1}^c \mathcal{O}(s_k \log s_k) \le \mathcal{O}\left(\left(\sum_{k=1}^c s_k\right) \log n\right) = \mathcal{O}(n \log n)$$
* **Overall Time Complexity:**
  $$\mathcal{O}(m \cdot \alpha(n) + n \log n)$$

### Space Complexity
* **DSU Storage:** Arrays `parent` and `rank` require $2n \times \text{sizeof}(\text{int})$, which is $\mathcal{O}(n)$.
* **Grouping & Reassignment Storage:** Arrays `head`, `next`, `comp_size`, and `val_buffer` each require $n \times \text{sizeof}(\text{int})$, which is $\mathcal{O}(n)$.
* **Overall Space Complexity:** $\mathcal{O}(n)$.

---

## 6. Sample Output

### Input Configuration
```text
n = 6
Initial Permutation A = [5, 3, 2, 4, 1, 6]
Allowable Swaps (1-based indices):
- (1, 3): Swaps index 1 and 3 (0-based: 0 and 2)
- (3, 5): Swaps index 3 and 5 (0-based: 2 and 4)
- (2, 4): Swaps index 2 and 4 (0-based: 1 and 3)
```

### Component Breakdown
* **Component 1 (Indices $\{0, 2, 4\}$):** Initial values $\{5, 2, 1\} \rightarrow$ Sorted values $\{1, 2, 5\}$ assigned to indices $0, 2, 4$.
* **Component 2 (Indices $\{1, 3\}$):** Initial values $\{3, 4\} \rightarrow$ Sorted values $\{3, 4\}$ assigned to indices $1, 3$.
* **Component 3 (Index $\{5\}$):** Single element $\{6\}$ remains at index $5$.

### Execution Output
```text
Initial Permutation: [5, 3, 2, 4, 1, 6]
Lexicographically Smallest Achievable: [1, 3, 2, 4, 5, 6]
```
