#include <stdlib.h>
#include "edge.h"


Edge* create_edge(struct Vertex* v1, struct Vertex* v2, int size){
    Edge* edge = calloc(1, sizeof(Edge));
    edge->size = size;
    edge->v1 = v1;
    edge->v2 = v2;
    return edge;
}


void erase_edge(Edge* edge){
    edge->v1 = NULL;
    edge->v2 = NULL;
    free(edge);
}
