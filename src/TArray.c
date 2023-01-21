#include <stdio.h>
#include <stdlib.h> // definisce la funzione malloc
#include <assert.h> // definisce la funzione assert
#include "TArray.h"

#define C_EXP 1000  // costante di espansione
#define C_RED 2000 // costante di riduzione


TArray arrayCreate (int length) {
    TArray a;
    int size = length + C_EXP;
    a.items = malloc(size * sizeof(TInfo));
    assert (size == 0 || a.items != NULL); 
    a.length = length;
    a.size = size; 

    return a;
}

void arrayDestroy (TArray *a) {
    free(a->items);
    a->items = NULL;
    a->length = a->size = 0;

}

void arrayResize (TArray *a, int length) {
    if (length > a->size || length < a->size - C_RED) {
        int size = length + C_EXP;
        a->items = realloc(a->items, size * sizeof(TInfo));
        assert (size == 0 || a->items != NULL); 
        a->size = size;        
    }
    a->length = length;

 }

/* FUNZIONI DI UTILITA' */

// Aggiunta di un elemento in coda all'array
void arrayAdd (TArray *a, TInfo info) {
    arrayResize(a, a->length + 1);
    a->items[a->length - 1] = info;
}

// Lettura di un elemento in posizione pos
TInfo arrayGet (TArray *a, int pos) {
    return a->items[pos];
}

// Lettura della lunghezza dell'array
int arrayLength (TArray *a) {
    return a->length;
}

// Inserimento di un elemento in posizione pos con ridimensionamento automatico
void arraySet (TArray *a, int pos, TInfo info) {
    if (pos >= a->length)
        arrayResize(a, pos + 1);
    a->items[pos] = info;
}

// Stampa dell'array
void arrayPrint(TArray *a) {
    for (int i = 0; i < a->length; ++i)
        printf ("%d   ", a->items[i]);
    printf ("\n");
}