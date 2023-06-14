#include "node.h"
#include <stdlib.h>

Node* create_node(Item* item){
    Node* node = (Node*) calloc(1, sizeof (Node));
    node -> info = item;
    node -> next = NULL;
    return node;
}

void delete_node(Node* node){
    delete_item(node->info);
    node->next = NULL;
    free(node);
}
