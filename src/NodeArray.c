#include <stdio.h>
#include <stdlib.h> // definisce la funzione malloc
#include <assert.h> // definisce la funzione assert
#include "NodeArray.h"

#define C_EXP 10000 // costante di espansione
#define C_RED 20000 // costante di riduzione


NodeArray nodeArrayCreate (int length) {
    NodeArray a;
    int size = length + C_EXP;
    a.items = malloc(size * sizeof(Node));
    assert (size == 0 || a.items != NULL); 
    a.length = length;
    a.size = size; 

    return a;
}

void nodeArrayDestroy (NodeArray *a) {
    free(a->items);
    a->items = NULL;
    a->length = a->size = 0;

}

void nodeArrayResize (NodeArray *a, int length) {
    if (length > a->size || length < a->size - C_RED) {
        int size = length + C_EXP;
        a->items = realloc(a->items, size * sizeof(Node));
        assert (size == 0 || a->items != NULL); 
        a->size = size;        
    }
    a->length = length;

 }

/* FUNZIONI DI UTILITA' */

// Aggiunta di un elemento in coda all'array
void nodeArrayAdd (NodeArray *a, Node info) {
    nodeArrayResize(a, a->length + 1);
    a->items[a->length - 1] = info;
}

// Lettura di un elemento in posizione pos
Node nodeArrayGet (NodeArray *a, int pos) {
    return a->items[pos];
}

// Lettura della lunghezza dell'array
int nodeArrayLength (NodeArray *a) {
    return a->length;
}

// Inserimento di un elemento in posizione pos con ridimensionamento automatico
void nodeArraySet (NodeArray *a, int pos, Node info) {
    if (pos >= a->length)
        nodeArrayResize(a, pos + 1);
    a->items[pos] = info;
}

// Stampa dell'array
void nodeArrayPrint(NodeArray *a) {
    for (int i = 0; i < a->length; ++i)
        printf ("%d   ", a->items[i].id);
    printf ("\n");
}

bool nodeGreater(Node node1, Node node2){
    if(node1.id > node2.id)
        return true;
    return false;
}

bool nodeLess(Node node1, Node node2){
    if(node1.id > node2.id)
        return false;
    return true;
}

bool nodeEqual(Node node1, Node node2){
    if(node1.id == node2.id)
        return true;
    return false;
}

void nodeArraySort(NodeArray *a)
{
    int i, j;
    Node key;
    for (i = 1; i < a->length; i++)
    {
        key = a->items[i];
        j = i - 1;

        while (j >= 0 && nodeGreater(a->items[j], key))
        {
            a->items[j + 1] = a->items[j];
            j = j - 1;
        }
        a->items[j + 1] = key;
    }
}

bool nodeArraySearch(NodeArray *a, int nodeId)
{
    nodeArraySort(a);
    Node node = node_create(nodeId, 0);
    int low = 0;
    int high = a->length - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (nodeEqual(a->items[mid], node))
        {
            node_destroy(&node);
            return true;
        }

        if (nodeLess(a->items[mid], node))
            low = mid + 1;
        else
            high = mid - 1;
    }
    node_destroy(&node);
    return false;
}