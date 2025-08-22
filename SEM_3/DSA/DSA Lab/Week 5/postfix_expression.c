/* Write a C code to evaluate a postfix expression using stacks. You are expected to fill in the code for the following functions.

'pop' for popping the elements from the stack.
'push' for pushing elements into the stack.
'eval' for evaluating the given postfix expression.
'disp' for printing the result after evaluating the postfix expression.

Sample Input:
231*+9-

Sample Output:
-4

Explanation:
3*1 is evaluated and gives 3.
2+3 is evaluated and gives 5.
5-9 is evaluated and gives -4. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 30

void push(char s, int* top, int stack[MAX]);
int pop(int stack[MAX], int* top);
void eval(int stack[MAX], int* top, char postfix[MAX]);
void disp(int stack[MAX],int* top);

int main()
{
    int stack[MAX];
    int top = -1;
    char postfix[30];
    scanf("%s", postfix);
    eval(stack, &top, postfix);
    disp(stack,&top);
    return 0;
}

void push(char s, int* top, int stack[MAX])
{
/*Your Code*/
    if (*top >= MAX - 1) {
        printf("Stack is full\n");
        exit(0);
    } else {
        (*top)++;
        stack[*top] = s;
    }

}

int pop(int stack[MAX], int* top)
{
/*Your Code*/
    if (*top == -1) {
        printf("Stack is empty\n");
        exit(0);
        return -1;
    } else {
        int val = stack[*top];
        (*top)--;
        return val;
    }
}

void eval(int stack[MAX], int* top, char postfix[MAX])
{
/*Your Code*/
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            // If it's a digit, push it to the stack after converting from char to int
            push(postfix[i] - '0', top, stack);
        } else {
            // It's an operator, pop two values from the stack
            int op2 = pop(stack, top);
            int op1 = pop(stack, top);
            int r;

            switch (postfix[i]) {
                case '+':
                    r = op1 + op2;
                    break;
                case '-':
                    r = op1 - op2;
                    break;
                case '*':
                    r = op1 * op2;
                    break;
                case '/':
                    r = op1 / op2;
                    break;
                default:
                    return;
            }
            // Push the result back onto the stack
            push(r, top, stack);
        }
    }
}

void disp(int stack[MAX],int* top)
{
/*Your Code*/
     if (*top != -1) {
        printf("%d\n", stack[*top]);
    } else {
        printf("Stack is empty\n");
    }
}