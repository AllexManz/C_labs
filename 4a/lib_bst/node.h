#ifndef NODE_H
#define NODE_H
#include "item.h"

typedef struct Node{
    struct Node *lc; // Left child
    struct Node *rc; // Right child
    Item *inf; // Key and Value
}Node;


Node* create_node(Item* item);

void delete_node(Node* node);

void delete_node_chain(Node* node);

#endif
