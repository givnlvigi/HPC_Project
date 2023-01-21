#include <stdio.h>
#include <stdlib.h> // definisce la funzione malloc
#include <assert.h> // definisce la funzione assert
#include "Array.h"

#define C_EXP 10000  // costante di espansione
#define C_RED 20000 // costante di riduzione




Array array_create (int length) {
    Array a;
    int size = length + C_EXP;
    a.items = malloc(size * sizeof(TInfo));
    assert (size == 0 || a.items != NULL); 
    a.length = length;
    a.size = size; 
    a.num_elem = 0;
    //printf ("Creazione array: length = %d, size = %d\n", length, size);
    return a;
}


void array_destroy (Array *a) {
    free(a->items);
    a->items = NULL;
    a->length = a->size = 0;
    //printf ("Distruzione array\n");
}

void array_resize (Array *a, int length) {
    if (length > a->size || length < a->size - C_RED) {
        int size = length + C_EXP;
        
        a->items = realloc(a->items, size * sizeof(TInfo));
        assert (size == 0 || a->items != NULL); 
        a->size = size;   
    }
    a->length = length;
    //printf ("Ridimensionamento array: length = %d, size = %d\n", length, a->size);
 }

/* FUNZIONI DI UTILITA' */

// Aggiunta di un elemento in coda all'array
void array_add (Array *a, TInfo info) {
    array_resize(a, a->length + 1);
    a->items[a->length - 1] = info;
    a->num_elem += 1;
}

// Lettura di un elemento in posizione pos
TInfo array_get (Array *a, int pos) {
    return a->items[pos];
}

// Lettura della lunghezza dell'array
int array_length (Array *a) {
    return a->length;
}

// Inserimento di un elemento in posizione pos con ridimensionamento automatico
void array_set (Array *a, int pos, TInfo info) {
    if (pos >= a->length)
        array_resize(a, pos + 1);
    a->items[pos] = info;
}

// Stampa dell'array
void array_print(Array *a) {
    for (int i = 0; i < a->length; ++i)
        printf ("%d ", a->items[i]);
    printf ("\n");
}