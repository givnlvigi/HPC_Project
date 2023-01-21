/*
 * TStack: implementazione di uno stack attraverso un array dinamico
 */

#ifndef SCCSTACK_H
#define SCCSTACK_H


#include "SCCArray.h"
#include "SCCNode.h"

typedef struct {
    SCCArray a;
} SCCStack;

SCCStack SCCStackCreate(void);
void SCCStackDestroy(SCCStack *s);
void SCCStackPush(SCCStack *s, SCCNode x);
SCCNode SCCStackPop(SCCStack *s);
SCCNode SCCStackTop(SCCStack *s);
int SCCStackIsEmpty(SCCStack *s);

#endif