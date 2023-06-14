#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

typedef struct Edge{
    struct Vertex* v1;
    struct Vertex* v2;
    int size;
}Edge;


Edge* create_edge(struct Vertex* v1, struct Vertex* v2, int size);

void erase_edge(Edge* edge);


#endif
