#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "edge.h"

typedef struct Graph{
    int n_vert;
    int n_edge;
    int** matrix;
    char** desc;
    struct Vertex** vertexes;
    struct Edge** edges;
}Graph;

Graph* create_graph();

void erase_graph(Graph* graph);

void delete_matrix(Graph* graph);

void print_matrix(Graph* graph);

void add_row_and_coll(Graph* graph);

void add_vertex(Graph* graph, struct Vertex* vertex);

void del_vertex(Graph* graph, const char* key);

void add_edge(Graph* graph, const char* key1, const char* key2, int size);

void del_edge(Graph* graph, const char* key1, const char* key2);

void change_vertex(Graph* graph, const char* or_key, const char* new_key, int type);

void change_edge(Graph* graph, const char* key1, const char* key2, int size);

#endif
