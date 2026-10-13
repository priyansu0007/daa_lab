#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Forward star edge representation
typedef struct {
    int *head;
    int *to;
    int *next;
    int edge_count;
} Graph;

Graph* graph_create(int V, int max_edges) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->head = (int*)malloc(V * sizeof(int));
    g->to = (int*)malloc(2 * max_edges * sizeof(int));
    g->next = (int*)malloc(2 * max_edges * sizeof(int));
    g->edge_count = 0;

    for (int i = 0; i < V; i++) {
        g->head[i] = -1;
    }
    return g;
}

void graph_add_edge(Graph *g, int u, int v) {
    g->to[g->edge_count] = v;
    g->next[g->edge_count] = g->head[u];
    g->head[u] = g->edge_count++;

    g->to[g->edge_count] = u;
    g->next[g->edge_count] = g->head[v];
    g->head[v] = g->edge_count++;
}

void graph_free(Graph *g) {
    if (g) {
        free(g->head);
        free(g->to);
        free(g->next);
        free(g);
    }
}

// Disjoint Set Union with component sums
typedef struct {
    int *parent;
    int *rank;
    long long *comp_sum;
    bool *is_active;
} DSU;

DSU* dsu_create(int V, const long long *weights) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(V * sizeof(int));
    dsu->rank = (int*)calloc(V, sizeof(int));
    dsu->comp_sum = (long long*)malloc(V * sizeof(long long));
    dsu->is_active = (bool*)calloc(V, sizeof(bool));

    for (int i = 0; i < V; i++) {
        dsu->parent[i] = i;
        dsu->comp_sum[i] = weights[i];
    }
    return dsu;
}

void dsu_free(DSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu->comp_sum);
        free(dsu->is_active);
        free(dsu);
    }
}

int dsu_find(DSU *dsu, int v) {
    if (dsu->parent[v] != v) {
        dsu->parent[v] = dsu_find(dsu, dsu->parent[v]);
    }
    return dsu->parent[v];
}

// Unites sets containing u and v; returns root of merged component
int dsu_union(DSU *dsu, int u, int v) {
    int root_u = dsu_find(dsu, u);
    int root_v = dsu_find(dsu, v);

    if (root_u == root_v) {
        return root_u;
    }

    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        dsu->parent[root_u] = root_v;
        dsu->comp_sum[root_v] += dsu->comp_sum[root_u];
        return root_v;
    } else if (dsu->rank[root_u] > dsu->rank[root_v]) {
        dsu->parent[root_v] = root_u;
        dsu->comp_sum[root_u] += dsu->comp_sum[root_v];
        return root_u;
    } else {
        dsu->parent[root_v] = root_u;
        dsu->comp_sum[root_u] += dsu->comp_sum[root_v];
        dsu->rank[root_u]++;
        return root_u;
    }
}

// Solves offline decremental component sum queries
void solve_reverse_deletions(int V, int E, const long long *weights, 
                             int edges[][2], const int *deletion_order, 
                             long long *out_answers) {
    Graph *g = graph_create(V, E);
    for (int i = 0; i < E; i++) {
        graph_add_edge(g, edges[i][0], edges[i][1]);
    }

    DSU *dsu = dsu_create(V, weights);
    long long current_max = 0;

    // After deleting the last vertex (all vertices gone), maximum sum is 0
    out_answers[V - 1] = 0;

    // Process vertices in reverse deletion order
    for (int k = V - 1; k >= 1; k--) {
        int u = deletion_order[k];
        dsu->is_active[u] = true;

        if (dsu->comp_sum[u] > current_max) {
            current_max = dsu->comp_sum[u];
        }

        // Connect u to its already active neighbors
        for (int e = g->head[u]; e != -1; e = g->next[e]) {
            int v = g->to[e];
            if (dsu->is_active[v]) {
                int merged_root = dsu_union(dsu, u, v);
                if (dsu->comp_sum[merged_root] > current_max) {
                    current_max = dsu->comp_sum[merged_root];
                }
            }
        }

        // Record answer after step k - 1 deletion
        out_answers[k - 1] = current_max;
    }

    dsu_free(dsu);
    graph_free(g);
}

int main(void) {
    int V = 5;
    int E = 5;
    long long weights[] = {10, 20, 30, 40, 50};

    // Graph edges: (u, v)
    int edges[][2] = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {0, 4}
    };

    // Deletion sequence P: 0-indexed vertex indices
    int P[] = {2, 0, 3, 4, 1};

    long long answers[5];
    solve_reverse_deletions(V, E, weights, edges, P, answers);

    printf("Sequential Vertex Deletions and Max Remaining Component Sum:\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("After deleting vertex p_%d (vertex %d): Max Component Sum = %lld\n", 
               i + 1, P[i], answers[i]);
    }

    return 0;
}