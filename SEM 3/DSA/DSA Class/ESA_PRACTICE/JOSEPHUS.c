#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum size of the queue

// Circular Queue structure
struct CircularQueue {
    int arr[MAX];
    int front, rear, size;
};

// Initialize the circular queue
void initializeQueue(struct CircularQueue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

// Check if the queue is empty
int isEmpty(struct CircularQueue* q) {
    return (q->size == 0);
}

// Check if the queue is full
int isFull(struct CircularQueue* q) {
    return (q->size == MAX);
}

// Enqueue operation
void enqueue(struct CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue %d.\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
    q->size++;
}

// Dequeue operation
int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}

// Josephus Problem
int josephus(int n, int k) {
    struct CircularQueue q;
    initializeQueue(&q);

    // Enqueue all people (1 to n)
    for (int i = 1; i <= n; i++) {
        enqueue(&q, i);
    }

    // Simulate the elimination process
    while (q.size > 1) {
        // Skip (k-1) people
        for (int i = 1; i < k; i++) {
            int skipped = dequeue(&q);  // Dequeue
            enqueue(&q, skipped);       // Enqueue back
        }
        // Eliminate the k-th person
        int eliminated = dequeue(&q);
        printf("Eliminated: %d\n", eliminated);
    }

    // The last person remaining
    return dequeue(&q);
}

int main() {
    int n, k;
    printf("Enter the number of people (n): ");
    scanf("%d", &n);
    printf("Enter the step size (k): ");
    scanf("%d", &k);

    int winner = josephus(n, k);
    printf("The winner is: %d\n", winner);

    return 0;
}
