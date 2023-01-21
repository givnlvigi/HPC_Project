#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Tarjan.h"

void SCC(Graph* g, SCCStack *sccStack){
    int size = g->V;                                // numero di nodi del grafo

    NodeStack st = nodeStackCreate();

    for(int i = 0; i < size; i++){
        if (g->adj[i].disc == -1)
        {
            SCCUtil(g,&(g->adj[i]),&g->adj[i].low,&g->adj[i].disc,&g->adj[i].stackMember,&st, sccStack);
        }
    }
}

void SCCUtil(Graph* g, Node* u,int* low,int* disc, bool* stackMember,NodeStack* st, SCCStack *sccStack){
    (*disc)= g->Time;
    (*low) = g->Time;
    g->Time +=1;
    int found = 0;
    //THT *ht = HTcreate(1);
    (*stackMember) = true;                         // index array per controllare velocemente se un nodo è presente nello stack
    nodeStackPush(st, *u);
    int index = -1;

    int n;

    for(int i = 0; i < u->degree; i++){
        // find V successor
        n = u->outgoing_edges[i];
        // finding neighbour in the adj list. outgoing_edges is a list of int, we need to find the index of the corresponding Node in g->adj
        for(int j=0; j<g->V;j++){
            if(g->adj[j].id == n){
                index = j;
                found = 1;
                break;
            }
        }

        // if w.index is undefined
        if(index != -1 && g->adj[index].disc == -1 && found == 1){

            // successor has not been visited. Recurse on it 
            SCCUtil(g,&(g->adj[index]),&g->adj[index].low,&g->adj[index].disc,&g->adj[index].stackMember,st, sccStack);
            u->low = (u->low <= g->adj[index].low)? u->low : g->adj[index].low;

        } else if( g->adj[index].stackMember == true && found == 1){ // else if w.OnStack 

            u->low = (u->low <= g->adj[index].disc)? u->low : g->adj[index].disc;
            // printf("I'm %d: my low: %d\n", u->id, u->low);

        }

        found = 0;
    }

    Node w = node_create(-1,0);
    
    if(u->low == u->disc){
        SCCNode supernode = SCCNodeCreate();
        // printf("-----created supernode!\n");
        while(w.id != u->id){
            w = nodeStackPop(st);
            // printf("popped: %d\n", w.id);

            g->adj[w.graph_index].stackMember = false; 
            nodeArrayAdd(&supernode.components, w); 

        }
        nodeArraySort(&supernode.components);
        
        // tutti gli archi uscenti di tutti i nodi che compongono l'SCC vengono salvati come outgoing del supernode
        for (int k = 0; k < supernode.components.length; k++){
            for (int j = 0; j < supernode.components.items[k].degree; j++)
                if(!nodeArraySearch(&supernode.components,supernode.components.items[k].outgoing_edges[j])){
                    TInfoList dest = infoListCreate(supernode.components.items[k].outgoing_edges[j],0);
                    supernode.outgoing = listInsert(supernode.outgoing, dest);
                    supernode.out_degree += 1;
                }
        }
        SCCStackPush(sccStack, supernode);
    }
}


