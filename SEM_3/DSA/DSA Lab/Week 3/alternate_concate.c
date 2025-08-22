// Complete the function 'concat'. It takes the head pointers of two lists as parameters. 
// Concatenate the nodes in both the lists in an alternate manner to form a new list. Return the new list.
// The first element is from the list with head1.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

typedef struct node* NODE;

NODE concat(NODE head1, NODE head2) {
    if (head1==NULL && head2==NULL){ 
        return NULL;
    }

    NODE nlist = NULL; 
    
    while (head1 || head2) {
        if (head1) {
            get_node(&nlist, head1->data);
            head1 = head1->next;
        }
        if (head2) {
            get_node(&nlist, head2->data);
            head2 = head2->next;
        }
    }
    
    return nlist;
}


void get_node(NODE* head, int ele) {
    NODE new = (NODE)malloc(sizeof(struct node));
    new->data = ele;
    new->next = NULL;

    if (*head == NULL) {
        *head = new;
        return;
    }
    NODE cur= *head;
    while(cur->next!=NULL){
        cur = cur->next;
    }
    cur->next=new;
}

void display(NODE head) {
    if (!head) {
        printf("NULL");
        return;
    }

    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int a, b;
    NODE head1 = NULL;
    NODE head2 = NULL;

    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        int ele;
        scanf("%d", &ele);
        get_node(&head1, ele);
    }

    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        int ele;
        scanf("%d", &ele);
        get_node(&head2, ele);
    }

    NODE new_list = concat(head1, head2);

    display(new_list);
    return 0;
}
