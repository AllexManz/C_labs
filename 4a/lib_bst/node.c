#include "node.h"
#include <stdlib.h>

Node* create_node(Item* item){
    Node* node = calloc(1, sizeof (Node));
    node -> inf =  item;
    return node;
}


void delete_node(Node* node){
    node -> lc = NULL;
    node -> rc = NULL;
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


