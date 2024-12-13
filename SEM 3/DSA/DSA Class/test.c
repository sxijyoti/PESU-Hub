#include <stdio.h>
#include <stdlib.h>

// Define the structure of a Node
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node* NODE;

// Function to create a new node
NODE createNode(int data) {
    NODE newNode = (NODE)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
NODE insertEnd(NODE head, int data) {
    NODE newNode = createNode(data);
    if (head == NULL) {
        return newNode; // If the list is empty, the new node becomes the head
    }
    NODE temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to calculate the length of the doubly linked list
int printlen(NODE head) {
    NODE temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

// Function to print the list
void printList(NODE head) {
    NODE temp = head;
    printf("Doubly Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to test the doubly linked list
int main() {
    NODE head = NULL;

    // Create the DLL with the elements 1, 3, 2, 8, 7, 6
    // head = insertEnd(head, 1);
    // head = insertEnd(head, 3);
    // head = insertEnd(head, 2);
    // head = insertEnd(head, 8);
    // head = insertEnd(head, 7);
    // head = insertEnd(head, 6);

    // Print the list
    printList(head);

    // Calculate and print the length of the list
    printf("Length of the list: %d\n", printlen(head));

    return 0;
}
