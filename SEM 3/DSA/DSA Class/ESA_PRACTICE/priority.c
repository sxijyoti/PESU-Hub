#include <stdio.h>
#define MAX 5

typedef struct {
    int arr[MAX];
    int priorities[MAX];
    int size;
} PriorityQueue;

// Initialize the priority queue
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Enqueue an element with priority
void enqueue(PriorityQueue* pq, int value, int priority) {
    if (pq->size == MAX) {
        printf("Priority Queue overflow! Cannot enqueue %d.\n", value);
        return;
    }
    int i = pq->size - 1;
    while (i >= 0 && pq->priorities[i] > priority) {
        pq->arr[i + 1] = pq->arr[i];
        pq->priorities[i + 1] = pq->priorities[i];
        i--;
    }
    pq->arr[i + 1] = value;
    pq->priorities[i + 1] = priority;
    pq->size++;
    printf("Enqueued %d with priority %d.\n", value, priority);
}

// Dequeue an element with the highest priority
int dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = pq->arr[0];
    for (int i = 1; i < pq->size; i++) {
        pq->arr[i - 1] = pq->arr[i];
        pq->priorities[i - 1] = pq->priorities[i];
    }
    pq->size--;
    printf("Dequeued %d.\n", value);
    return value;
}

// Display the priority queue
void display(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority Queue is empty.\n");
        return;
    }
    printf("Priority Queue elements:\n");
    for (int i = 0; i < pq->size; i++) {
        printf("%d (Priority: %d)\n", pq->arr[i], pq->priorities[i]);
    }
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    enqueue(&pq, 10, 2);
    enqueue(&pq, 20, 1);
    enqueue(&pq, 30, 3);
    display(&pq);

    dequeue(&pq);
    display(&pq);

    return 0;
}
