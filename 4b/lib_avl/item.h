#ifndef ITEM_H
#define ITEM_H

typedef struct Item{
    int n;
    unsigned int key;
    unsigned int* val;
}Item;


Item* create_item(unsigned int key, unsigned int val);

void add_release(Item* item, unsigned int val);

void delete_item(Item* item);

void delete_release(Item* item);

#endif
