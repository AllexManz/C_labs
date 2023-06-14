#include "node.h"
#include <stdlib.h>

Node* create_node(Item* item){
    Node* node = calloc(1, sizeof (Node));
    node -> height = 1;
    node -> inf =  item;
    return node;
}

// Calculate height
int height(Node* node) {
    if (node == NULL)
        return 0;
    return node -> height;
}

// Get the balance factor
int getBalance(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->lc) - height(node->rc);
}


void special_delete_node(Node* node){
    node -> lc = NULL;
    node -> rc = NULL;
    node -> p = NULL;
    node -> inf = NULL;
    free(node);
}



void delete_node(Node* node){
    node -> lc = NULL;
    node -> rc = NULL;
    node -> p = NULL;
    delete_item(node -> inf);
    free(node);
}


void delete_node_chain(Node* node){
    if (node == NULL){
        return;
    }
    if (node -> lc != NULL){
        delete_node_chain(node -> lc);
    }
    if (node -> rc != NULL){
        delete_node_chain(node -> rc);
    }
    delete_item(node -> inf);
    free(node);
}
