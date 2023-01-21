#include "TList.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* 
 * Operazioni su THLNode e TList
 */

THLNode *nodeCreate(TInfoList info) {
    THLNode *new = malloc (sizeof(THLNode));
    if (new != NULL) {
        new->info = info;
        new->link = NULL;
    }
    return new;
}

void nodeDestroy(THLNode *node) {
    free (node);
}

TList listCreate() {
    return NULL;
}

TList listDestroy(TList list) {
    THLNode *node;
    while (list != NULL) {
        node = list;
        list = list->link;
        nodeDestroy(node);
    }
    return list;
}

TList listInsert(TList l, TInfoList info) {
    if (l == NULL || infoListGreater(l->info, info)) {
        THLNode *node = nodeCreate(info);
        assert (node != NULL);
        node->link = l;
        return node;
    }
    TList m = listInsert(l->link, info);
    l->link = m;
    return l;
}

THLNode *listSearch(TList list, TInfoList info) {
    THLNode *node = list;
    while (node != NULL && infoListGreater(info, node->info))
        node = node->link;
    if (node != NULL && !infoListEqual(info,node->info)) 
	    node = NULL;
    return node;
}

TList listDelete(TList list, TInfoList info) {
    THLNode *prec = NULL, *node = list;
    while (node != NULL && infoListGreater(info, node->info)) {
        prec = node;
        node = node->link;
    }
    if (node != NULL && infoListEqual(info, node->info)) {
        if (prec == NULL) 
            list = node->link;
        else
            prec->link = node->link;
        nodeDestroy(node);
    }
    return list;
}

void listPrint(TList list) {
    THLNode *node = list;
    while (node != NULL) {
        infoListPrint (node->info);
        
        node = node->link;
    }

    printf("\n");
}
