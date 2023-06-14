#include "file_acces.h"
#include "avl_tree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int open(AVL* avl){
    FILE* file = fopen("../test_input.txt", "r");

    if (file)
	printf("YES\n");
    else
	printf("NO\n");

    char *info = NULL, *key = NULL;

    while (!feof(file)){
        key = myl(file);
        // printf("Key: %s\n", key);
        info = myl(file);
        // printf("Info: %s\n", info);

        if (key != NULL && info != NULL){
            add_node(avl, create_node(create_item(string_to_int(key), string_to_int(info))));
        }

        if (info != NULL)
            free(info);
        if (key != NULL)
            free(key);
    }

    fclose(file);
    beauty_print(avl);
    print(avl, 1);
    return 0;
}

int n_open(AVL* avl, int n){
    FILE* file = fopen("../input.txt", "r");

    char *info = NULL, *key = NULL;

    int i = 0;
    while (!feof(file) && i < n){
        key = myl(file);
        //printf("Key: %s\n", key);
        info = myl(file);
        //printf("Info: %s\n", info);

        if (key != NULL && info != NULL){
            add_node(avl, create_node(create_item(string_to_int(key), string_to_int(info))));
        }

        if (info != NULL)
            free(info);
        if (key != NULL)
            free(key);
        i += 1;
    }

    fclose(file);
    return 0;
}


static unsigned int string_to_int(char *str) {
    unsigned int result = 0;
    while (*str != '\0') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}


static char *myl(FILE *file) {
    char *input = malloc(sizeof (char));
    input[0] = '\0';

    char buf[81] = {0};
    int flag = 1, length = 0, buf_len;
    while (flag > 0) {
        flag = fscanf(file, "%80[^\n]", buf);
        if (flag == EOF) {
            free(input);
            return NULL;
        }
        if (!flag)
            fscanf(file, "%*c");
        else {
            buf_len = strlen(buf);
            length += buf_len;
            input = realloc(input, length + 1);
            memcpy(input + length - buf_len, buf, buf_len * sizeof (char));
            input[length] = '\0';
        }
    }
    return input;
}
