#ifndef ALGO_H
#define ALGO_H
#include "graph.h"

typedef struct Queue{
    Edge** arr;
    int size;
}Queue;


Queue* create_queue();

void delete_queue(Queue* queue);

void add_queue(Queue* queue, Edge * v);

Edge * rem_queue(Queue* queue);

void dfs(Graph* graph, char* key);

int __dfs(Graph* graph, int** visited, int v);

void BellmanFord(Graph* graph, char* key);

void skeleton(Graph* graph);

#endif
