#include "table.h"
#include "stdio.h"
#include "string.h"


Table* create_table(){
    Table* table = (Table*) calloc(1, sizeof (Table));
    table -> ks = (KeySpace**) calloc(10, sizeof (KeySpace*));
    table -> c_size = 0;
    table -> max_size = MAX_SIZE;
    return table;
}

void delete_table(Table* table){
    for (int i = 0; i < table->max_size; i++){
        if (table->ks[i] != NULL)
            delete_ks(table->ks[i]);
    }
    free(table->ks);
    free(table);
}

void add_ks(Table* table, KeySpace* ks){
    unsigned int key = hash(ks->node->release);
    if (table->ks[key] == NULL){
        table->ks[key] = ks;
        table->c_size += 1;
        return;
    }

    Node* node = table->ks[key]->node;
    while (node->next != NULL){
        node = node->next;
    }
    node->next = ks->node;
    table->c_size += 1;

    ks->node = NULL;
    delete_ks(ks);
}

void print(Table* table){
    if (table->c_size == 0){
        printf("Table is Empty\n");
        return;
    }

    printf("\n|   HASH   |   KEY    |   INFO   \n");
    printf("----------------------------------\n");
    for (int i = 0; i < table->max_size; i++){
        if(table->ks[i] != NULL){

            Node* node = table->ks[i]->node;

            while (node != NULL){

                // Hash field
                printf("|");
                printf("%d", i);
                for (int k = 0; k < 10 - len_counter(i); k++){
                    printf(" ");
                }
                printf("|");

                // Key field
                printf("%d", node->release);
                for (int k = 0; k < 10 - len_counter(node->release); k++){
                    printf(" ");
                }
                printf("|");

                // Info field
                printf("%s\n", node->info->info);

                node = node->next;
            }
        }
    }

    printf("\n");
}

void special_delete(Table* table, unsigned int key){
    for (int i = 0; i < table->max_size; i++){
        if (table->ks[i] != NULL){

            Node *node = table->ks[i]->node, *prev = table->ks[i]->node;
            while (node != NULL){
                if (node->release == key){

                    if (table->ks[i]->node == node){
                        table->ks[i]->node = node->next;
                        if (node->next == NULL){
                            delete_ks(table->ks[i]);
                            table->ks[i] = NULL;
                        }
                        delete_node(node);
                        return;
                    }

                    prev->next = node->next;
                    delete_node(node);
                }

                prev = node;
                node = node->next;
            }
        }
    }
}

Table* find(Table* table, unsigned int key){
    Table* new_table = create_table();
    for (int i = 0; i < table->max_size; i++){
        if (table->ks[i] != NULL){
            Node* node = table->ks[i]->node;

            while (node != NULL){
                if (node->release == key){
                    add_ks(new_table, create_ks(key, create_node(create_item(node->info->info))));
                }
                node = node->next;
            }
        }
    }

    return new_table;
}

void my_delete(Table* table, unsigned int key, unsigned int version){
    if (key < (table->max_size - 1) && table->ks[key] != NULL){

        Node *node = table->ks[key]->node, *prev = table->ks[key]->node;
        while (node != NULL){
            if (node->release == version){

                if (table->ks[key]->node == node){
                    table->ks[key]->node = node->next;
                    if (node->next == NULL){
                        delete_ks(table->ks[key]);
                        table->ks[key] = NULL;
                        table->c_size -= 1;
                    }
                    delete_node(node);
                    return;
                }

                prev->next = node->next;
                delete_node(node);
            }

            prev = node;
            node = node->next;
        }
    }
}

Table* my_find(Table* table, unsigned int key, unsigned int version){
    Table* new_table = create_table();

    if (table->ks[key] != NULL){
        Node* node = table->ks[key]->node;

        while (node != NULL){
            if (node->release == version){
                add_ks(new_table, create_ks(version, create_node(create_item(node->info->info))));
            }
            node = node->next;
        }
    }

    return new_table;
}

static int len_counter(int n){
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

static unsigned int hash(unsigned int n){
    return n % MAX_SIZE;
}
