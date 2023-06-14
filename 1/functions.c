#include "functions.h"

int get_int(int* n){
    printf("Enter the value: ");
    int checker = scanf("%d", n);
    while(checker != 1){
        if (checker == -1){
            printf("EOF Found\n");
            return 0;
        }
        printf("\n!    Wrong input. Value should be digital number.\n\n");
        scanf("%*[^\n]");
        printf("Enter the value: ");
        checker = scanf("%d", n);
    }

    return 1;
}


void output(Matrix* matrix){
    printf("Matrix:\n\n");
    int m = matrix->m;
    for (int i = 0; i < m; i++){
        int n = matrix->lines[i].n;
        for (int j = 0; j < n; j++){
            printf("%d ", matrix->lines[i].array[j]);
        }
        printf("\n");
    }
    printf("\n\n");
}


int get_matrix(Matrix* matrix){
    int m, n, flag;
    printf("Enter the number of lines.\n");
    flag = get_int(&m);
    if (flag == 0){
        return 0;
    }
    while(m <= 0){
        printf("\n!    Wrong input. Value should be greater than zero.\n\n");
        printf("Enter the number of lines.\n");
        get_int(&m);
    }

    matrix->m = m;
    matrix->lines = calloc(m, sizeof(Line));


    for (int i = 0; i < m; i++){
        printf("Enter the size of line[%d].\n", i);
        flag = get_int(&n);
        if (flag == 0){
            return 0;
        }
        while(n < 0){
            printf("\n!    Wrong input. Value should be greater than zero.\n\n");
            printf("Enter the size of line[%d].\n", i);
            get_int(&n);
        }

        matrix->lines[i].n = n;
        matrix->lines[i].array = calloc(n, sizeof(int));
        for (int j = 0; j < n; j++){
            int temp;
            printf("Enter the value of matrix[%d][%d].\n", i, j);
            flag = get_int(&temp);
            if (flag == 0){
                return 0;
            }
            matrix->lines[i].array[j] = temp;
        }
    }

    return 1;
}


void free_all(Matrix* matrix){
    for (int i = 0; i < matrix->m; i++){
        free(matrix->lines[i].array);
    }
    free(matrix->lines);
    //free(matrix);
}



void create_matrix(Matrix* matrix, Matrix* new_matrix){
    new_matrix->m = matrix->m;
    new_matrix->lines = malloc(sizeof (Line) * matrix->m);

    for (int i = 0; i < matrix->m; i++){
        new_matrix->lines[i].n = 0;
        new_matrix->lines[i].array = malloc(sizeof (int) * new_matrix->lines[i].n);
        for (int j = 0; j < matrix->lines[i].n; j++){
            if (check(matrix->lines[i].array[j]) == 1){
                new_matrix->lines[i].n += 1;
                new_matrix->lines[i].array = realloc(new_matrix->lines[i].array, sizeof (int) * new_matrix->lines[i].n);
                new_matrix->lines[i].array[new_matrix->lines[i].n - 1] = matrix->lines[i].array[j];
            }
        }
    }
}


int reverse(int n){
    int ans = 0;
    while (n != 0){
        ans *= 10;
        ans += n % 10;
        n /= 10;
    }

    return ans;
}


int check(int value){
    int reversed_value = reverse(value);
    while (value != 0){
        if ((value % 10) != (reversed_value % 10)){
            return 0;
        }
        value /= 10;
        reversed_value /= 10;
    }

    return 1;
}
