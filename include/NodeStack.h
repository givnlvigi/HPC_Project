/*
 * TStack: implementazione di uno stack attraverso un array dinamico
 */

#ifndef NODESTACK_H
#define NODESTACK_H


#include "NodeArray.h"

typedef struct {
    NodeArray a;
} NodeStack;

NodeStack nodeStackCreate(void);
void nodeStackDestroy(NodeStack *s);
void nodeStackPush(NodeStack *s, Node x);
Node nodeStackPop(NodeStack *s);
Node nodeStackTop(NodeStack *s);
int nodeStackIsEmpty(NodeStack *s);

#endif