#include <stdlib.h>
#include "vertex.h"
#include "string.h"


Vertex* create_vertex(const char* key, int type){
    Vertex* vertex = calloc(1, sizeof(Vertex));
    vertex->id = strdup(key);
    vertex->type = type;
    return vertex;
}


void erase_vertex(Vertex* vertex){
    for (int i = 0; i < vertex->n_edges; i++){
        if (vertex->edges[i] != NULL){
            erase_edge(vertex->edges[i]);
	    vertex->edges[i] = NULL;
	}
    }
    // graph->n_edge -= vertex->n_edges;
    free(vertex->edges);
    free(vertex->id);
    free(vertex);
}
