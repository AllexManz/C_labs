#ifndef FILE_ACCES_H
#define FILE_ACCES_H
#include <stdio.h>
#include "avl_tree.h"


int open(AVL* avl);

int n_open(AVL* avl, int n);

static unsigned int string_to_int(char *str);

static  char* myl(FILE* file);

#endif
