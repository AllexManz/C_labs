#include "process.h"
#include <stdio.h>

#if defined VECTOR
#include "stack_vector/stack.h"
#elif defined LIST
#include "stack_list/stack.h"
#endif

int evaluate(void* stack, int* result){
    char c, flag = 1;

    printf("Enter equation: ");
    while ((c = getchar()) != EOF && c != '\n' && flag) {
        if (isDigit(c)) {
            int n = c - '0';
            while ((c = getchar()) != EOF && isDigit(c)) {
                n = n * 10 + (c - '0');
            }
	    if (!push(stack, n)){
		printf("STACK OVERFLOW\n");
		flag = 0;
		break;
	    }
        }
        if (c == '+' || c == '-' || c == '*') {
            if (stackSize(stack) < 2){
                printf("Equation entered with errors\n");
                flag = 0;
		break;
            }

            int a = pop(stack);
            int b = pop(stack);
            switch (c) {
                case '+':
                    if (!push(stack, b + a)){
                	printf("STACK OVERFLOW\n");
			flag = 0;
		    }
                    break;
                case '-':
		    if (!push(stack, b - a)){
                        printf("STACK OVERFLOW\n");
                        flag = 0;
                    }
                    break;
                case '*':
		    if (!push(stack, b * a)){
                        printf("STACK OVERFLOW\n");
                        flag = 0;
                    }
                    break;
            }
        }
        if (c == '/'){
            if (stackSize(stack) < 2){
                printf("Equation entered with errors\n");
                flag = 0;
            }

            int a = pop(stack);
            int b = pop(stack);
            if (a == 0){
                printf("Equation entered with errors\n");
                flag = 0;
            }
            else{
		if (!push(stack, b / a)){
                    printf("STACK OVERFLOW\n");
                    flag = 0;
		    break;
                }
            }
        }
    }

    if (flag){
        (*result) = pop(stack);
        return 0;
    }
    else{
        return 1;
    }
}


int isDigit(char c){
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}
