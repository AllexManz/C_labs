#include "stack.h"
#include <stdlib.h>


Stack* createStack(){
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    stack -> size = 0;
    stack -> max_size = 100;
    stack -> arr = NULL;
    return stack;
}


int push(Stack* stack, int data){
    if (stack -> size == stack -> max_size){
	stack -> max_size += 100;
	stack -> arr = realloc(stack -> arr, (stack -> size + 100) * sizeof(int));
    }
    stack -> arr[stack -> size] = data;
    stack -> size += 1;
    return 1;
}


int pop(Stack* stack){
    if (stack->size == 0){
	return -1;
    }
    stack->size-=1;
    int value = stack -> arr[stack -> size ];
    stack -> arr = realloc(stack -> arr, (stack -> size) * sizeof(int));
    return value;
}


int stackSize(Stack* stack){
    return stack->size;
}


void deleteStack(Stack* stack) {
    free(stack->arr);
    free(stack);
}

