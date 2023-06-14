#include "avl_tree.h"
#include <stdlib.h>
#include <stdio.h>


AVL* create_avl(){
    AVL* avl = calloc(1, sizeof (AVL));
    avl -> root = NULL;
    return avl;
}

void delete_avl(AVL* avl) {
    delete_node_chain(avl->root);
    free(avl);
}

// Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->lc;
    Node* T2 = x->rc;

    x->rc = y;
    y->lc = T2;

    y->height = simple_max(height(y->lc), height(y->rc)) + 1;
    x->height = simple_max(height(x->lc), height(x->rc)) + 1;

    return x;
}

// Left rotate
Node* leftRotate(Node* x) {
    Node* y = x->rc;
    Node* T2 = y->lc;

    y->lc = x;
    x->rc = T2;

    x->height = simple_max(height(x->lc), height(x->rc)) + 1;
    y->height = simple_max(height(y->lc), height(y->rc)) + 1;

    return y;
}



void add_node(AVL* avl, Node* node){
    if (avl->root == NULL){
        avl->root = node;
        return;
    }

    avl->root = _add_node(avl->root, node);
}


Node *_add_node(Node* avl_node, Node* node) {
    // Find the correct position to insertNode the node and insertNode it
    if (avl_node == NULL)
        return node;

    if (node->inf->key < avl_node->inf->key)
        avl_node->lc = _add_node(avl_node->lc, node);
    else if (node->inf->key > avl_node->inf->key)
        avl_node->rc = _add_node(avl_node->rc, node);
    else if (node->inf->key == avl_node->inf->key){
        add_release(avl_node->inf, (node->inf->val[0]));
        delete_node(node);
        return avl_node;
    }

    // Update the balance factor of each node and
    // Balance the tree
    avl_node->height = 1 + simple_max(height(avl_node->lc), height(avl_node->rc));

    int balance = getBalance(avl_node);
    if (balance > 1 && node->inf->key < avl_node->lc->inf->key)
        return rightRotate(avl_node);

    if (balance < -1 && node->inf->key > avl_node->rc->inf->key)
        return leftRotate(avl_node);

    if (balance > 1 && node->inf->key > avl_node->lc->inf->key) {
        avl_node->lc = leftRotate(avl_node->lc);
        return rightRotate(avl_node);
    }

    if (balance < -1 && node->inf->key < avl_node->rc->inf->key) {
        avl_node->rc = rightRotate(avl_node->rc);
        return leftRotate(avl_node);
    }

    return avl_node;
}



void delete(AVL* avl, unsigned int key){
    if (avl->root == NULL){
        return;
    }

    avl->root = _delete(avl->root, key);
}

// Delete a nodes
Node* _delete(Node *root, unsigned int key) {
    // Find the node and delete it
    if (root == NULL)
        return root;

    if (key < root->inf->key)
        root->lc = _delete(root->lc, key);
    if (key > root->inf->key)
        root->rc = _delete(root->rc, key);
    if (key == root->inf->key) {
        if (root->inf->n > 1){
            delete_release(root->inf);
            return root;
        }
        if ((root->lc == NULL) || (root->rc == NULL)) {
            Node *temp = root->lc ? root->lc : root->rc;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            delete_node(temp);
        } else {
            Node *temp = _min_(root->rc);

            root->inf->key = temp->inf->key;

            root->rc = _delete(root->rc, temp->inf->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + simple_max(height(root->lc), height(root->rc));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->lc) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->lc) < 0) {
        root->lc = leftRotate(root->lc);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->rc) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->rc) > 0) {
        root->rc = rightRotate(root->rc);
        return leftRotate(root);
    }

    return root;
}


void tree_traversal(AVL* avl, unsigned int key){
    if (key == 0){
        print(avl, 3);
        return;
    }
    if (avl->root == NULL){
        printf("Tree is Empty\n");
        return;
    }

    int n = 0;
    // printf("\n|    val    |    key    |\n");
    // printf("-------------------------\n");
    _tree_traversal_(avl->root, key);
}



static void _tree_traversal_(Node* node, unsigned int key){
    if (node->lc != NULL){
        _tree_traversal_(node->lc, key);
    }


    if (node->inf->key > key) {
        printf("|%d", node->inf->key);
        for (int k = 0; k < 11 - len_counter(node->inf->key); k++){
            printf(" ");
        }

        for (int i = 0; i < node -> inf -> n; i++){
            printf("|%d ", node->inf->val[i]);
            for (int k = 0; k < 11 - len_counter(node->inf->val[i]); k++){
                printf(" ");
            }
        }
        printf("|\n");
    }


    if (node->rc != NULL){
        _tree_traversal_(node->rc, key);
    }
}


void timing_tree_traversal(AVL* avl, unsigned int key){
    if (key == 0)
        return;
    if (avl->root == NULL)
        return;

    _timing_tree_traversal_(avl->root, key);
}



static void _timing_tree_traversal_(Node* node, unsigned int key){
    if (node->lc != NULL){
        _tree_traversal_(node->lc, key);
    }


    /*
    if (node->inf->key > key) {
        printf("|%d", node->inf->key);
        for (int k = 0; k < 11 - len_counter(node->inf->key); k++){
            printf(" ");
        }

        for (int i = 0; i < node -> inf -> n; i++){
            printf("|%d ", node->inf->val[i]);
            for (int k = 0; k < 11 - len_counter(node->inf->val[i]); k++){
                printf(" ");
            }
        }
        printf("|\n");
    }
    */


    if (node->rc != NULL){
        _tree_traversal_(node->rc, key);
    }
}



void print(AVL* avl, int option){
    if (avl -> root == NULL){
        printf("Tree is empty\n");
        return;
    }

    printf("\n|    val    |    key    |\n");
    printf("-------------------------\n");
    if (option == 1){
        print_preOrder(avl->root);
    }
    if (option == 2){
        print_inOrder(avl->root);
    }
    if (option == 3){
        print_postOrder(avl->root);
    }
}

void print_preOrder(Node* node){
    if (node->lc != NULL){
        print_inOrder(node->lc);
    }

    printf("|%d", node->inf->key);
    for (int k = 0; k < 11 - len_counter(node->inf->key); k++){
        printf(" ");
    }

    for (int i = 0; i < node -> inf -> n; i++){
        printf("|%d ", node->inf->val[i]);
        for (int k = 0; k < 11 - len_counter(node->inf->val[i]); k++){
            printf(" ");
        }
    }
    printf("|\n");

    if (node->rc != NULL){
        print_inOrder(node->rc);
    }
}

void print_inOrder(Node* node){
    if (node->lc != NULL){
        print_inOrder(node->lc);
    }

    printf("|%d", node->inf->key);
    for (int k = 0; k < 11 - len_counter(node->inf->key); k++){
        printf(" ");
    }

    for (int i = 0; i < node -> inf -> n; i++){
        printf("|%d ", node->inf->val[i]);
        for (int k = 0; k < 11 - len_counter(node->inf->val[i]); k++){
            printf(" ");
        }
    }
    printf("|\n");

    if (node->rc != NULL){
        print_inOrder(node->rc);
    }
}

void print_postOrder(Node* node){
    if (node->rc != NULL){
        print_inOrder(node->rc);
    }

    printf("|%d", node->inf->key);
    for (int k = 0; k < 11 - len_counter(node->inf->key); k++){
        printf(" ");
    }

    for (int i = 0; i < node -> inf -> n; i++){
        printf("|%d ", node->inf->val[i]);
        for (int k = 0; k < 11 - len_counter(node->inf->val[i]); k++){
            printf(" ");
        }
    }
    printf("|\n");

    if (node->lc != NULL){
        print_inOrder(node->lc);
    }
}



int find(AVL* avl, unsigned int key, unsigned int* res){
    if (avl->root == NULL){
        printf("Tree is Empty\n");
        return 0;
    }

    return _find_(avl->root, key, res);
}

static int _find_(Node* bt_node, unsigned int key, unsigned int* res){
    if (key == bt_node->inf->key){
        (*res) = bt_node->inf->val[0];
        return 1;
    }
    if (key < bt_node->inf->key){
        if (bt_node->lc == NULL){
            return 0;
        }

        return _find_(bt_node->lc, key, res);
    }
    if (key > bt_node->inf->key){
        if (bt_node->rc == NULL){
            return 0;
        }

        return _find_(bt_node->rc, key, res);
    }
}



Node* min(AVL* avl){
    if (avl->root == NULL){
        printf("Tree is Empty\n");
        return 0;
    }

    return _min_(avl->root);
}

static Node* _min_(Node* bt_node){
    if (bt_node->lc != NULL){
        _min_(bt_node->lc);
    }
    else{
        return bt_node;
    }
}



void beauty_print(AVL* avl){
    if (avl->root == NULL){
        printf("Tree is Empty\n");
        return;
    }

    printf("\nTree: \n\n");
    _beauty_print_(avl->root, 0, 0);
}

static void _beauty_print_(Node* node, int height, unsigned int size){
    if (node->rc != NULL){
        _beauty_print_(node->rc, height + 1, size + len_counter(node->inf->key));
    }

    if (size == 0){
        printf("----%d|\n", node->inf->key);
    }
    else{
        for (int i = 0; i < size + height * 4; i++){
            printf(" ");
        }
        printf("|---%d|\n", node->inf->key);
    }

    if (node->lc != NULL){
        _beauty_print_(node->lc, height + 1, size + len_counter(node->inf->key));
    }
}



int simple_max(int a, int b){
    if (a > b)
        return a;
    return b;
}



static int len_counter(unsigned int n){
    if (n == 0){
        return 1;
    }

    int cnt = 0;
    while (n != 0){
        n /= 10;
        cnt ++;
    }

    return cnt;
}
