#include <stdio.h>

#define N 7

char nodes[N] = {'A','B','C','D','E','F','G'};

/* Adjacency matrix with weights */
int graph[N][N] = {
    {0, 6, 0, 0, 0, 0, 0},
    {6, 0,11, 5, 0, 0, 0},
    {0,11, 0,17, 0, 0,25},
    {0, 5,17, 0,22, 0, 0},
    {0, 0, 0,22, 0,10, 0},
    {0, 0, 0, 0,10, 0,22},
    {0, 0,25, 0, 0,22, 0}
};

int getIndex(char c) {
    for (int i = 0; i < N; i++)
        if (nodes[i] == c) return i;
    return -1;
}

int main() {
    char start;
    printf("Enter suspected workstation: ");
    scanf(" %c", &start);

    int s = getIndex(start);
    if (s == -1) {
        printf("Invalid workstation\n");
        return 0;
    }

    printf("\nDirectly connected workstations:\n");

    int maxRisk = 0;
    char riskyNode = '-';

    for (int i = 0; i < N; i++) {
        if (graph[s][i] > 0) {
            printf("%c (data transfer = %d)\n", nodes[i], graph[s][i]);

            if (graph[s][i] > maxRisk) {
                maxRisk = graph[s][i];
                riskyNode = nodes[i];
            }
        }
    }

    printf("\nHighest risk connection: %c (%d minutes)\n",
           riskyNode, maxRisk);

    return 0;
}
