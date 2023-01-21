#ifndef GRAFO_H
#define GRAFO_H

#include "Node.h"
#include <stdbool.h>




typedef struct {
    int V,Time;
    Node *adj;
    int max_ID;
    int min_ID;
    int top;
} Graph;

Graph graphCreate(int num_nodes);
void addNode(Graph* g, Node v);
void graphDestroy(Graph* g);
void graphResize(Graph* g, int num_nodes);


#endif