#include "table.h"
#include <stdlib.h>


Table* create_table(const char* name){
    FILE* file = fopen(name, "wb+");
    Table* table = (Table*)calloc(1, sizeof(Table));
    table->file = file;
    return table;
}


void delete_table(Table* table){
    fclose(table->file);
    free(table);
}


void add(Table* table, unsigned int key, unsigned int par, unsigned int info){
    unsigned int check_key, check_par, check_info, new_par = 0;

    for (int i = 0; i < table->size; i++) {
        fseek(table->file, (long) sizeof(unsigned int) * 3 * i, SEEK_SET);
        download(table, &check_key, &check_par, &check_info);
        if (check_key == par){
            new_par = par;
            break;
        }
	if (check_key == key){
            return;
        }
    }

    fseek(table->file, (long) sizeof(unsigned int) * 3 * table->size, SEEK_SET);
    fwrite(&key, sizeof (unsigned int), 1, table->file);
    fwrite(&new_par, sizeof (unsigned int), 1, table->file);
    fwrite(&info, sizeof (unsigned int), 1, table->file);
    table->size++;
}


void find(Table* table, unsigned int key){
    if (table == NULL){
        printf("Table is Empty\n");
        return;
    }

    unsigned int check_key, check_par, check_info;
    printf("\n|   key    |  parent  |   info   |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        fseek(table->file, (long) sizeof(unsigned int) * 3 * i, SEEK_SET);
        download(table, &check_key, &check_par, &check_info);
        if (check_key == key){
            printf("|");
            printf("%d", check_key);
            for (int j = 0; j < 10 - len_counter(check_key); j++){
                printf(" ");
            }
            printf("|");

            printf("%d", check_par);
            for (int j = 0; j < 10 - len_counter(check_par); j++){
                printf(" ");
            }
            printf("|");

            printf("%d", check_info);
            for (int j = 0; j < 10 - len_counter(check_info); j++){
                printf(" ");
            }
            printf("|\n");
        }
    }
}


void par_find(Table* table, unsigned int par){
    if (table == NULL){
        printf("Table is Empty\n");
        return;
    }

    unsigned int check_key, check_par, check_info;
    printf("\n|   key    |  parent  |   info   |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        fseek(table->file, (long) sizeof(unsigned int) * 3 * i, SEEK_SET);
        download(table, &check_key, &check_par, &check_info);
        if (check_par == par){
            printf("|");
            printf("%d", check_key);
            for (int j = 0; j < 10 - len_counter(check_key); j++){
                printf(" ");
            }
            printf("|");

            printf("%d", check_par);
            for (int j = 0; j < 10 - len_counter(check_par); j++){
                printf(" ");
            }
            printf("|");

            printf("%d", check_info);
            for (int j = 0; j < 10 - len_counter(check_info); j++){
                printf(" ");
            }
            printf("|\n");
        }
    }
}


void delete(Table* table, unsigned int key){
    if (table == NULL){
        printf("Table is Empty\n");
        return;
    }

    unsigned int check_key, check_par, check_info;
    for (int i = 0; i < table->size; i++){
        fseek(table->file, (long) sizeof(unsigned int) * 3 * i, SEEK_SET);
        download(table, &check_key, &check_par, &check_info);
        if (check_key == key) {
            unsigned int last_key, last_par, last_info;

            fseek(table->file, (long) sizeof(unsigned int) * 3 * (table->size - 1), SEEK_SET);
            download(table, &last_key, &last_par, &last_info);

            fseek(table->file, (long) sizeof(unsigned int) * 3 * i, SEEK_SET);
            fwrite(&last_key, sizeof (unsigned int), 1, table->file);
            fwrite(&last_par, sizeof (unsigned int), 1, table->file);
            fwrite(&last_info, sizeof (unsigned int), 1, table->file);
            table->size--;
        }
    }
}



void print(Table* table){
    if (table == NULL){
        printf("Table is Empty\n");
        return;
    }

    unsigned int key, par, info;
    printf("\n|   key    |  parent  |   info   |\n");
    printf("----------------------------------\n");
    for (int i = 0; i < table->size; i++){
        fseek(table->file, (long) sizeof (unsigned int) * 3 * i, SEEK_SET);
        download(table, &key, &par, &info);

        printf("|");
        printf("%d", key);
        for (int j = 0; j < 10 - len_counter(key); j++){
            printf(" ");
        }
        printf("|");

        printf("%d", par);
        for (int j = 0; j < 10 - len_counter(par); j++){
            printf(" ");
        }
        printf("|");

        printf("%d", info);
        for (int j = 0; j < 10 - len_counter(info); j++){
            printf(" ");
        }
        printf("|\n");
    }
    printf("\n");

}


static void download(Table* table, unsigned int* key, unsigned int* par, unsigned int* info){
    fread(key, sizeof(unsigned int), 1, table->file);
    fread(par, sizeof(unsigned int), 1, table->file);
    fread(info, sizeof(unsigned int), 1, table->file);
}


static unsigned int len_counter(unsigned int n){
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
