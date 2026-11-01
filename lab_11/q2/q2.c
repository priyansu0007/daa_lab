#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000

typedef struct Node {
    int v;
    struct Node* next;
} Node;

Node* adj[MAXV];
int dist[MAXV];
int owner[MAXV];

void addEdge(int u, int v) {
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->v = v;
    newNode1->next = adj[u];
    adj[u] = newNode1;

    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->v = u;
    newNode2->next = adj[v];
    adj[v] = newNode2;
}

void solveMultiSourceBFS(int V, int* hubs, int K, int R) {
    int queue[MAXV];
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }

    for (int i = 0; i < K; i++) {
        int h = hubs[i];
        queue[rear++] = h;
        dist[h] = 0;
        owner[h] = h;
    }

    while (front < rear) {
        int u = queue[front++];

        for (Node* edge = adj[u]; edge != NULL; edge = edge->next) {
            int v = edge->v;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[rear++] = v;
            } else if (dist[v] == dist[u] + 1) {
                if (owner[u] < owner[v]) {
                    owner[v] = owner[u];
                }
            }
        }
    }

    printf("--- Multi-Source BFS Results (Radius = %d) ---\n", R);
    for (int i = 0; i < V; i++) {
        if (dist[i] > R || dist[i] == -1) {
            owner[i] = -1;
        }
        printf("Node %d: Owner = %d, Distance = %d\n", i, owner[i], dist[i] > R ? -1 : dist[i]);
    }
}

int main() {
    int V = 6;
    for(int i = 0; i < V; i++) adj[i] = NULL;

    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 4);
    addEdge(4, 5);
    addEdge(1, 4);

    int hubs[] = {0, 5};
    int K = 2;
    int R = 2;

    solveMultiSourceBFS(V, hubs, K, R);
    return 0;
}
