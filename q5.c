#include <stdio.h>
#include <limits.h>

#define V 10   // number of vertices
#define E 14   // number of edges

struct Edge {
    int src, dest, weight;
};

// Recursive function to print path from source to vertex j
void printPath(int parent[], int j) {
    if (parent[j] == -1) {      // reached source
        printf("%c", 'A' + j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %c", 'A' + j);
}

void bellmanFord(struct Edge edges[], int source) {
    int dist[V];
    int parent[V]; // store predecessor of each vertex

    // Step 1: Initialize distances and parents
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;  // no predecessor initially
    }
    dist[source] = 0;

    // Step 2: Relax edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u; // track predecessor
            }
        }
    }

    // Step 3: Check for negative cycles
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    // Step 4: Print shortest paths and costs
    printf("Shortest transaction paths and minimum cumulative costs from Branch A:\n\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%c : INF (no path)\n", 'A' + i);
        } else {
            printf("%c : %d | Path: ", 'A' + i, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    struct Edge edges[E] = {
        {0, 1, 4},   // A-B
        {0, 3, 16},  // A-D
        {1, 2, 6},   // B-C
        {1, 3, 6},   // B-D
        {1, 9, 7},   // B-J
        {2, 6, 9},   // C-G
        {3, 9, 0},   // D-J
        {3, 4, 7},   // D-E
        {9, 5, 3},   // J-F
        {5, 6, 0},   // F-G
        {5, 4, 10},  // F-E
        {5, 8, 10},  // F-I
        {4, 8, 2},   // E-I
        {6, 7, 13}   // G-H
    };

    bellmanFord(edges, 0); // source = A
    return 0;
}
