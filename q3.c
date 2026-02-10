#include <stdio.h>
#include <stdlib.h>

#define V 7   // number of vertices
#define E 8   // number of edges

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Find set (with path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare edges by weight (for qsort)
int compare(const void *a, const void *b) {
    struct Edge *e1 = (struct Edge *)a;
    struct Edge *e2 = (struct Edge *)b;
    return e1->weight - e2->weight;
}

int main() {
    struct Edge edges[E] = {
        {0, 1, 6},   // A-B
        {1, 3, 5},   // B-D
        {1, 2, 11},  // B-C
        {2, 3, 17},  // C-D
        {2, 6, 25},  // C-G
        {3, 4, 22},  // D-E
        {4, 5, 10},  // E-F
        {5, 6, 22}   // F-G
    };

    // Sort edges by weight
    qsort(edges, E, sizeof(edges[0]), compare);

    struct Subset subsets[V];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    int totalCost = 0;
    int count = 0;

    printf("Edges in the Minimum Spanning Tree:\n");

    for (int i = 0; i < E && count < V - 1; i++) {
        int x = find(subsets, edges[i].src);
        int y = find(subsets, edges[i].dest);

        if (x != y) {
            printf("%c - %c : %d\n",
                   edges[i].src + 'A',
                   edges[i].dest + 'A',
                   edges[i].weight);

            totalCost += edges[i].weight;
            Union(subsets, x, y);
            count++;
        }
    }

    printf("Total cost of MST = %d\n", totalCost);

    return 0;
}
