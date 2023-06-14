#ifndef ITEM_H
#define ITEM_H

typedef struct Item{
    char* info;
}Item;


Item* create_item(char* a);

void delete_item(Item* item);

#endif
