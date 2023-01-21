/*
 * TList: Lista
 */

#ifndef TLIST_H
#define TLIST_H

#include "TInfoList.h"
typedef struct SHLNode THLNode;

struct SHLNode {
    TInfoList info;
    THLNode *link;
};

typedef THLNode* TList;

TList listCreate();
TList listDestroy(TList);
TList listInsert(TList, TInfoList);
THLNode *listSearch(TList, TInfoList);
TList listDelete(TList, TInfoList);
void listPrint(TList);


#endif /* TLIST_H */


