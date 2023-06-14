#ifndef KEY_SPACE_H
#define KEY_SPACE_H
#include "item.h"

typedef struct KeySpace{
    int key; // node key
    int par; // parent key
    Item *info;
    struct KeySpace *next;
} KeySpace;


KeySpace* create_ks(int parent, int key, Item* item);

void delete_ks(KeySpace* ks);

#endif //KEY_SPACE_H
