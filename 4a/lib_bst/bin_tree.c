#include "bin_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


BT* create_bt(){
    BT* bt = calloc(1, sizeof (BT));
    bt -> root = NULL;
    return bt;
}


void delete_bt(BT* bt){
    delete_node_chain(bt->root);
    free(bt);
}

void print(BT* bt){
    if (bt -> root == NULL){
        printf("The tree is empty\n");
        return;
    }

    printf("\n|    val    |    key    |\n");
    printf("-------------------------\n");
    print_inOrder(bt->root);
}

void print_inOrder(Node* node){
    if (node->lc != NULL){
        print_inOrder(node->lc);
    }

    printf("|%d", node->inf->val);
    for (int i = 0; i < 11 - len_counter(node->inf->val); i++){
        printf(" ");
    }
    printf("|");

    printf("%s\n", node->inf->key);

    if (node->rc != NULL){
        print_inOrder(node->rc);
    }

}

int add_node(BT* bt, Node* node, unsigned int* res){
    if (bt->root == NULL){
        bt->root = node;
        return 0;
    }

    return _add_node(bt->root, node, res);
}

static int _add_node(Node* bt_node, Node* node, unsigned int* res){
    if (strcmp(node->inf->key, bt_node->inf->key) == 0){
        (*res) = bt_node->inf->val;
        return 1;
    }
    if (strcmp(node->inf->key, bt_node->inf->key) < 0){
        if (bt_node->lc == NULL){
            bt_node->lc = node;
            return 0;
        }

        return _add_node(bt_node->lc, node, res);
    }
    if (strcmp(node->inf->key, bt_node->inf->key) > 0){
        if (bt_node->rc == NULL){
            bt_node->rc = node;
            return 0;
        }

        return _add_node(bt_node->rc, node, res);
    }
}

int find(BT* bt, char* key, unsigned int* res){
    if (bt->root == NULL){
        return 0;
    }

    return _find_(bt->root, key, res);
}

static int _find_(Node* bt_node, char* key, unsigned int* res){
    if (strcmp(key, bt_node->inf->key) == 0){
        (*res) = bt_node->inf->val;
        return 1;
    }
    if (strcmp(key, bt_node->inf->key) < 0){
        if (bt_node->lc == NULL){
            return 0;
        }

        return _find_(bt_node->lc, key, res);
    }
    if (strcmp(key, bt_node->inf->key) > 0){
        if (bt_node->rc == NULL){
            return 0;
        }

        return _find_(bt_node->rc, key, res);
    }
}

Node* max(BT* bt){
    if (bt->root == NULL){
        printf("Tree is Empty\n");
        return 0;
    }

    return _max_(bt->root);
}

static Node* _max_(Node* bt_node){
    if (bt_node->rc != NULL){
        _max_(bt_node->rc);
    }
    else{
        return bt_node;
    }
}

void tree_traversal(BT* bt, char* key){
    if (key == NULL){
        print(bt);
        return;
    }
    if (bt->root == NULL){
        printf("Tree is Empty\n");
        return;
    }


    printf("\n|    val    |    key    |\n");
    printf("-------------------------\n");

    _tree_traversal_(bt->root, key);
}

void _tree_traversal_(Node* bt_node, const char* key){
    if (bt_node->lc != NULL){
        _tree_traversal_(bt_node->lc, key);
    }

    if (strcmp(bt_node->inf->key, key) > 0) {
        printf("|%d", bt_node->inf->val);
        for (int i = 0; i < 11 - len_counter(bt_node->inf->val); i++) {
            printf(" ");
        }
        printf("|");

        printf("%s\n", bt_node->inf->key);
    }


    if (bt_node->rc != NULL){
        _tree_traversal_(bt_node->rc, key);
    }
}

void delete(BT* bt, const char* key){
    if (bt->root == NULL){
        printf("Tree is Empty\n");
        return;
    }
    if (strcmp(bt->root->inf->key, key) == 0){
        if (bt->root->lc == NULL && bt->root->rc == NULL){
            delete_node(bt->root);
            bt->root = NULL;
            return;
        }
        if (bt->root->lc == NULL && bt->root->rc != NULL){
            Node* temp = bt->root->rc;
            delete_node(bt->root);
            bt->root = temp;
            return;
        }
        if (bt->root->lc != NULL && bt->root->rc == NULL){
            Node* temp = bt->root->lc;
            delete_node(bt->root);
            bt->root = temp;
            return;
        }
        if (bt->root->lc != NULL && bt->root->rc != NULL) {
            Node *min_node = bt->root->rc, *prev = bt->root->rc;

            while (min_node->lc != NULL) {
                prev = min_node;
                min_node = min_node->lc;
            }

	    prev->lc = min_node->rc;
            min_node->rc = bt->root->rc;
            min_node->lc = bt->root->lc;
            delete_node(bt->root);
            bt->root = min_node;
            return;
        }
    }

    _delete_(bt->root, bt->root, key);
}

static void _delete_(Node* bt_node, Node* prev, const char* key){
    if (strcmp(key, bt_node->inf->key) == 0){
        if (bt_node->lc == NULL && bt_node->rc == NULL){
	    if (prev->lc == bt_node){
                prev->lc = NULL;
            }
            if (prev->rc == bt_node){
                prev->rc = NULL;
            }
            delete_node(bt_node);
            return;
        }
        if (bt_node->lc == NULL && bt_node->rc != NULL){
            if (prev->lc == bt_node){
                prev->lc = bt_node->rc;
            }
            if (prev->rc == bt_node){
                prev->rc = bt_node->rc;
            }
            delete_node(bt_node);
            return;
        }
        if (bt_node->lc != NULL && bt_node->rc == NULL){
            if (prev->lc == bt_node){
                prev->lc = bt_node->lc;
            }
            if (prev->rc == bt_node){
                prev->rc = bt_node->lc;
            }
            delete_node(bt_node);
            return;
        }
        if (bt_node->lc != NULL && bt_node->rc != NULL) {
            Node *min_node = bt_node->rc, *prevert = bt_node->rc;
            while (min_node->lc != NULL) {
                prevert = min_node;
                min_node = min_node->lc;
            }

            prevert->lc = min_node->rc;
	    min_node->rc = bt_node->rc;
            min_node->lc = bt_node->lc;
            if (prev->rc == bt_node){
                prev->rc = min_node;
            }
            if (prev->lc == bt_node){
                prev->lc = min_node;
            }
            delete_node(bt_node);

            return;
        }
    }
    if (strcmp(key, bt_node->inf->key) < 0){
        _delete_(bt_node->lc, bt_node, key);
    }
    if (strcmp(key, bt_node->inf->key) > 0){
        _delete_(bt_node->rc, bt_node, key);
    }
}

Node* min(BT* bt){
    if (bt->root == NULL){
        printf("Tree is Empty\n");
        return 0;
    }

    return _min_(bt->root);
}

static Node* _min_(Node* bt_node){
    if (bt_node->lc != NULL){
        _min_(bt_node->lc);
    }
    else{
        return bt_node;
    }
}

void beauty_print(BT* bt){
    if (bt->root == NULL){
        printf("Tree is Empty\n");
        return;
    }

    printf("\nTree: \n\n");
    _beauty_print_(bt->root, 0, 0);
}

static void _beauty_print_(Node* node, int height, unsigned int size){
    if (node->rc != NULL){
        _beauty_print_(node->rc, height + 1, size + strlen(node->inf->key));
    }

    if (size == 0){
        printf("----%s|\n", node->inf->key);
    }
    else{
        for (int i = 0; i < size + height * 4; i++){
            printf(" ");
        }
        printf("|---%s|\n", node->inf->key);
    }

    if (node->lc != NULL){
        _beauty_print_(node->lc, height + 1, size + strlen(node->inf->key));
    }
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
