#include <stdio.h>
#define MAX 5

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

// Initialize the queue
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == -1;
}

// Check if the queue is full
int isFull(Queue* q) {
    return q->rear == MAX - 1;
}

// Enqueue an element
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue overflow! Cannot enqueue %d.\n", value);
        return;
    }
    if (isEmpty(q)) q->front = 0;  // Set front for first element
    q->arr[++q->rear] = value;
    printf("Enqueued %d.\n", value);
}

// Dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    int value = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;  // Reset queue when empty
    } else {
        q->front++;
    }
    printf("Dequeued %d.\n", value);
    return value;
}

// Display the queue
void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements:\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);

    dequeue(&q);
    display(&q);

    return 0;
}
