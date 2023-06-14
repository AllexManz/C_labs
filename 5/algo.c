#include "algo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Queue* create_queue(){
    Queue* queue = calloc(1, sizeof(Queue));
    return queue;
}


void delete_queue(Queue* queue){
    free(queue->arr);
    free(queue);
}


void add_queue(Queue* queue, Edge* v){
    queue->size += 1;
    queue->arr = realloc(queue->arr, sizeof(Edge *) * queue->size);
    queue->arr[queue->size - 1] = v;
}


Edge * rem_queue(Queue* queue){
    Edge *v = queue->arr[0];

    for (int i = 1; i < queue->size; i++){
        queue->arr[i - 1] = queue->arr[i];
    }

    queue->size -= 1;
    queue->arr = realloc(queue->arr, sizeof(Edge *) * queue->size);

    return v;
}


void dfs(Graph* graph, char* key){
    int* visited = calloc(graph->n_vert, sizeof(int));

    int pos = -1;
    //Finding the vertex in the graph
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, key) == 0){
            //vertex = graph->vertexes[i];
            pos = i;
        }
    }
    if (pos == -1){
        printf("There is no such vertex\n");
        free(visited);
        return;
    }

    if (__dfs(graph, &visited, pos)){
        printf("There is a path\n");
    }
    else{
        printf("There is no path\n");
    }
    free(visited);
}


int __dfs(Graph* graph, int** visited, int v){
    (*visited)[v] = 1;

    for (int i = 0; i < graph->n_vert; i++){
        if (graph->matrix[v][i] != 0  && visited[i] == 0){
            if (graph->vertexes[i]->type == 2){
                return 1;
            }
            __dfs(graph, visited, i);
        }
    }

    return 0;
}


void BellmanFord(Graph* graph, char* key){
    //Finding the vertex in the graph
    int pos = -1;
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, key) == 0){
            pos = i;
        }
    }
    if (pos == -1){
        printf("There is no such vertex\n");
        return;
    }

    // Preparing distance array
    int* weights = calloc(graph->n_vert, sizeof(int));
    for (int i = 0; i < graph->n_vert; i++){
        weights[i] = 999999;
    }
    weights[pos] = 0;


    for (int l = 0; l < graph->n_vert; l++){

        // First Vertex
        for (int u = 0; u < graph->n_vert; u++){

            // Second Vertex
            for (int v = 0; v < graph->n_vert; v++){
                if (weights[u] != 999999 && graph->matrix[u][v] != 0){
                    int w = 0;

                    // Finding edge between vertexes
                    for (int i = 0; i < graph->n_edge; i++){
                        if (strcmp(graph->edges[i]->v1->id, graph->vertexes[u]->id) == 0 &&
                            strcmp(graph->edges[i]->v2->id, graph->vertexes[v]->id) == 0){
                            w = graph->edges[i]->size;
                        }
                        if (strcmp(graph->edges[i]->v1->id, graph->vertexes[v]->id) == 0 &&
                            strcmp(graph->edges[i]->v2->id, graph->vertexes[u]->id) == 0){
                            w = graph->edges[i]->size;
                        }
                    }

                    // Updating weights
                    if (weights[u] + w < weights[v]){
                        weights[v] = weights[u] + w;
                    }
                }
            }
        }
    }

    printf("Distances between the chosen vertex and all other vertexes\n");
    for (int i = 0; i < graph->n_vert; i++){
        printf("%d ", weights[i]);
    }
    free(weights);
}


void skeleton(Graph* graph){
    int size = 0;
    Queue* queue = create_queue();

    int* tree_id = calloc(graph->n_vert, sizeof (int));
    for (int i = 0; i < graph->n_vert; i++)
        tree_id[i] = i;

    for (int i = 0; i < graph->n_edge; i++){
        size += graph->edges[i]->size;

        int pos1 = 0, pos2 = 0;
        for (int j = 0; j < graph->n_vert; j++){
            if (strcmp(graph->vertexes[j]->id, graph->edges[i]->v1->id) == 0) pos1 = j;
            if (strcmp(graph->vertexes[j]->id, graph->edges[i]->v2->id) == 0) pos2 = j;
        }

        if (tree_id[pos1] != tree_id[pos2]){
            size += graph->edges[i]->size;

            add_queue(queue, graph->edges[i]);
            int old = tree_id[pos2], new = tree_id[pos1];
            for (int k = 0; k < graph->n_vert; k++){
                if (tree_id[k] == old)
                    tree_id[k] = new;
            }
        }
    }

    free(tree_id);
    for (int i = 0; i < queue->size; i++){
        printf("V1: %s, V2: %s, edge size: %d\n", queue->arr[i]->v1->id, queue->arr[i]->v2->id, queue->arr[i]->size);
    }
    delete_queue(queue);
}
