#include "key_space.h"


KeySpace* create_ks(unsigned int key, Node* node){
    KeySpace* ks = (KeySpace*) calloc(1, sizeof(KeySpace));
    //ks->key = key;
    ks->node = node;
    node->release = key;
    ks->next = NULL;
    return ks;
}


void delete_ks(KeySpace* ks){
    Node* node = ks->node, *temp;
    while (node != NULL){
        temp = node;
        node = node -> next;
        delete_node(temp);
    }

    ks->next = NULL;
    free(ks);
}
