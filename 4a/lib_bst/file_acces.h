#ifndef FILE_ACCES_H
#define FILE_ACCES_H
#include <stdio.h>
#include "bin_tree.h"


int open(BT* bt);

static unsigned int string_to_int(char *str);

static  char* myl(FILE* file);

char *rl(const char* input);

#endif
