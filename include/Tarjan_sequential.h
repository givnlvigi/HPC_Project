#ifndef TARJAN_SEQUENTIAL
#define TARJAN_SEQUENTAL

#include "Grafo.h"
#include "NodeStack.h"
#include "TList.h"
#include "NodeArray.h"
#include "SCCNode.h"
#include "SCCStack.h"
#include "utils.h"

#include <string.h>

void SCC(Graph* g, SCCStack *sccStack);
void SCCUtil(Graph* g,Node* u,int* low,int* disc, bool *stackMember,NodeStack* st, SCCStack * sccStack);

#endif 