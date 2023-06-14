#include <stdio.h>
#include "lib_table/table.h"




int main(){
    int x = 1, key, par, info, check;
    Table* table = NULL;


    do{
        printf("\n\n_____________________________________________\n");
        printf("0 for quiting from program\n");
        printf("1 for table initialisation\n");
        printf("2 for inserting new key_space in table\n");
        printf("3 for deleting existing key_space from table\n");
        printf("4 for recursive deleting key_space from table\n");
        printf("5 for finding by key\n");
        printf("6 for finding by parents key\n");
        printf("7 for printing the table\n");
        printf("_____________________________________________\n\n");

        printf("Your command: ");
        int checker = scanf("%d", &x);
        while(checker != 1 || x < 0 || x > 7){
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
                if (table != NULL)
                    delete_table(table);
                table = create_table("lab.bin");
                break;
            case 2:
                printf("Enter key, parent_key, info: ");
                check = scanf("%d%d%d", &key, &par, &info);
                while(check != 3){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key, parent_key, info: ");
                    check = scanf("%d%d%d", &key, &par, &info);
                }
                if (table == NULL)
			table = create_table("lab.bin");
                add(table, key, par, info);
                print(table);
                break;
            case 3:
                printf("Enter key: ");
                check = scanf("%d", &key);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d", &key);
                }
                if (table == NULL)
			table = create_table("lab.bin");
                delete(table, key);
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
                if (table == NULL)
			table = create_table("lab.bin");
                // rec_delete(table, key);
                print(table);
                break;
            case 5:
                printf("Enter key: ");
                check = scanf("%d", &key);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d", &key);
                }
                if (table == NULL)
			table = create_table("lab.bin");
                find(table, key);
                break;
            case 6:
                printf("Enter parent_key: ");
                check = scanf("%d", &par);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter parent_key: ");
                    check = scanf("%d", &par);
                }
                if (table == NULL)
			table = create_table("lab.bin");
                par_find(table, par);
                break;
            case 7:
                print(table);
                break;
            default:
                printf("!   There is no such command\n");
        }
    }
    while (x != 0);


    if (table != NULL)
        delete_table(table);

    return 0;
}
