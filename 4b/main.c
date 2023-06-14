#include <stdio.h>
#include "lib_avl/avl_tree.h"
#include "time.h"
#include "lib_avl/file_acces.h"


void timing();


int main(){
    AVL* avl = create_avl();
    Node* node = NULL;
    int x = 0, check;
    unsigned int res = 0, info, key;



    do{
        printf("\n\n_____________________________________________\n");
        printf("0 for quiting from program\n");
        printf("1 for inserting new node in the tree\n");
        printf("2 for deleting node from the tree\n");
        printf("3 for tree traversal\n");
        printf("4 for finding the value in tree by key\n");
        printf("5 for finding the min key value in the tree\n");
        printf("6 for printing the tree InOrder\n");
        printf("7 for reading the tree from file\n");
        printf("8 for printing the tree in Tree-Shape\n");
        printf("9 for timing\n");
        printf("_____________________________________________\n\n");

        printf("Your command: ");
        int checker = scanf("%d", &x);
        while(checker != 1 || x < 0 || x > 9){
            printf("\n!    Wrong input. Command should be digital number greater than -1 and lesser than 6.\n\n");
            scanf("%*[^\n]");
            printf("Enter your command: ");
            checker = scanf("%d", &x);
        }
        switch (x) {
            case 0:
                // Quiting from program
                printf("Successfully finished program\n");
                break;
            case 1:
                // Inserting new node in the tree
                printf("Enter key and info: ");
                check = scanf("%d%d",&key, &info);
                while(check != 2){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key and info: ");
                    check = scanf("%d%d",&key, &info);
                }
                if (avl == NULL)
                    avl = create_avl();
                add_node(avl, create_node(create_item(key, info)));
                beauty_print(avl);
                break;
            case 2:
                // Deleting node from the tree
                printf("Enter key: ");
                check = scanf("%d",&key);
                while(check != 1){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d",&key);
                }
                if (avl == NULL)
                    avl = create_avl();
                delete(avl, key);
                beauty_print(avl);
                break;
            case 3:
                // Tree traversal
                printf("Enter key: ");
                check = scanf("%d",&key);
                while(check != 1){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d",&key);
                }
                if (avl == NULL)
                    avl = create_avl();
                tree_traversal(avl, key);
                beauty_print(avl);
                break;
            case 4:
                // Finding the value in tree by key
                printf("Enter key: ");
                check = scanf("%d",&key);
                while(check != 1){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter key: ");
                    check = scanf("%d",&key);
                }
                if (avl == NULL)
                    avl = create_avl();
                if(find(avl, key, &res) == 1)
                    printf("Found value: %d\n", res);
                beauty_print(avl);
                break;
            case 5:
                // Finding the min key value in the tree
                node = min(avl);
                if (node != NULL){
                    printf("Key: %d\n", node->inf->key);
                    for (int i = 0; i < node -> inf -> n; i++){
                        printf("Val[%d]: %d\n", i + 1, node->inf->val[i]);
                    }
                    node = NULL;
                }
                break;
            case 6:
                // Printing the tree InOrder
                if (avl == NULL)
                    avl = create_avl();
                print(avl, 2);
                break;
            case 7:
                // Reading the tree from file
                if (avl == NULL)
                    avl = create_avl();
                open(avl);
                break;
            case 8:
                // Printing the tree in Tree-Shape
                if (avl == NULL)
                    avl = create_avl();
                beauty_print(avl);
                break;
            case 9:
                // Timing
                timing();
                break;
            default:
                printf("!   There is no such command\n");
        }
    }
    while (x != 0);

    if (avl != NULL)
        delete_avl(avl);



    return 0;
}



void timing() {
    AVL *avl = create_avl();
    FILE *file = fopen("output.txt", "w+");

    unsigned int key = 0, info = 0;
    unsigned int res;
    clock_t start_time, end_time;

    for (int i = 1; i <= 500001; i += 5000) {
        printf("PERCENT: %d\n", i / 5000);
        n_open(avl, i);
        beauty_print(avl);



        start_time = clock();  // добавление
        add_node(avl, create_node(create_item(key, info)));
        end_time = clock();
        fprintf(file, "INSERT %lf\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
        printf("OK1\n");


        start_time = clock();  // удаление
        delete(avl, key);
        end_time = clock();
        fprintf(file, "DELETE %lf\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
        printf("OK2\n");


        start_time = clock();  // обход
        timing_tree_traversal(avl, key);
        end_time = clock();
        fprintf(file, "TRAVER %lf\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
        printf("OK3\n");

        start_time = clock();  // поиск
        find(avl, key, &res);
        end_time = clock();
        fprintf(file, "FIND %lf\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
        printf("OK4\n");

        start_time = clock();  // спец_поиск
        min(avl);
        end_time = clock();
        fprintf(file, "SPEC_FIND %lf\n", (double) (end_time - start_time) / CLOCKS_PER_SEC);
        printf("OK5\n");
    }

    fclose(file);
    if (avl != NULL)
        delete_avl(avl);
}
