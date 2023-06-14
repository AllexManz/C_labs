#include "item.h"
#include <stdlib.h>
#include <string.h>

Item* create_item(char* key, unsigned int val){
    Item* item = calloc(1, sizeof (Item));
    item -> key = strdup(key);
    item -> val = val;
    return item;
}

void delete_item(Item* item){
    free(item->key);
    free(item);
}
