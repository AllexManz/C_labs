#ifndef TABLE_H
#define TABLE_H
#include "key_space.h"

typedef struct Table{
    KeySpace *ks;
} Table;

Table* create_table();

void delete_table(Table* table);

int add_ks(Table* table, KeySpace* ks);

void print(Table* table);

static int len_counter(int n);

Table* find(Table* table, int key);

Table* par_find(Table* table, int key);

void delete(Table* table, int key);

void rec_delete(Table* table, int key);

#endif //TABLE_H
