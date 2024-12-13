#include <stdio.h>

// array
#define MAX 100

typedef struct stack {
    int arr[MAX];
    int top;
} Stack;

void initStack(Stack* stack){
    stack->top = -1;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int isFull(Stack* stack){
    return stack->top == MAX-1;
}

void push(Stack* stack, int val){
    if(isFull(stack)){
        printf("ERROR");
        return;
    }
    stack->arr[++(stack->top)] = val;

}

int pop(Stack* stack){
    if(isEmpty(stack)){
        printf("ERROR");
        return -1;
    }
    return stack->arr[(stack->top)--];
    
}

void display(Stack* stack){
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    for(int i = stack->top; i>=0; i--){
        printf("%d",stack->arr[i]);
    }
}

// linkedlist

struct Node{
    int data;
    struct Node* next;
};

typedef struct Node* node;

node push(node top, int val){
    node new = (node)malloc(sizeof(struct Node));
    if(!new){
        printf("error");
        return top;
    }
    new->data = val;
    new->next = top;
    return new;
}

node pop(node top){
    if(!top){
        printf("error");
        return NULL;
    }
    node temp = top;
    top = top->next;
    free(temp);
    return top;
}