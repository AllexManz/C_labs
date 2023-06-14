#include "graph.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "algo.h"

// SEM_2/LAB_5/main.c SEM_2/LAB_5/graph.c SEM_2/LAB_5/graph.h SEM_2/LAB_5/vertex.c SEM_2/LAB_5/vertex.h SEM_2/LAB_5/edge.c SEM_2/LAB_5/edge.h
char *readline(const char* input) {
    printf("%s", input);
    int clean;
    while ((clean = getchar()) != '\n' && clean != EOF){}
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



int main(){
    Graph* graph = NULL;
    int x = 0, check = 0, type = 0, size = 0;
    char* key = NULL, *key1 = NULL, *key2 = NULL;

    do{
        printf("\n\n_____________________________________________\n");
        printf("0 for quiting from program\n");
        printf("1 for adding new vertex in the graph\n");
        printf("2 for adding new edge in the graph\n");
        printf("3 for deleting the edge from the graph\n");
        printf("4 for deleting the vertex from the graph\n");
        printf("5 for changing vertex id\n");
        printf("6 for changing the edge weight\n");
        printf("7 for checking for a path\n");
        printf("8 for finding the shortest path\n");
        printf("9 for creating skeleton of the graph\n");
        printf("10 for matrix printing\n");
        printf("_____________________________________________\n\n");

        printf("Your command: ");
        int checker = scanf("%d", &x);
        while(checker != 1 || x < 0 || x > 10){
            printf("\n!    Wrong input. Command should be digital number greater than -1 and lesser than 10.\n\n");
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
                // Adding new vertex in the graph
                key = readline("Enter vertex key: ");

                printf("Enter vertex type: \n");
                printf("1: Maze entrance\n");
                printf("2: Maze exit\n");
                printf("3: Simple Room\n\n");

                printf("Type: ");
                check = scanf("%d", &type);
                while(check != 1 || type < 0 || type > 3){
                    printf("\n!    Wrong input. Numbers should be digital, between 0 and 3\n");
                    scanf("%*[^\n]");

                    printf("1: Maze entrance\n");
                    printf("2: Maze exit\n");
                    printf("3: Simple Room\n");
                    printf("Enter vertex type: ");
                    check = scanf("%d", &type);
                }
                if (graph == NULL)
                    graph = create_graph();
                printf("%s\n%d", key, type);
                add_vertex(graph, create_vertex(key, type));
                free(key);
                //beauty_print(avl);
                break;
            case 2:
                // Adding new edge in the graph
                key1 = readline("Enter vertex1 key: ");
                printf("Enter edge weight: ");
                check = scanf("%d",&size);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital and positive\n\n");
                    scanf("%*[^\n]");
                    printf("Enter edge weight: ");
                    check = scanf("%d",&size);
                }
                key2 = readline("Enter vertex2 key: ");

                if (graph == NULL)
                    graph = create_graph();
                add_edge(graph, key1, key2, size);
                free(key1);
                free(key2);
                //beauty_print(avl);
                break;
            case 3:
                // Deleting the edge from the graph
                key1 = readline("Enter vertex1 key: ");
                printf("Enter edge weight: ");
                check = scanf("%d",&size);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital and positive\n\n");
                    scanf("%*[^\n]");
                    printf("Enter edge weight: ");
                    check = scanf("%d",&size);
                }
                key2 = readline("Enter vertex2 key: ");

                if (graph == NULL)
                    graph = create_graph();

                del_edge(graph, key1, key2);
                free(key1);
                free(key2);
                //beauty_print(avl);
                break;
            case 4:
                // Deleting the vertex from the graph
                key1 = readline("Enter vertex key: ");

                if (graph == NULL)
                    graph = create_graph();

                del_vertex(graph, key1);
		free(key1);
                print_matrix(graph);
                break;
	    case 5:
                // Changing vertex id
                key1 = readline("Enter original vertex key: ");

                printf("Enter new vertex type: \n");
                printf("1: Maze entrance\n");
                printf("2: Maze exit\n");
                printf("3: Simple Room\n\n");

                printf("Type: ");
                check = scanf("%d", &type);
                while(check != 1 || type < 0 || type > 3){
                    printf("\n!    Wrong input. Numbers should be digital, between 0 and 3\n");
                    scanf("%*[^\n]");

                    printf("1: Maze entrance\n");
                    printf("2: Maze exit\n");
                    printf("3: Simple Room\n");
                    printf("Enter vertex type: ");
                    check = scanf("%d", &type);
                }

                key2 = readline("Enter new vertex key: ");

                if (graph == NULL)
                    graph = create_graph();

		change_vertex(graph, key1, key2, type);

                free(key1);
                free(key2);

                break;
	    case 6:
                // Changing edge weight
                key1 = readline("Enter vertex1 key: ");
                printf("Enter new edge weight: ");
                check = scanf("%d",&size);
                while(check != 1){
                    printf("\n!    Wrong input. Number should be digital and positive\n\n");
                    scanf("%*[^\n]");
                    printf("Enter new edge weight: ");
                    check = scanf("%d",&size);
                }
                key2 = readline("Enter vertex2 key: ");

                if (graph == NULL)
                    graph = create_graph();

		change_edge(graph, key1, key2, size);
                print_matrix(graph);

                free(key1);
                free(key2);
                break;
	    case 7:
                // Checking for a path via DFS
                if (graph == NULL)
                    graph = create_graph();

                key = readline("Enter vertex key: ");
                dfs(graph, key);
		free(key);
                break;
            case 8:
                // Finding the shortest paths from the vertex
                if (graph == NULL)
                    graph = create_graph();

                key = readline("Enter vertex key: ");
                BellmanFord(graph, key);
                free(key);
                break;
	    case 9:
                // Printing the skeleton of the graph
                if (graph == NULL)
                    graph = create_graph();

                skeleton(graph);
                break;
            case 10:
                // Printing
                print_matrix(graph);
                printf("\n\n");
                break;
            default:
                printf("!   There is no such command\n");
        }
    }
    while (x != 0);

    if (graph != NULL)
        erase_graph(graph);

    return 0;
}
