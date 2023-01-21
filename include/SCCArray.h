#ifndef SCCARRAY_H
#define SCCARRAY_H


#include <stdbool.h>
#include "SCCNode.h"




typedef struct {
    SCCNode* items; // puntatore agli elementi dell'array
    int length;   // lunghezza array    
    int size;     // dimensione allocata (>= length)
    int num_elem;
} SCCArray;


/* ALGORITMI - VERSIONI PIU' EFFICIENTI */
SCCArray SCCArrayCreate (int length);
void SCCArrayDestroy (SCCArray *a);
void SCCArrayResize (SCCArray *a, int length);

/* FUNZIONI DI UTILITA' */
void SCCArrayAdd (SCCArray *a, SCCNode info);
SCCNode SCCArrayGet (SCCArray *a, int pos);
int SCCArrayLength (SCCArray *a);
void SCCArraySet (SCCArray *a, int pos, SCCNode info);
void SCCArrayPrint(SCCArray *a);


#endif