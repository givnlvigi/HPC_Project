/*
 * TStack: implementazione di uno stack attraverso un nodeArray dinamico
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "NodeStack.h"

NodeStack nodeStackCreate(void) {
    NodeStack s;
    s.a = nodeArrayCreate(0);
    return s;
}

void nodeStackDestroy(NodeStack *s) {
    nodeArrayDestroy(&s->a);
}

void nodeStackPush(NodeStack *s, Node x) {
    nodeArrayResize(&s->a, s->a.length+1);
    s->a.items[s->a.length-1] = x;
}

Node nodeStackPop(NodeStack *s) {
    Node x = s->a.items[s->a.length-1];
    nodeArrayResize(&s->a, s->a.length-1);
    return x;
}

Node nodeStackTop(NodeStack *s) {
    return s->a.items[s->a.length-1];
}

int nodeStackIsEmpty(NodeStack *s) {
    return s->a.length == 0;
}
