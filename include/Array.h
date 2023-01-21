#ifndef ARRAY_H
#define ARRAY_H


#include "TInfo.h"



typedef struct {
    TInfo* items; // puntatore agli elementi dell'array
    int length;   // lunghezza array    
    int size;     // dimensione allocata (>= length)
    int num_elem;
} Array;


/* ALGORITMI - VERSIONI PIU' EFFICIENTI */
Array array_create (int length);
void array_destroy (Array *a);
void array_resize (Array *a, int length);

/* FUNZIONI DI UTILITA' */
void array_add (Array *a, TInfo info);
TInfo array_get (Array *a, int pos);
int array_length (Array *a);
void array_set (Array *a, int pos, TInfo info);
void array_print(Array *a);

#endif