#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *parent;
    int *rank;
    int n;
} DSU;

DSU* dsu_create(int n) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

void dsu_free(DSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }
}

int dsu_find(DSU *dsu, int i) {
    if (dsu->parent[i] == i) {
        return i;
    }
    return dsu->parent[i] = dsu_find(dsu, dsu->parent[i]);
}

void dsu_union(DSU *dsu, int u, int v) {
    int root_u = dsu_find(dsu, u);
    int root_v = dsu_find(dsu, v);

    if (root_u != root_v) {
        if (dsu->rank[root_u] < dsu->rank[root_v]) {
            dsu->parent[root_u] = root_v;
        } else if (dsu->rank[root_u] > dsu->rank[root_v]) {
            dsu->parent[root_v] = root_u;
        } else {
            dsu->parent[root_v] = root_u;
            dsu->rank[root_u]++;
        }
    }
}

static int compare_ints(const void *a, const void *b) {
    int val_a = *(const int*)a;
    int val_b = *(const int*)b;
    return (val_a > val_b) - (val_a < val_b);
}

// Computes the lexicographically smallest permutation in-place
void lexicographically_smallest_permutation(int n, int *A, int m, int edges[][2]) {
    DSU *dsu = dsu_create(n);

    // 1. Unify index positions connected by allowable swaps
    for (int i = 0; i < m; i++) {
        // Convert 1-based edge indices to 0-based
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;
        if (u >= 0 && u < n && v >= 0 && v < n) {
            dsu_union(dsu, u, v);
        }
    }

    // 2. Group indices into components in naturally ascending order
    int *head = (int*)malloc(n * sizeof(int));
    int *next = (int*)malloc(n * sizeof(int));
    int *comp_size = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }

    // Iterating backwards ensures traversal from head yields increasing indices
    for (int i = n - 1; i >= 0; i--) {
        int root = dsu_find(dsu, i);
        next[i] = head[root];
        head[root] = i;
        comp_size[root]++;
    }

    // 3. Extract, sort, and place values for each component
    int *val_buffer = (int*)malloc(n * sizeof(int));

    for (int r = 0; r < n; r++) {
        if (head[r] == -1) continue;

        int size = comp_size[r];
        int idx = 0;

        // Collect values from the component's indices
        for (int curr = head[r]; curr != -1; curr = next[curr]) {
            val_buffer[idx++] = A[curr];
        }

        // Sort values ascending
        qsort(val_buffer, size, sizeof(int), compare_ints);

        // Assign back to indices in ascending order
        idx = 0;
        for (int curr = head[r]; curr != -1; curr = next[curr]) {
            A[curr] = val_buffer[idx++];
        }
    }

    free(val_buffer);
    free(comp_size);
    free(next);
    free(head);
    dsu_free(dsu);
}

int main(void) {
    int n = 6;
    // Permutation of numbers 1...n
    int A[] = {5, 3, 2, 4, 1, 6};

    // 1-based allowable swaps: (u, v)
    int edges[][2] = {
        {1, 3}, // Swap index 1 and 3 (0-based: 0 and 2)
        {3, 5}, // Swap index 3 and 5 (0-based: 2 and 4)
        {2, 4}  // Swap index 2 and 4 (0-based: 1 and 3)
    };
    int m = sizeof(edges) / sizeof(edges[0]);

    printf("Initial Permutation: [");
    for (int i = 0; i < n; i++) {
        printf("%d%s", A[i], (i == n - 1) ? "" : ", ");
    }
    printf("]\n");

    lexicographically_smallest_permutation(n, A, m, edges);

    printf("Lexicographically Smallest Achievable: [");
    for (int i = 0; i < n; i++) {
        printf("%d%s", A[i], (i == n - 1) ? "" : ", ");
    }
    printf("]\n");

    return 0;
}