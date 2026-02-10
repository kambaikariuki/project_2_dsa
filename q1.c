#include <stdio.h>

#define MAX 50

typedef struct {
    char id;
    int priority;
} Job;

Job heap[MAX];
int size = 0;

/* Swap two jobs */
void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify down */
void heapifyDown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].priority > heap[largest].priority)
        largest = left;

    if (right < size && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapifyDown(largest);
    }
}

/* Heapify up */
void heapifyUp(int i) {
    if (i && heap[(i - 1) / 2].priority < heap[i].priority) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        heapifyUp((i - 1) / 2);
    }
}

/* Insert job */
void insertJob(char id, int priority) {
    heap[size].id = id;
    heap[size].priority = priority;
    size++;
    heapifyUp(size - 1);
}

/* Remove root (max) */
void removeMax() {
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
}

/* Print heap */
void printHeap() {
    for (int i = 0; i < size; i++)
        printf("(%c,%d) ", heap[i].id, heap[i].priority);
    printf("\n");
}

int main() {
    char ids[] = {'A','B','C','D','E','F','G','H','I','J','K'};
    int priorities[] = {42,17,93,28,65,81,54,60,99,73,88};

    /* Build heap */
    for (int i = 0; i < 11; i++)
        insertJob(ids[i], priorities[i]);

    printf("Initial Max-Heap:\n");
    printHeap();

    /* Insert urgent job */
    insertJob('L', 100);
    printf("After inserting urgent job (100):\n");
    printHeap();

    /* Remove urgent job */
    removeMax();
    printf("After removing urgent job:\n");
    printHeap();

    return 0;
}
