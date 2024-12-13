#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void front_insert(struct node **p, int x) {
    struct node *new = (struct node *)malloc(sizeof(struct node));
    new->data = x;
    new->next = NULL;

    if (*p == NULL) {
        // Case: Empty circular linked list
        new->next = new; // New node points to itself
        *p = new;        // Update head to new node
    } else {
        // Case: Non-empty circular linked list
        struct node *last = *p;

        // Find the last node in the circular list
        while (last->next != *p) {
            last = last->next;
        }

        // Update the new node's next pointer and the last node's next pointer
        new->next = *p;  // New node points to the current head
        last->next = new; // Last node points to the new node
        *p = new;        // Update head to the new node
    }
}
