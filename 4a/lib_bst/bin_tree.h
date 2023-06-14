#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "node.h"

typedef struct BT{
    Node* root;
}BT;

BT* create_bt();

void delete_bt(BT* bt);

void print(BT* bt);

void print_inOrder(Node* node);

int add_node(BT* bt, Node* node, unsigned int* res);

static int _add_node(Node* bt_node, Node* node, unsigned int* res);

int find(BT* bt, char* key, unsigned int* res);

Node* max(BT* bt);

static Node* _max_(Node* bt_node);

static int _find_(Node* bt_node, char* key, unsigned int* res);

void tree_traversal(BT* bt, char* key);

void _tree_traversal_(Node* bt_node, const char* key);

void delete(BT* bt, const char* key);

static void _delete_(Node* bt_node, Node* prev, const char* key);

Node* min(BT* bt);

static Node* _min_(Node* bt_node);

void beauty_print(BT* bt);

static void _beauty_print_(Node* node, int height, unsigned int size);

static int len_counter(unsigned int n);

#endif
