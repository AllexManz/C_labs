#include "file_acces.h"
#include "bin_tree.h"
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int open(BT* bt){
    FILE* file = fopen("input.txt", "r");

    char *temp = NULL, *key = NULL;
    unsigned int res;


    while (!feof(file)){
	key = myl(file);
        temp = myl(file);

        if (key != NULL && temp != NULL){
            add_node(bt, create_node(create_item(key, string_to_int(temp))), &res);
        }

        if (temp != NULL)
            free(temp);
        if (key != NULL)
            free(key);
    }

    fclose(file);
    print(bt);

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


static char *myl(FILE *file) {  // считывает строку
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

char *rl(const char* input) {
    printf("%s", input);
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;

    do {
        n = scanf("%80[^\n]", buf);

        if (n < 0) {
            return NULL;
        }
        if (n > 0) {
            int chunck_len = strlen(buf);
            int str_len = len + chunck_len;
            res = realloc(res, sizeof (char) * (str_len + 1));
            memcpy(res + len, buf, chunck_len);
            len = str_len;
        }
        if (n == 0){
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) res[len] = '\0';
    else res = calloc(1, sizeof(char));
    return res;
}
