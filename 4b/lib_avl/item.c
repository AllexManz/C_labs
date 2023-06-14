#include "item.h"
#include <stdlib.h>

Item* create_item(unsigned int key, unsigned int val){
    Item* item = calloc(1, sizeof (Item));
    item -> key = key;
    add_release(item, val);
    return item;
}

void add_release(Item* item, unsigned int val){
    item -> n += 1;
    item -> val = realloc(item -> val, item -> n * sizeof (int));
    item -> val[item -> n - 1] = val;
}

void delete_release(Item* item){
    if (item -> n == 1){
        delete_item(item);
        return;
    }

    item -> n -= 1;
    item -> val = realloc(item -> val, item -> n * sizeof (int));
}

void delete_item(Item* item){
    free(item->val);
    free(item);
}
