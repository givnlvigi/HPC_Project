#include <stdio.h>
#include <stdlib.h> // definisce la funzione malloc
#include <assert.h> // definisce la funzione assert
#include "SCCArray.h"

#define C_EXP 10000  // costante di espansione
#define C_RED 20000 // costante di riduzione


SCCArray SCCArrayCreate (int length) {
    SCCArray a;
    int size = length + C_EXP;
    a.items = malloc(size * sizeof(SCCNode));
    assert (size == 0 || a.items != NULL); 
    a.length = length;
    a.size = size; 

    return a;
}

void SCCArrayDestroy (SCCArray *a) {
    free(a->items);
    a->items = NULL;
    a->length = a->size = 0;

}

void SCCArrayResize (SCCArray *a, int length) {
    if (length > a->size || length < a->size - C_RED) {
        int size = length + C_EXP;
        a->items = realloc(a->items, size * sizeof(SCCNode));
        assert (size == 0 || a->items != NULL); 
        a->size = size;        
    }
    a->length = length;

 }

/* FUNZIONI DI UTILITA' */

// Aggiunta di un elemento in coda all'array
void SCCArrayAdd (SCCArray *a, SCCNode info) {
    SCCArrayResize(a, a->length + 1);
    a->items[a->length - 1] = info;
}

// Lettura di un elemento in posizione pos
SCCNode SCCArrayGet (SCCArray *a, int pos) {
    return a->items[pos];
}

// Lettura della lunghezza dell'array
int SCCArrayLength (SCCArray *a) {
    return a->length;
}

// Inserimento di un elemento in posizione pos con ridimensionamento automatico
void SCCArraySet (SCCArray *a, int pos, SCCNode info) {
    if (pos >= a->length)
        SCCArrayResize(a, pos + 1);
    a->items[pos] = info;
}

// Stampa dell'array
void SCCArrayPrint(SCCArray *a) {
    for (int i = 0; i < a->length; ++i){
        nodeArrayPrint(&a->items[i].components);

    }
    printf ("\n");
}

