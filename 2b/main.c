#include <stdio.h>
#include "process.h"

#if defined VECTOR
#include "stack_vector/stack.h"
#elif defined LIST
#include "stack_list/stack.h"
#endif

int main() {
    int result;
    void *stack = createStack();

    if (!evaluate(stack, &result)){
        printf("Result: %d\n", result);
    }

    deleteStack(stack);
    return 0;
}


