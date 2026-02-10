#include <stdio.h>
#include <string.h>

#define MAX 50

typedef struct {
    char name[20];
    int risk;
} Passenger;

Passenger heap[MAX];
int size = 0;

/* Swap two heap nodes */
void swap(Passenger *a, Passenger *b) {
    Passenger temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify down */
void heapifyDown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].risk > heap[largest].risk)
        largest = left;

    if (right < size && heap[right].risk > heap[largest].risk)
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapifyDown(largest);
    }
}

/* Heapify up */
void heapifyUp(int i) {
    if (i > 0 && heap[(i - 1) / 2].risk < heap[i].risk) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        heapifyUp((i - 1) / 2);
    }
}

/* Insert passenger */
void insertPassenger(char name[], int risk) {
    strcpy(heap[size].name, name);
    heap[size].risk = risk;
    size++;
    heapifyUp(size - 1);
}

/* Remove highest-risk passenger */
void removeMax() {
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
}

/* Extract max (priority queue behavior) */
Passenger extractMax() {
    Passenger max = heap[0];
    removeMax();
    return max;
}

/* Print heap */
void printHeap() {
    for (int i = 0; i < size; i++)
        printf("(%s, %d) ", heap[i].name, heap[i].risk);
    printf("\n");
}

int main() {
    insertPassenger("Alice", 45);
    insertPassenger("Brian", 72);
    insertPassenger("Chen", 60);
    insertPassenger("Fatima", 85);
    insertPassenger("Noah", 55);
    insertPassenger("Sofia", 90);

    printf("Initial Max-Heap:\n");
    printHeap();

    insertPassenger("Zara", 98);
    printf("\nAfter inserting passenger with risk 98:\n");
    printHeap();

    removeMax();
    printf("\nAfter removing passenger with risk 98:\n");
    printHeap();

    printf("\nScreening order (priority queue):\n");
    while (size > 0) {
        Passenger p = extractMax();
        printf("%s (%d)\n", p.name, p.risk);
    }

    return 0;
}
