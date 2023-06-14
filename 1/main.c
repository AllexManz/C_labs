#include "functions.h"




int main(){
    Matrix matrix = {0, NULL};
    Matrix new_matrix = {0, NULL};


    if (get_matrix(&matrix) == 0){
	free_all(&matrix);
        return 1;
    }
    printf("Start ");
    output(&matrix);


    create_matrix(&matrix, &new_matrix);
    printf("New ");
    output(&new_matrix);


    free_all(&matrix);
    free_all(&new_matrix);


    return 0;
}
