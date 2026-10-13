#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long weight;
    int root_id;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* heap_create(int capacity) {
    MaxHeap *h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heap_free(MaxHeap *h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

static void heap_swap(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heap_push(MaxHeap *h, long long weight, int root_id) {
    if (h->size >= h->capacity) return;
    int i = h->size++;
    h->data[i].weight = weight;
    h->data[i].root_id = root_id;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent].weight < h->data[i].weight) {
            heap_swap(&h->data[parent], &h->data[i]);
            i = parent;
        } else {
            break;
        }
    }
}

void heap_pop(MaxHeap *h) {
    if (h->size <= 0) return;
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (h->data[left].weight > h->data[largest].weight) {
            largest = left;
        }
        if (right < h->size && h->data[right].weight > h->data[largest].weight) {
            largest = right;
        }
        if (largest != i) {
            heap_swap(&h->data[i], &h->data[largest]);
            i = largest;
        } else {
            break;
        }
    }
}

typedef struct {
    int V;
    int K;
    int *parent;
    int *rank;
    int *comp_size;
    long long *comp_weight;
    MaxHeap *heap;
} ConstrainedGraphDSU;

ConstrainedGraphDSU* dsu_create(int V, int K, const long long *vertex_weights) {
    ConstrainedGraphDSU *dsu = (ConstrainedGraphDSU*)malloc(sizeof(ConstrainedGraphDSU));
    dsu->V = V;
    dsu->K = K;
    dsu->parent = (int*)malloc(V * sizeof(int));
    dsu->rank = (int*)calloc(V, sizeof(int));
    dsu->comp_size = (int*)malloc(V * sizeof(int));
    dsu->comp_weight = (long long*)malloc(V * sizeof(long long));

    // At most V initial nodes + (V - 1) merges ever inserted
    dsu->heap = heap_create(2 * V);

    for (int i = 0; i < V; i++) {
        dsu->parent[i] = i;
        dsu->comp_size[i] = 1;
        dsu->comp_weight[i] = vertex_weights[i];
        if (1 <= K) {
            heap_push(dsu->heap, vertex_weights[i], i);
        }
    }
    return dsu;
}

void dsu_free(ConstrainedGraphDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu->comp_size);
        free(dsu->comp_weight);
        heap_free(dsu->heap);
        free(dsu);
    }
}

int dsu_find(ConstrainedGraphDSU *dsu, int v) {
    if (dsu->parent[v] != v) {
        dsu->parent[v] = dsu_find(dsu, dsu->parent[v]);
    }
    return dsu->parent[v];
}

// Online addition of an edge (u, v) with weight w_edge
void dsu_add_edge(ConstrainedGraphDSU *dsu, int u, int v, double w_edge) {
    (void)w_edge; // Edge weight preserved in signature for stream metadata
    int root_u = dsu_find(dsu, u);
    int root_v = dsu_find(dsu, v);

    if (root_u == root_v) {
        return; // Cycle within existing component; sizes and weights remain unchanged
    }

    // Union by rank
    int merged_root, child_root;
    if (dsu->rank[root_u] < dsu->rank[root_v]) {
        merged_root = root_v;
        child_root = root_u;
    } else {
        merged_root = root_u;
        child_root = root_v;
        if (dsu->rank[root_u] == dsu->rank[root_v]) {
            dsu->rank[root_u]++;
        }
    }

    dsu->parent[child_root] = merged_root;
    dsu->comp_size[merged_root] += dsu->comp_size[child_root];
    dsu->comp_weight[merged_root] += dsu->comp_weight[child_root];

    // If new merged component satisfies size constraint, register candidate
    if (dsu->comp_size[merged_root] <= dsu->K) {
        heap_push(dsu->heap, dsu->comp_weight[merged_root], merged_root);
    }
}

// Queries the maximum component weight with size <= K
bool dsu_get_max_weight(ConstrainedGraphDSU *dsu, long long *max_weight) {
    while (dsu->heap->size > 0) {
        HeapNode top = dsu->heap->data[0];

        // Validate top entry:
        // 1. Must still be a root
        // 2. Component size must be <= K
        // 3. Stored weight must match root's current weight
        if (dsu->parent[top.root_id] == top.root_id &&
            dsu->comp_size[top.root_id] <= dsu->K &&
            dsu->comp_weight[top.root_id] == top.weight) {
            *max_weight = top.weight;
            return true;
        }

        // Drop stale entry
        heap_pop(dsu->heap);
    }
    return false; // No component satisfies size <= K
}

int main(void) {
    int V = 5;
    int K = 2; // Maximum component size threshold
    long long vertex_weights[] = {10, 20, 5, 40, 15};

    ConstrainedGraphDSU *dsu = dsu_create(V, K, vertex_weights);

    // Stream of incoming edges: {u, v, edge_weight}
    double edge_stream[][3] = {
        {0, 1, 2.5},  // Merges {0} and {1}: size 2 <= K=2, weight = 10 + 20 = 30
        {2, 3, 1.0},  // Merges {2} and {3}: size 2 <= K=2, weight = 5 + 40 = 45
        {0, 2, 4.0},  // Merges {0,1} and {2,3}: size 4 > K=2 -> Disqualified!
        {3, 1, 0.5},  // Redundant cycle edge
        {3, 4, 3.2}   // Merges {4} into {0,1,2,3}: size 5 > K=2
    };

    int num_edges = sizeof(edge_stream) / sizeof(edge_stream[0]);
    long long max_w;

    printf("Online Component Weight Maintenance (V = %d, K = %d)\n", V, K);
    printf("Initial vertex weights: [0]:10, [1]:20, [2]:5, [3]:40, [4]:15\n");
    printf("-------------------------------------------------------------\n");

    if (dsu_get_max_weight(dsu, &max_w)) {
        printf("Initial state: Max weight component (size <= %d) = %lld\n", K, max_w);
    }

    for (int i = 0; i < num_edges; i++) {
        int u = (int)edge_stream[i][0];
        int v = (int)edge_stream[i][1];
        double w_e = edge_stream[i][2];

        dsu_add_edge(dsu, u, v, w_e);

        if (dsu_get_max_weight(dsu, &max_w)) {
            printf("After adding edge (%d, %d, wt=%.1f) -> Max component weight: %lld\n", 
                   u, v, w_e, max_w);
        } else {
            printf("After adding edge (%d, %d, wt=%.1f) -> No component with size <= %d\n", 
                   u, v, w_e, K);
        }
    }

    dsu_free(dsu);
    return 0;
}