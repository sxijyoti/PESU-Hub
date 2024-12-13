#include <stdio.h>
#include <stdlib.h>
#define SIZE 10  // Maximum size of the deque

struct Deque {
    int arr[SIZE];
    int front;
    int rear;
};

// Initialize the deque
void initializeDeque(struct Deque* dq) {
    dq->front = -1;
    dq->rear = -1;
}

// Check if deque is full
int isFull(struct Deque* dq) {
    return ((dq->front == 0 && dq->rear == SIZE - 1) || (dq->front == dq->rear + 1));
}

// Check if deque is empty
int isEmpty(struct Deque* dq) {
    return (dq->front == -1);
}

// Insert at the front
void insertFront(struct Deque* dq, int data) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert at front.\n");
        return;
    }
    if (isEmpty(dq)) {  // First element
        dq->front = dq->rear = 0;
    } else if (dq->front == 0) {
        dq->front = SIZE - 1;  // Wrap around
    } else {
        dq->front--;
    }
    dq->arr[dq->front] = data;
    printf("Inserted %d at the front.\n", data);
}

// Insert at the rear
void insertRear(struct Deque* dq, int data) {
    if (isFull(dq)) {
        printf("Deque is full. Cannot insert at rear.\n");
        return;
    }
    if (isEmpty(dq)) {  // First element
        dq->front = dq->rear = 0;
    } else if (dq->rear == SIZE - 1) {
        dq->rear = 0;  // Wrap around
    } else {
        dq->rear++;
    }
    dq->arr[dq->rear] = data;
    printf("Inserted %d at the rear.\n", data);
}

// Delete from the front
void deleteFront(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from front.\n");
        return;
    }
    printf("Deleted %d from the front.\n", dq->arr[dq->front]);
    if (dq->front == dq->rear) {  // Single element
        dq->front = dq->rear = -1;
    } else if (dq->front == SIZE - 1) {
        dq->front = 0;  // Wrap around
    } else {
        dq->front++;
    }
}

// Delete from the rear
void deleteRear(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty. Cannot delete from rear.\n");
        return;
    }
    printf("Deleted %d from the rear.\n", dq->arr[dq->rear]);
    if (dq->front == dq->rear) {  // Single element
        dq->front = dq->rear = -1;
    } else if (dq->rear == 0) {
        dq->rear = SIZE - 1;  // Wrap around
    } else {
        dq->rear--;
    }
}

// Display the deque
void display(struct Deque* dq) {
    if (isEmpty(dq)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque elements: ");
    int i = dq->front;
    while (1) {
        printf("%d ", dq->arr[i]);
        if (i == dq->rear)
            break;
        i = (i + 1) % SIZE;  // Circular increment
    }
    printf("\n");
}

int main() {
    struct Deque dq;
    initializeDeque(&dq);

    insertRear(&dq, 10);
    insertRear(&dq, 20);
    insertFront(&dq, 5);
    insertFront(&dq, 1);
    display(&dq);

    deleteFront(&dq);
    deleteRear(&dq);
    display(&dq);

    return 0;
}


// LINKEDLIST

// #include <stdio.h>
// #include <stdlib.h>

// // Node structure
// struct Node {
//     int data;
//     struct Node* next;
//     struct Node* prev;
// };

// // Deque structure
// struct Deque {
//     struct Node* front;
//     struct Node* rear;
// };

// // Initialize the deque
// void initializeDeque(struct Deque* dq) {
//     dq->front = NULL;
//     dq->rear = NULL;
// }

// // Check if deque is empty
// int isEmpty(struct Deque* dq) {
//     return (dq->front == NULL);
// }

// // Insert at the front
// void insertFront(struct Deque* dq, int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->next = dq->front;
//     newNode->prev = NULL;

//     if (isEmpty(dq)) {
//         dq->rear = newNode;
//     } else {
//         dq->front->prev = newNode;
//     }
//     dq->front = newNode;
//     printf("Inserted %d at the front.\n", data);
// }

// // Insert at the rear
// void insertRear(struct Deque* dq, int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->next = NULL;
//     newNode->prev = dq->rear;

//     if (isEmpty(dq)) {
//         dq->front = newNode;
//     } else {
//         dq->rear->next = newNode;
//     }
//     dq->rear = newNode;
//     printf("Inserted %d at the rear.\n", data);
// }

// // Delete from the front
// void deleteFront(struct Deque* dq) {
//     if (isEmpty(dq)) {
//         printf("Deque is empty. Cannot delete from front.\n");
//         return;
//     }
//     struct Node* temp = dq->front;
//     printf("Deleted %d from the front.\n", temp->data);

//     dq->front = dq->front->next;
//     if (dq->front == NULL) {
//         dq->rear = NULL;
//     } else {
//         dq->front->prev = NULL;
//     }
//     free(temp);
// }

// // Delete from the rear
// void deleteRear(struct Deque* dq) {
//     if (isEmpty(dq)) {
//         printf("Deque is empty. Cannot delete from rear.\n");
//         return;
//     }
//     struct Node* temp = dq->rear;
//     printf("Deleted %d from the rear.\n", temp->data);

//     dq->rear = dq->rear->prev;
//     if (dq->rear == NULL) {
//         dq->front = NULL;
//     } else {
//         dq->rear->next = NULL;
//     }
//     free(temp);
// }

// // Display the deque
// void display(struct Deque* dq) {
//     if (isEmpty(dq)) {
//         printf("Deque is empty.\n");
//         return;
//     }
//     printf("Deque elements: ");
//     struct Node* temp = dq->front;
//     while (temp != NULL) {
//         printf("%d ", temp->data);
//         temp = temp->next;
//     }
//     printf("\n");
// }

// int main() {
//     struct Deque dq;
//     initializeDeque(&dq);

//     insertRear(&dq, 10);
//     insertRear(&dq, 20);
//     insertFront(&dq, 5);
//     insertFront(&dq, 1);
//     display(&dq);

//     deleteFront(&dq);
//     deleteRear(&dq);
//     display(&dq);

//     return 0;
// }
