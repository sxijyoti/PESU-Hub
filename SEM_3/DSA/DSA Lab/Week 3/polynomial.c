// Write a C program that takes 2 polynomials, adds them and evaluate it with an input value(x). 
// If the resultant linked list is empty print -1.
// You are required to fill in the code for the following functions:
// The 'input' function that inputs the terms of the polynomials.
// The 'sum' function that finds the sum of the polynomials and returns the resulting polynomial.
// The 'eval' function that evaluates the polynomial with the value x.
// The 'destroy function' that frees all the nodes in the linked list.
// Note: Each node of a linked list for a polynomial stores each term of the polynomial(coefficient, degree). 
// The terms in each polynomial are stored in decreasing order of their powers.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct node{
    int coeff;
    int pow;
    struct node* next;
}node;

void input(node** head,node** tail,int n);
node* sum(node* head1,node* head2);
int eval(node* head,int x);
void destroy(node **head);

int main(){
    int m=0;
    int n=0;
    node* head1=NULL;
    node* head2=NULL;
    node* tail1=NULL;
    node* tail2=NULL;
    
    int x=0;//value of the variable for evaluation

    scanf("%d %d",&m,&n);
    scanf("%d",&x);
    input(&head1,&tail1,m);
    input(&head2,&tail2,n);
    
    node *headres=sum(head1,head2);
    int res=eval(headres,x);
    printf("%d",res);
    destroy(&headres);
    return 0;
}

void input(node** head,node** tail,int n){
    //Your Code
    for (int i = 0; i < n; i++) {
        int coeff, pow;
        scanf("%d %d", &coeff, &pow);
        
        node* new = (node*)malloc(sizeof(struct node));
        new ->coeff = coeff;
        new ->pow = pow;
        new ->next = NULL;
        
        if (*head == NULL) {
            *head = *tail = new;
        } else {
            (*tail)->next = new;
            *tail = new;
        }
    }
}
node* sum(node* head1,node* head2){
    //Your Code
     node* headres = NULL;
    node* tailres = NULL;
    
    while (head1 != NULL && head2 != NULL) {
        node* new = (node*)malloc(sizeof(struct node));
        new->next = NULL;
        
        if (head1->pow > head2->pow) {
            new->coeff = head1->coeff;
            new->pow = head1->pow;
            head1 = head1->next;
        } else if (head1->pow < head2->pow) {
            new->coeff = head2->coeff;
            new->pow = head2->pow;
            head2 = head2->next;
        } else {
            new->coeff = head1->coeff + head2->coeff;
            new->pow = head1->pow;
            head1 = head1->next;
            head2 = head2->next;
        }
        
        if (headres == NULL) {
            headres = tailres = new;
        } else {
            tailres->next = new;
            tailres = new;
        }
    }
    
    while (head1 != NULL) {
        node* new = (node*)malloc(sizeof(struct node));
        new ->coeff = head1->coeff;
        new ->pow = head1->pow;
        new ->next = NULL;
        head1 = head1->next;
        
        if (headres == NULL) {
            headres = tailres = new ;
        } else {
            tailres->next = new ;
            tailres = new ;
        }
    }
    
    while (head2 != NULL) {
        node* new = (node*)malloc(sizeof(struct node));
        new ->coeff = head2->coeff;
        new->pow = head2->pow;
        new ->next = NULL;
        head2 = head2->next;
        
        if (headres == NULL) {
            headres = tailres = new;
        } else {
            tailres->next = new;
            tailres = new;
        }
    }
    
    return headres;

}

int eval(node* head,int x){
    //Your Code
     if (head == NULL) {
        return -1;
    }
    
    int res = 0;
    while (head != NULL) {
        res = res + head->coeff * pow(x, head->pow);
        head = head->next;
    }
    return res;
}

void destroy(node **head){
    //Your Code
    node* cur = *head;
    node* next;
    
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}