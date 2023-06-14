#include "item.h"
#include <stdlib.h>
#include <string.h>


Item* create_item(char* a){
    Item* item = (Item*) calloc(1, sizeof (Item));
    item -> info = strdup(a);
    return item;
}


void delete_item(Item* item){
    free(item->info);
    free(item);
}
