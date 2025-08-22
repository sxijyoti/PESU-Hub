// Given a circular queue of n tasks, each represented by a unique position number from 1 to n, and a number k, 
// representing the step count to process every k-th task, 
// determine the position of the last remaining task in the queue after all others have been processed.

#include <stdio.h>
#include <stdlib.h>

#define MAX 500

// Circular Queue structure
typedef struct {
   int data[MAX];
   int front;
   int rear;
   int size;
} CircularQueue;

// Function to initialize the circular queue
void initializeQueue(CircularQueue* q) {
   q->front = 0;
   q->rear = -1;
   q->size = 0;
}

// Function to check if the queue is empty
int isEmpty(CircularQueue* q) {
   return q->size == 0;
}

// Function to check if the queue is full
int isFull(CircularQueue* q) {
   return q->size == MAX;
}

// Function to enqueue an element
void enqueue(CircularQueue* q, int value) {
   if (isFull(q)) {
      
       return;
   }
   q->rear = (q->rear + 1) % MAX;
   q->data[q->rear] = value;
   q->size++;
}

// Function to dequeue an element
int dequeue(CircularQueue* q) {
   if (isEmpty(q)) {
      
       return -1;
   }
   int value = q->data[q->front];
   q->front = (q->front + 1) % MAX;
   q->size--;
   return value;
}

// Function to find the position of the last remaining task

int findLastTask(CircularQueue* q, int k) {

//Write the code here
    
    while (q->size > 1) {
        for (int i = 1; i < k; ++i) {
            int task = dequeue(q);
            enqueue(q,task);
    }
    dequeue(q);
}
    return dequeue(q);
  
}

int main() {
   int n, k;
  
   // Input number of tasks and step count
   scanf("%d %d", &n, &k);
  
   // Create and initialize the circular queue
   CircularQueue queue;
   initializeQueue(&queue);

   // Enqueue all tasks
   for (int i = 1; i <= n; i++) {
       enqueue(&queue, i);
   }

   // Find the last remaining task
   int result = findLastTask(&queue, k);
  
   // Output the result
   printf("%d\n", result);
  
   return 0;
}