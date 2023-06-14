#include <stdio.h>
#include <readline/readline.h>

#if defined HASH
#include "lib_hash/table.h"
#endif

int main(){
    unsigned int x = 1, key, version, check;
    char* inf;
    Table* table = create_table(), *new_table = NULL;

    do{
        printf("\n\n_____________________________________________\n");
        printf("0 for quiting from program\n");
        printf("1 for inserting new key_space in table\n");
        printf("2 for deleting existing key_space from table\n");
        printf("3 for deleting value by hash and key\n");
        printf("4 for finding by key\n");
        printf("5 for finding by hash and key\n");
        printf("6 for printing the table\n");
        printf("_____________________________________________\n\n");

        printf("Your command: ");
        int checker = scanf("%d", &x);
        while(checker != 1 || x < 0 || x > 6){
            printf("\n!    Wrong input. Command should be digital number greater than -1 and lesser than 6.\n\n");
            scanf("%*[^\n]");
            printf("Enter your command: ");
            checker = scanf("%d", &x);
        }
        switch (x) {
            case 0:
                printf("Successfully finished program\n");
                break;
            case 1:
                printf("Enter key: ");
                check = scanf("%d", &key);
                while(check != 1){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d", &key);
                }
                inf = readline("Enter info: ");
                if (table == NULL)
                    table = create_table();
                add_ks(table, create_ks(key, create_node(create_item(inf))));
                free(inf);
                print(table);
                break;
            case 2:
                printf("Enter key: ");
                check = scanf("%d", &key);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d", &key);
                }
                if (table == NULL)
                    table = create_table();
                special_delete(table, key);
                print(table);
                break;
            case 3:
                printf("Enter key and version: ");
                check = scanf("%d%d", &key, &version);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d%d", &key, &version);
                }
                if (table == NULL)
                    table = create_table();
                my_delete(table, key, version);
                print(table);
                break;
            case 4:
                printf("Enter key: ");
                check = scanf("%d", &key);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d", &key);
                }
                if (new_table != NULL)
                    delete_table(new_table);
                if (table == NULL)
                    table = create_table();
                new_table = find(table, key);
                print(new_table);
                delete_table(new_table);
                new_table = NULL;
                break;
            case 5:
                printf("Enter key and version: ");
                check = scanf("%d%d", &key, &version);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key and version: ");
                    check = scanf("%d%d", &key, &version);
                }
                if (new_table != NULL)
                    delete_table(new_table);
                if (table == NULL)
                    table = create_table();
                new_table = my_find(table, key, version);
                print(new_table);
                delete_table(new_table);
                new_table = NULL;
                break;
            case 6:
                print(table);
                break;
            default:
                printf("!   There is no such command\n");
        }
    }
    while (x != 0);


    if (table != NULL)
        delete_table(table);
    if (new_table != NULL)
        delete_table(new_table);


    return 0;
}
