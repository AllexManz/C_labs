#ifndef LIST_H
#define LIST_H

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct stack {
    Node* top;
    int size;
} Stack;

Stack* createStack();

void push(Stack* stack, int data);

int pop(Stack* stack);

int stackSize(Stack* stack);

void deleteStack(Stack* stack);


#endif
