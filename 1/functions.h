#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    int* array;
} Line;


typedef struct {
    int m;
    Line* lines;
} Matrix;


int get_int(int* n);


int get_matrix(Matrix* matrix);


void output(Matrix* matrix);


void free_all(Matrix* matrix);



void create_matrix(Matrix* matrix, Matrix* new_matrix);


int check(int value);


int reverse(int n);


#endif
