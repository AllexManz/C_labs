#ifndef KEY_SPACE_H
#define KEY_SPACE_H
#include <stdlib.h>
#include "node.h"


typedef struct KeySpace{
    unsigned int key;
    Node *node;
    struct KeySpace* next;
}KeySpace;

KeySpace* create_ks(unsigned int key, Node* node);

void delete_ks(KeySpace* ks);

#endif
