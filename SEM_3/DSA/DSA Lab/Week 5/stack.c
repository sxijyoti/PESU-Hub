/* You are given a row of plants, where each plant has a certain level of pesticide. 
Every day, any plant that has more pesticide than the plant directly to its left dies. 
This process continues until no plant dies. 
Your task is to determine the number of days after which no plant dies.
Sample input:
7
6 5 8 4 7 10 9
Output:
2
Explanation:
Day 1: Plants 8, 7, and 10 die. Remaining: [6, 5, 4, 9]
Day 2: Plant 9 dies. Remaining: [6, 5, 4]
Plants stop dying after 2 days. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Define a Plant struct with pesticide level and days survived
typedef struct {
   int pesticide;
   int days;
} Plant;


// Stack structure
typedef struct {
   Plant* data;
   int top;
} Stack;


// Function to create a stack
Stack* createStack(int size) {
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    new_stack->data = (Plant*)malloc(size * sizeof(Plant));
    new_stack->top = -1;
    return new_stack;
}


// Function to push an element to the stack
void push(Stack* stack, Plant plant) {
    stack->data[++stack->top] = plant;
   }


// Function to pop an element from the stack
Plant pop(Stack* stack) {
    return stack->data[stack->top--];
   }


// Function to peek at the top element of the stack
Plant peek(Stack* stack) {
   return stack->data[stack->top];
}


// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
  return stack->top == -1;
}


// Free stack memory
void freeStack(Stack* stack) {
     free(stack->data);
     free(stack);
}


// The poisonousPlants function
int poisonousPlants(int p_count, int* p) {
    Stack* ppstack = createStack(p_count);
    int max = 0;

    for (int i = 0; i < p_count; i++) {
        int days = 0;
        
        while (!isEmpty(ppstack) && peek(ppstack).pesticide >= p[i]) {
            days = (days > peek(ppstack).days) ? days : peek(ppstack).days;
            pop(ppstack);
        }

        if (!isEmpty(ppstack)) {
            days++;
        }

        Plant plant = { p[i], days };
        push(ppstack, plant);

        if (days > max) {
            max = days;
        }
    }

    freeStack(ppstack);
    
    return max;
   }


int main() {
   int n;
   // printf("Enter number of plants: ");
   scanf("%d", &n);

   int* p = (int*)malloc(n * sizeof(int));
   // printf("Enter pesticide levels: ");
   for (int i = 0; i < n; i++) {
       scanf("%d", &p[i]);
   }

   int result = poisonousPlants(n, p);
   printf("%d\n", result);

   free(p);
   return 0;
}