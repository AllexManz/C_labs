#ifndef UNTITLED_TABLE_H
#define UNTITLED_TABLE_H
#include <stdio.h>

typedef struct Table{
    FILE* file;
    int size;
}Table;

Table* create_table(const char* name);

void delete_table(Table* table);

void print(Table* table);

void add(Table* table, unsigned int key, unsigned int par, unsigned int info);

void find(Table* table, unsigned int key);

void delete(Table* table, unsigned int key);

void par_find(Table* table, unsigned int par);

static void download(Table* table, unsigned int* key, unsigned int* par, unsigned int* info);

static unsigned int len_counter(unsigned int n);

#endif
