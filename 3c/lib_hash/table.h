#ifndef TABLE_H
#define TABLE_H
#include "key_space.h"
#define MAX_SIZE 5

typedef struct Table{
    KeySpace** ks;
    int max_size;
    int c_size;
} Table;


Table* create_table();

void delete_table(Table* table);

void add_ks(Table* table, KeySpace* ks);

void print(Table* table);

void special_delete(Table* table, unsigned int key);

Table* find(Table* table, unsigned int key);

void my_delete(Table* table, unsigned int key, unsigned int version);

Table* my_find(Table* table, unsigned int key, unsigned int version);

static int len_counter(int n);

static unsigned int hash(unsigned int n);

#endif
