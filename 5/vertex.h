#ifndef VERTEX_H
#define VERTEX_H
#include "edge.h"
#include "graph.h"

typedef struct Vertex{
    int type;
    char* id;
    struct Edge** edges;
    int n_edges;
}Vertex;


Vertex* create_vertex(const char* key, int type);

void erase_vertex(Vertex* vertex);

#endif
