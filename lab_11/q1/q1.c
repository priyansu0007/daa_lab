#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXV 1000
#define INF INT_MAX

typedef struct Node {
    int v, w;
    struct Node* next;
} Node;

Node* adj[MAXV];

void addEdge(int u, int v, int w) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->w = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void solve01BFS(int V, int start, int C) {
    int dist[MAXV][2];
    for (int i = 0; i < V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    int deque[MAXV * 4][2];
    int front = MAXV * 2, rear = MAXV * 2;

    deque[rear][0] = start;
    deque[rear][1] = 0;
    rear++;
    dist[start][0] = 0;

    while (front < rear) {
        int u = deque[front][0];
        int p = deque[front][1];
        front++;

        for (Node* edge = adj[u]; edge != NULL; edge = edge->next) {
            int v = edge->v;
            int w = edge->w;
            int np = (p + w) % 2;
            int n_cost = dist[u][p] + w;

            if (n_cost < dist[v][np]) {
                dist[v][np] = n_cost;
                if (w == 0) {
                    front--;
                    deque[front][0] = v;
                    deque[front][1] = np;
                } else {
                    deque[rear][0] = v;
                    deque[rear][1] = np;
                    rear++;
                }
            }
        }
    }

    printf("--- 0-1 BFS Results ---\n");
    for (int i = 0; i < V; i++) {
        int ans0 = dist[i][0];
        int ans1 = dist[i][1] == INF ? INF : dist[i][1] + C;
        int ans = ans0 < ans1 ? ans0 : ans1;
        if (ans == INF) {
            printf("Node %d is unreachable\n", i);
        } else {
            printf("Node %d: Minimum Cost = %d\n", i, ans);
        }
    }
}

int main() {
    int V = 4;
    int start_node = 0;
    int penalty_C = 5;

    for(int i = 0; i < V; i++) adj[i] = NULL;

    // Example Graph: (u, v, weight)
    addEdge(0, 1, 1);
    addEdge(1, 2, 0);
    addEdge(0, 2, 0);
    addEdge(2, 3, 1);

    solve01BFS(V, start_node, penalty_C);
    return 0;
}
