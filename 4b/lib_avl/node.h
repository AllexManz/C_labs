#ifndef NODE_H
#define NODE_H
#include "item.h"

typedef struct Node{
    struct Node *p; // Parent
    struct Node *lc; // Left child
    struct Node *rc; // Right child
    Item *inf; // Key and Value
    int height; // Height of the node
}Node;


Node* create_node(Item* item);

int height(Node* node);

int getBalance(Node *node);

void delete_node(Node* node);

void special_delete_node(Node* node);

void delete_node_chain(Node* node);

#endif
