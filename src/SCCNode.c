#include <stdlib.h>
#include <stdio.h>


#include "SCCNode.h"




SCCNode SCCNodeCreate(){
    SCCNode sccNode;
    sccNode.components = nodeArrayCreate(0);
    sccNode.out_degree = 0;
    sccNode.outgoing = listCreate();
    return sccNode;
}

void sccAddNode(SCCNode* sccNode, Node v){
    nodeArrayAdd(&sccNode->components,v);
}

void sccNodeDestroy(SCCNode* sccNode){
    listDestroy(sccNode->outgoing);
    nodeArrayDestroy(&sccNode->components);
}


