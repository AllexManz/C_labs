#ifndef AVL_H
#define AVL_H
#include "node.h"


typedef struct AVL{
    Node* root;
}AVL;

AVL* create_avl();

void delete_avl(AVL* avl);

Node *rightRotate(Node *y);

Node *leftRotate(Node *x);

void add_node(AVL* avl, Node* node);

Node *_add_node(Node* avl_node, Node* node);

void delete(AVL* avl, unsigned int key);

Node* _delete(Node *root, unsigned int key);

void tree_traversal(AVL* avl, unsigned int key);

static void _tree_traversal_(Node* bt_node, unsigned int key);

void timing_tree_traversal(AVL* avl, unsigned int key);

static void _timing_tree_traversal_(Node* bt_node, unsigned int key);

void print(AVL* avl, int option);

void print_preOrder(Node* node);

void print_inOrder(Node* node);

void print_postOrder(Node* node);

void beauty_print(AVL* avl);

static void _beauty_print_(Node* node, int height, unsigned int size);

int find(AVL* avl, unsigned int key, unsigned int* res);

static int _find_(Node* bt_node, unsigned int key, unsigned int* res);

Node* min(AVL* avl);

static Node* _min_(Node* bt_node);

int simple_max(int a, int b);

static int len_counter(unsigned int n);

#endif
