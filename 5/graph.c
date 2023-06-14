#include <stdlib.h>
#include "graph.h"
#include "string.h"
#include "stdio.h"


Graph* create_graph(){
    Graph* graph = calloc(1, sizeof (Graph));
    return graph;
}


void erase_graph(Graph* graph){
    delete_matrix(graph);
    for (int i = 0; i < graph->n_vert; i++){
        erase_vertex(graph->vertexes[i]);
        free(graph->desc[i]);
    }
    free(graph->desc);
    free(graph->vertexes);
    free(graph->edges);
    free(graph);
}


void delete_matrix(Graph* graph){
    for (int i = 0; i < graph->n_vert; i++){
        free(graph->matrix[i]);
    }
    free(graph->matrix);
}


void print_matrix(Graph* graph){
    printf("Matrix: \n");
    for (int i = 0; i < graph->n_vert; i++){
        for (int j = 0; j < graph->n_vert; j++){
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void add_row_and_coll(Graph* graph){
    // Adding new row to a matrix and expanding it
    graph->matrix = realloc(graph->matrix, sizeof (int*) * graph->n_vert);
    graph->matrix[graph->n_vert - 1] = calloc(graph->n_vert, sizeof(int));

    for (int i = 0; i < graph->n_vert; i++){
        graph->matrix[i] = realloc(graph->matrix[i], sizeof(int) * graph->n_vert);
        graph->matrix[i][graph->n_vert - 1] = 0;
    }
}


void add_vertex(Graph* graph, struct Vertex* vertex){
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->desc[i], vertex->id) == 0){
            erase_vertex(vertex);
            return;
        }
    }

    graph->n_vert += 1;
    add_row_and_coll(graph);

    graph->desc = realloc(graph->desc, sizeof(char *) * graph->n_vert);
    graph->desc[graph->n_vert - 1] = strdup(vertex->id);

    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex*) * graph->n_vert);
    graph->vertexes[graph->n_vert - 1] = vertex;
}


void add_edge(Graph* graph, const char* key1, const char* key2, int size){
    // Hyper circles are not allowed in this graph
    if (strcmp(key1, key2) == 0) return;

    // Edge weights must be positive
    if (size < 0) return;

    // Checking existence of the vertexes
    int flag1 = 0, flag2 = 0;
    Vertex *v1 = NULL, *v2 = NULL;
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, key1) == 0) {
            flag1 = 1;
            v1 = graph->vertexes[i];
        }
        if (strcmp(graph->vertexes[i]->id, key2) == 0) {
            flag2 = 1;
            v2 = graph->vertexes[i];
        }
    }
    if (flag1 == 0 || flag2 == 0){
        return;
    }

    // Checking existence of the edge
    for (int i = 0; i < graph->n_edge; i++){
        if (strcmp(graph->edges[i]->v1->id, key1) == 0 && strcmp(graph->edges[i]->v2->id, key2) == 0) return;
    }

    //Adding an edge to the first vertex
    Edge *edge = create_edge(v1, v2, size);
    graph->n_edge += 1;
    graph->edges = realloc(graph->edges, sizeof(Edge*) * graph->n_edge);
    graph->edges[graph->n_edge - 1] = edge;

    v1->n_edges += 1;
    v1->edges = realloc(v1->edges, sizeof(Edge*) * v1->n_edges);
    v1->edges[v1->n_edges - 1] = edge;

    //Adding an edge to the second vertex
    edge = create_edge(v1, v2, size);
    graph->n_edge += 1;
    graph->edges = realloc(graph->edges, sizeof(Edge*) * graph->n_edge);
    graph->edges[graph->n_edge - 1] = edge;

    v2->n_edges += 1;
    v2->edges = realloc(v2->edges, sizeof(Edge*) * v2->n_edges);
    v2->edges[v2->n_edges - 1] = edge;

    //Adding the edge to the matrix
    int pos1 = 0, pos2 = 0;
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->desc[i], v1->id) == 0)
            pos1 = i;
        if (strcmp(graph->desc[i], v2->id) == 0)
            pos2 = i;
    }

    printf("\nOld ");
    print_matrix(graph);
    graph->matrix[pos1][pos2] = size;
    graph->matrix[pos2][pos1] = size;
    printf("New ");
    print_matrix(graph);
}


void del_vertex(Graph* graph, const char* key){
    Vertex* vertex = NULL;
    int pos = 0;
    //Finding the vertex in the graph
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, key) == 0){
            vertex = graph->vertexes[i];
            pos = i;
        }
    }

    // Deleting all edges that are connected to the vertex
    int i = 0, n = graph->n_edge;
    while (i < n){
        if (strcmp(graph->edges[i]->v1->id, key) == 0){
            del_edge(graph, graph->edges[i]->v1->id, graph->edges[i]->v2->id);
	    n -= 1;
	    i = -1;
        }
        else if (strcmp(graph->edges[i]->v2->id, key) == 0){
            del_edge(graph, graph->edges[i]->v1->id, graph->edges[i]->v2->id);
	    n -= 1;
	    i = -1;
        }
        i++;
    }

    // Deleting a description that is connected to the vertex
    free(graph->desc[pos]);
    for (int k = pos + 1; k < graph->n_vert; k++){
        graph->desc[k - 1] = graph->desc[k];
    }
    graph->desc = realloc(graph->desc, sizeof(char*) * (graph->n_vert - 1));


    // Editing the matrix
    for (i = pos; i < graph->n_vert; i++){
        for (int j = pos + 1; j < graph->n_vert; j++){
            graph->matrix[i][j - 1] = graph->matrix[i][j];
        }
        graph->matrix[i] = realloc(graph->matrix[i], sizeof(int) * (graph->n_vert - 1));
    }
    free(graph->matrix[pos]);
    for (i = pos + 1; i < graph->n_vert; i++){
        graph->matrix[i - 1] = graph->matrix[i];
    }
    graph->matrix = realloc(graph->matrix, sizeof (int*) * (graph->n_vert - 1));


    // Deleting the vertex itself
    for (int j = pos + 1; j < graph->n_vert; j++){
        graph->vertexes[j - 1] = graph->vertexes[j];
    }
    erase_vertex(vertex);
    graph->n_vert -= 1;
    graph->vertexes = realloc(graph->vertexes, sizeof(Vertex*) * graph->n_vert);
}


void del_edge(Graph* graph, const char* key1, const char* key2){
    // Hyper circles are not allowed in this graph
    if (strcmp(key1, key2) == 0) return;

    int cnt = 0;
    for (int i = 0; i < graph->n_edge; i++){
        if (strcmp(graph->edges[i]->v1->id, key1) == 0 && strcmp(graph->edges[i]->v2->id, key2) == 0){
            for (int j = 0; j < graph->edges[i]->v1->n_edges; j++){
                if (graph->edges[i]->v1->edges[j] == graph->edges[i])
                    graph->edges[i]->v1->edges[j] = NULL;
            }
            for (int j = 0; j < graph->edges[i]->v2->n_edges; j++){
                if (graph->edges[i]->v2->edges[j] == graph->edges[i])
                    graph->edges[i]->v2->edges[j] = NULL;
            }
            erase_edge(graph->edges[i]);
            graph->edges[i] = NULL;
            cnt += 1;
        }
        else if (strcmp(graph->edges[i]->v1->id, key2) == 0 && strcmp(graph->edges[i]->v2->id, key1) == 0){
            for (int j = 0; j < graph->edges[i]->v1->n_edges; j++){
                if (graph->edges[i]->v1->edges[j] == graph->edges[i])
                    graph->edges[i]->v1->edges[j] = NULL;
            }
            for (int j = 0; j < graph->edges[i]->v2->n_edges; j++){
                if (graph->edges[i]->v2->edges[j] == graph->edges[i])
                    graph->edges[i]->v2->edges[j] = NULL;
            }
            erase_edge(graph->edges[i]);
            graph->edges[i] = NULL;
            cnt += 1;
        }

        int l = 0, k = 0;
        for (; k < graph->n_edge; k++){
            if (graph->edges[k]){
                graph->edges[l] = graph->edges[k];
                //graph->edges[l]->v1 = graph->edges[k]->v1;
                //graph->edges[l]->v2 = graph->edges[k]->v2;
                //graph->edges[l]->size = graph->edges[k]->size;
                l++;
            }
        }
        graph->n_edge -= cnt;
        graph->edges = realloc(graph->edges, sizeof(Edge*) * graph->n_edge);


        // Deleting an edge from matrix
        int pos1 = 0, pos2 = 0;
        for (int j = 0; j < graph->n_vert; j++){
            if (strcmp(graph->desc[i], key1) == 0) pos1 = i;
            if (strcmp(graph->desc[i], key2) == 0) pos2 = i;
        }
        graph->matrix[pos1][pos2] = 0;
        graph->matrix[pos2][pos1] = 0;
    }
}


void change_vertex(Graph* graph, const char* or_key, const char* new_key, int type){
    Vertex *vertex = NULL;
    int pos;
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, or_key) == 0){
            vertex = graph->vertexes[i];
            pos = i;
        }
    }

    free(graph->desc[pos]);
    free(vertex->id);
    vertex->id = strdup(new_key);
    graph->desc[pos] = strdup(new_key);
    vertex->type = type;
}


void change_edge(Graph* graph, const char* key1, const char* key2, int size){
    // Hyper circles are not allowed in this graph
    if (strcmp(key1, key2) == 0) return;

    // Edge weights must be positive
    if (size < 0) return;

    // Checking existence of the vertexes
    for (int i = 0; i < graph->n_edge; i++){
        if (strcmp(graph->edges[i]->v1->id, key1) == 0 && strcmp(graph->edges[i]->v2->id, key2) == 0){
            graph->edges[i]->size = size;
        }
        if (strcmp(graph->edges[i]->v1->id, key2) == 0 && strcmp(graph->edges[i]->v2->id, key1) == 0){
            graph->edges[i]->size = size;
        }
    }

    // Changing the matrix
    int pos1 = -1, pos2 = -1;
    for (int i = 0; i < graph->n_vert; i++){
        if (strcmp(graph->vertexes[i]->id, key1) == 0) {
            pos1 = i;
        }
        if (strcmp(graph->vertexes[i]->id, key2) == 0) {
            pos2 = i;
        }
    }
    graph->matrix[pos1][pos2] = size;
    graph->matrix[pos2][pos1] = size;
}
