#ifndef TARRAY_H
#define TARRAY_H


#include <stdbool.h>
#include "TInfo.h"




typedef struct {
    TInfo* items; // puntatore agli elementi dell'array
    int length;   // lunghezza array    
    int size;     // dimensione allocata (>= length)
    int num_elem;
} TArray;


/* ALGORITMI - VERSIONI PIU' EFFICIENTI */
TArray arrayCreate (int length);
void arrayDestroy (TArray *a);
void arrayResize (TArray *a, int length);

/* FUNZIONI DI UTILITA' */
void arrayAdd (TArray *a, TInfo info);
TInfo arrayGet (TArray *a, int pos);
int arrayLength (TArray *a);
void arraySet (TArray *a, int pos, TInfo info);
void arrayPrint(TArray *a);

#endif