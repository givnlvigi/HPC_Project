#ifndef SCCNODE_H
#define SCCNODE_H

#include "NodeArray.h"
#include <stdbool.h>




typedef struct {
    TList outgoing;
    NodeArray components;
    int out_degree;
} SCCNode;

SCCNode SCCNodeCreate();
void sccAddNode(SCCNode* sccNode, Node v);
void sccNodeDestroy(SCCNode* sccNode);


#endif