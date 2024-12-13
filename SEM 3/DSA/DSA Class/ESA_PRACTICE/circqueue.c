#include <stdio.h>
#define MAX 5

typedef struct {
    int arr[MAX];
    int front, rear;
} CircularQueue;

// Initialize the circular queue
void initQueue(CircularQueue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the circular queue is empty
int isEmpty(CircularQueue* q) {
    return q->front == -1;
}

// Check if the circular queue is full
int isFull(CircularQueue* q) {
    return (q->rear + 1) % MAX == q->front;
}

// Enqueue an element
void enqueue(CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue overflow! Cannot enqueue %d.\n", value);
        return;
    }
    if (isEmpty(q)) q->front = 0;  // Set front for first element
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
    printf("Enqueued %d.\n", value);
}

// Dequeue an element
int dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;  // Reset queue when empty
    } else {
        q->front = (q->front + 1) % MAX;
    }
    printf("Dequeued %d.\n", value);
    return value;
}

// Display the circular queue
void display(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements:\n");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);

    dequeue(&q);
    display(&q);

    return 0;
}
