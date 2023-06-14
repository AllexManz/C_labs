#include <stdlib.h>
#include "stack.h"


Stack* createStack() {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack* stack, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        return -1;
    }
    Node* node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}


int stackSize(Stack* stack) {
    return stack->size;
}

void deleteStack(Stack* stack) {
    Node* node = stack->top;
    while (node != NULL) {
        Node* temp = node;
        node = node->next;
        free(temp);
    }
    free(stack);
}
