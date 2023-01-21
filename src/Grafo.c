#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Grafo.h"
#include "THT.h"

#define C_EXP 100000

Graph graphCreate(int num_nodes){
    Graph g;
    g.V = num_nodes;
    g.Time = 0;
    g.adj = malloc(sizeof(Node) * (num_nodes+C_EXP));
    g.max_ID = -1;
    g.min_ID = 9999999;
    g.top = 0;
    return g;
}

void addNode(Graph* g, Node v){
    graphResize(g, g->top);
    v.graph_index = g->top;
    g->adj[g->top] = v;
    g->top++;
    if (v.id > g->max_ID)
        g->max_ID = v.id;
    if(v.id < g->min_ID)
        g->min_ID = v.id;
}

void graphDestroy(Graph *g){
    free(g->adj);
}

void graphResize(Graph* g, int num_nodes){
    
    if(num_nodes > g->V+C_EXP)
        g->adj = realloc(g->adj, sizeof(Node) * num_nodes);
    g->V = num_nodes + 1;
}

void graphPrint(Graph* g){
    printf("Info about this graph:\n");
    printf("minID: %d\t", g->min_ID);
    printf("maxID: %d\t", g->max_ID);
    printf("top: %d\t", g->top);
    printf("V: %d\n", g->V);
    printf("Printing graph structure...\n");
    for(int i=0; i<g->V;i++){
        printf("%d -----> ", g->adj[i].id);
        for(int j=0; j<g->adj[i].degree;j++){
            printf("%d  ",g->adj[i].outgoing_edges[j]);
        }
        printf("\n");
    }
    
}


