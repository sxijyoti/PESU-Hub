#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Stack {
    char arr[MAX];
    int top;
};

// Initialize the stack
void initializeStack(struct Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

// Push an element onto the stack
void push(struct Stack* s, char c) {
    if (isFull(s)) {
        printf("Stack overflow.\n");
        return;
    }
    s->arr[++(s->top)] = c;
}

// Pop an element from the stack
char pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow.\n");
        return '\0';
    }
    return s->arr[(s->top)--];
}

// Peek the top element of the stack
char peek(struct Stack* s) {
    if (isEmpty(s)) {
        return '\0';
    }
    return s->arr[s->top];
}

// Check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;  // Higher precedence for exponentiation
    return 0;
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    struct Stack s;
    initializeStack(&s);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) {
            postfix[j++] = token;  // Add operand to output
        } else if (token == '(') {
            push(&s, token);
        } else if (token == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);  // Pop to output until '('
            }
            pop(&s);  // Discard '('
        } else {  // Operator
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token)) {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    // Pop remaining operators
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';  // Null-terminate the string
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
