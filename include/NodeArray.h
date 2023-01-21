#ifndef NODEARRAY_H
#define NODEARRAY_H


#include <stdbool.h>
#include "Node.h"




typedef struct {
    Node* items; // puntatore agli elementi dell'array
    int length;   // lunghezza array    
    int size;     // dimensione allocata (>= length)
    int num_elem;
} NodeArray;


/* ALGORITMI - VERSIONI PIU' EFFICIENTI */
NodeArray nodeArrayCreate (int length);
void nodeArrayDestroy (NodeArray *a);
void nodeArrayResize (NodeArray *a, int length);

/* FUNZIONI DI UTILITA' */
void nodeArrayAdd (NodeArray *a, Node info);
Node nodeArrayGet (NodeArray *a, int pos);
int nodeArrayLength (NodeArray *a);
void nodeArraySet (NodeArray *a, int pos, Node info);
void nodeArrayPrint(NodeArray *a);
bool nodeArraySearch(NodeArray *a, int nodeId);
void nodeArraySort(NodeArray *a);

#endif