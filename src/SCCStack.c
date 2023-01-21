/*
 * TStack: implementazione di uno stack attraverso un nodeArray dinamico
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SCCStack.h"

SCCStack SCCStackCreate(void) {
    SCCStack s;
    s.a = SCCArrayCreate(0);
    return s;
}

void SCCStackDestroy(SCCStack *s) {
    SCCArrayDestroy(&s->a);
}

void SCCStackPush(SCCStack *s, SCCNode x) {
    SCCArrayResize(&s->a, s->a.length+1);
    s->a.items[s->a.length-1] = x;
}

SCCNode SCCStackPop(SCCStack *s) {
    SCCNode x = s->a.items[s->a.length-1];
    SCCArrayResize(&s->a, s->a.length-1);
    return x;
}

SCCNode SCCStackTop(SCCStack *s) {
    return s->a.items[s->a.length-1];
}

int SCCStackIsEmpty(SCCStack *s) {
    return s->a.length == 0;
}
