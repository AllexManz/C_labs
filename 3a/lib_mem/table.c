#include "table.h"
#include <stdlib.h>
#include <stdio.h>

Table* create_table(){
    Table* table = (Table*) calloc(1, sizeof(Table));
    table->ks = NULL;
    return table;
}


void delete_table(Table* table){
    KeySpace* node = table->ks;
    if (node == NULL){
	free(table);
        return;
    }

    delete_ks(table->ks);

    free(table);
}


int add_ks(Table* table, KeySpace* ks){
    KeySpace* node = table->ks;
    KeySpace* next = table->ks;

    if (table->ks == NULL){
        table->ks = ks;
        return 1;
    }

    while(next->next != NULL){
	if (node->next->key == ks->key){
	    delete_ks(ks);
	    return 0;
	}
        next = node->next;
	node = next;
    }

    next->next = ks;
    return 1;
}


void print(Table* table){
    KeySpace* node = table->ks;

    if (node == NULL){
        printf("Table is Empty\n");
        return;
    }

    printf("\n|   key    |  parent  |   info   |\n");
    printf("----------------------------------\n");
    while(node != NULL){
        printf("|");
        printf("%d", node->key);
        for (int i = 0; i < 10 - len_counter(node->key); i++){
            printf(" ");
        }
        printf("|");

        printf("%d", node->par);
        for (int i = 0; i < 10 - len_counter(node->par); i++){
            printf(" ");
        }
        printf("|");

        printf("%d", node->info->info);
        for (int i = 0; i < 10 - len_counter(node->info->info); i++){
            printf(" ");
        }
        printf("|\n");

        node = node -> next;
    }
    printf("\n");
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


Table* find(Table* table, int key){
    Table* new_table = create_table();
    KeySpace *node = table->ks;

    while (node != NULL){
        if (node->key == key){
            add_ks(new_table, create_ks(node->par, node->key, create_item(node->info->info)));
        }

        node = node->next;
    }

    return new_table;
}


Table* par_find(Table* table, int key){
    Table* new_table = create_table();
    KeySpace *node = table->ks;

    while (node != NULL){
        if (node->par == key){
            add_ks(new_table, create_ks(node->par, node->key, create_item(node->info->info)));
        }

        node = node->next;
    }

    return new_table;
}


void delete(Table* table, int key){
    KeySpace *node = table->ks, *prev = NULL;

    while (node != NULL){
        if (node->key == key){
            if(table->ks == node){
                table->ks = node->next;
		node->next = NULL;
                delete_ks(node);
                return;
            }
            if (node->next == NULL){
		prev->next = NULL;
                delete_ks(node);
                return;
            }

            prev->next = node->next;
	    node->next = NULL;
            delete_ks(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void rec_delete(Table* table, int key){
    KeySpace *node = table->ks, *prev = table->ks;

    while (node != NULL){
	if (node->par == key){
            if(table->ks == node){
		while (node != NULL && node->par == key) {
                    KeySpace* temp = node->next;
                    node->next = NULL;
                    delete_ks(node);
                    node = temp;
                }

                table->ks = node;
            }
            else{
                delete(table, node->key);
                node = prev;
            }
        }

	prev = node;
	if (node == NULL)
	    break;
        node = node->next;
    }
}

