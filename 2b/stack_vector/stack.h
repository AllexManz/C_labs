#ifndef VECTOR_H
#define VECTOR_H
#define MAX_SIZE 100

typedef struct stack {
    int* arr;
    int size;
    int max_size;
} Stack;

Stack* createStack();

int push(Stack* stack, int data);

int pop(Stack* stack);

int stackSize(Stack* stack);

void deleteStack(Stack* stack);


#endif
