#ifndef ITEM_H
#define ITEM_H

typedef struct Item{
    char* key;
    unsigned int val;
}Item;


Item* create_item(char* key, unsigned int val);

void delete_item(Item* item);

#endif
