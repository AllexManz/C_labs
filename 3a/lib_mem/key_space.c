#include "key_space.h"
#include <stdlib.h>


KeySpace* create_ks(int parent, int key, Item* item){
    KeySpace* ks = (KeySpace*)calloc(1, sizeof(KeySpace));
    ks->par = parent;
    ks->key = key;
    ks->info = item;
    ks->next = NULL;
    return ks;
}


void delete_ks(KeySpace* ks){
    free(ks->info);

    if(ks->next != NULL)
	delete_ks(ks->next);

    free(ks);
}
