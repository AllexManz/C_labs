#ifndef NODE_H
#define NODE_H
#include "item.h"

typedef struct Node{
    unsigned int release;
    Item* info;
    struct Node* next;
}Node;

Node* create_node(Item* item);

void delete_node(Node* node);

#endif
