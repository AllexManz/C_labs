#include "item.h"
#include <stdlib.h>

Item* create_item(int data){
    Item* item = (Item*) calloc(1, sizeof(Item));
    item -> info = data;
    return item;
}
