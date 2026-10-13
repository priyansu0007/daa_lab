#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    EDGE_ACCEPTED_TREE,
    EDGE_ACCEPTED_EVEN_CYCLE,
    EDGE_REJECTED_ODD_CYCLE
} EdgeResult;

typedef struct {
    int *parent;
    int *rank;
    int *parity; // 0: same color as parent, 1: opposite color
    int num_vertices;
} BipartiteDSU;

BipartiteDSU* dsu_create(int n) {
    BipartiteDSU *dsu = (BipartiteDSU*)malloc(sizeof(BipartiteDSU));
    dsu->num_vertices = n;
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)calloc(n, sizeof(int));
    dsu->parity = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

void dsu_free(BipartiteDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu->parity);
        free(dsu);
    }
}

// Find representative with path compression and parity propagation
int dsu_find(BipartiteDSU *dsu, int v) {
    if (v != dsu->parent[v]) {
        int original_parent = dsu->parent[v];
        dsu->parent[v] = dsu_find(dsu, original_parent);
        dsu->parity[v] ^= dsu->parity[original_parent];
    }
    return dsu->parent[v];
}

// Online edge-arrival evaluation
EdgeResult dsu_add_edge(BipartiteDSU *dsu, int u, int v) {
    int root_u = dsu_find(dsu, u);
    int root_v = dsu_find(dsu, v);

    if (root_u == root_v) {
        // In the same connected component
        if (dsu->parity[u] == dsu->parity[v]) {
            // Same color: edge introduces an odd-length cycle
            return EDGE_REJECTED_ODD_CYCLE;
        }
        // Opposite color: edge introduces an even-length cycle
        return EDGE_ACCEPTED_EVEN_CYCLE;
    }

    // Disjoint components: union by rank
    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        dsu->parent[root_u] = root_v;
        dsu->parity[root_u] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
    } else {
        dsu->parent[root_v] = root_u;
        dsu->parity[root_v] = dsu->parity[u] ^ dsu->parity[v] ^ 1;
        if (dsu->rank[root_u] == dsu->rank[root_v]) {
            dsu->rank[root_u]++;
        }
    }

    return EDGE_ACCEPTED_TREE;
}

int main(void) {
    int V = 6;
    BipartiteDSU *dsu = dsu_create(V);

    // Online stream of incoming edges: (u, v)
    int stream[][2] = {
        {0, 1}, // Tree edge
        {1, 2}, // Tree edge
        {2, 3}, // Tree edge
        {3, 0}, // Even cycle (length 4) -> ACCEPT
        {0, 2}, // Odd cycle (triangle 0-1-2) -> REJECT
        {4, 5}, // New component tree edge
        {3, 4}, // Merges {0,1,2,3} and {4,5}
        {0, 5}, // Even cycle (length 6: 0-1-2-3-4-5) -> ACCEPT
        {1, 5}  // Odd cycle (length 5: 1-2-3-4-5) -> REJECT
    };

    int num_edges = sizeof(stream) / sizeof(stream[0]);

    printf("Online Graph Bipartiteness Validation (V = %d):\n", V);
    printf("--------------------------------------------------\n");

    for (int i = 0; i < num_edges; i++) {
        int u = stream[i][0];
        int v = stream[i][1];
        EdgeResult res = dsu_add_edge(dsu, u, v);

        printf("Edge (%d, %d): ", u, v);
        switch (res) {
            case EDGE_ACCEPTED_TREE:
                printf("[ACCEPTED] Added spanning forest edge.\n");
                break;
            case EDGE_ACCEPTED_EVEN_CYCLE:
                printf("[ACCEPTED] Forms an even cycle (bipartiteness preserved).\n");
                break;
            case EDGE_REJECTED_ODD_CYCLE:
                printf("[REJECTED] Violates bipartiteness (introduces odd cycle).\n");
                break;
        }
    }

    dsu_free(dsu);
    return 0;
}