#include "lib_bst/bin_tree.h"
#include "lib_bst/node.h"
#include <stdio.h>
#include <stdlib.h>
#include "lib_bst/file_acces.h"


int main(){
    int x = 0, check, clean;
    unsigned int res = 0, info;
    char* key = NULL;

    Node* node = NULL;
    BT *bt = create_bt();


    do{
        printf("\n\n_____________________________________________\n");
        printf("0 for quiting from program\n");
        printf("1 for inserting new node in the tree\n");
        printf("2 for deleting node from the tree\n");
        printf("3 for tree traversal\n");
        printf("4 for finding the value in tree by key\n");
        printf("5 for finding the max key value in the tree\n");
        printf("6 for printing the tree InOrder\n");
        printf("7 for reading the tree from file\n");
        printf("8 for printing the tree in Tree-Shape\n");
        printf("_____________________________________________\n\n");

        printf("Your command: ");
        int checker = scanf("%d", &x);
        while(checker != 1 || x < 0 || x > 8){
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
                while ((clean = getchar()) != '\n' && clean != EOF){}
                clean=0;
                key = rl("Enter key: ");
                printf("Enter info: ");
                check = scanf("%d", &info);
                while(check != 1){
                    printf("\n!    Wrong input. Numbers should be digital\n\n");
                    scanf("%*[^\n]");
                    printf("Enter info: ");
                    check = scanf("%d", &info);
                }
                if (bt == NULL)
                    bt = create_bt();
                if (add_node(bt, create_node(create_item(key, info)), &res) == 1)
                    printf("Old value: %d\n", res);
                free(key);
                beauty_print(bt);
                break;
            case 2:
                while ((clean = getchar()) != '\n' && clean != EOF){}
                clean=0;
                key = rl("Enter key: ");
                printf("Enter info: ");
                if (bt == NULL)
                    bt = create_bt();
                delete(bt, key);
                free(key);
                beauty_print(bt);
                break;
            case 3:
                while ((clean = getchar()) != '\n' && clean != EOF){}
                clean=0;
                key = rl("Enter key: ");
                printf("Enter info: ");
                if (bt == NULL)
                    bt = create_bt();
                tree_traversal(bt, key);
                free(key);
                beauty_print(bt);
                break;
            case 4:
                while ((clean = getchar()) != '\n' && clean != EOF){}
                clean=0;
                key = rl("Enter key: ");
                printf("Enter info: ");
                if (bt == NULL)
                    bt = create_bt();
                if(find(bt, key, &res) == 1)
                    printf("Found value: %d\n", res);
                free(key);
                beauty_print(bt);
                break;
            case 5:
                node = max(bt);
                if (node != NULL){
                    printf("Key: %s\n", node->inf->key);
                    printf("Val: %d\n", node->inf->val);
                    node = NULL;
                }
                break;
            case 6:
                if (bt == NULL)
                    bt = create_bt();
                print(bt);
                break;
            case 7:
                if (bt == NULL)
                    bt = create_bt();
                open(bt);
		beauty_print(bt);
                break;
            case 8:
                if (bt == NULL)
                    bt = create_bt();
                beauty_print(bt);
                break;
            default:
                printf("!   There is no such command\n");
        }
    }
    while (x != 0);

    if (bt != NULL)
        delete_bt(bt);

    return 0;
}
