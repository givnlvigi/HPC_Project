#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Grafo.h"
#include "NodeStack.h"
#include "TList.h"
#include "NodeArray.h"
#include "SCCNode.h"
#include "SCCStack.h"
#include "Utils.h"


void updateEdges(Graph * g, int id, int new_id){
    for(int i = 0; i < g->V; i++){
        for(int j = 0; j < g->adj[i].degree; j++){
            if( g->adj[i].outgoing_edges[j] == id &&  g->adj[i].outgoing_edges[j] != new_id){
                 g->adj[i].outgoing_edges[j] = new_id;
            }
        }
    }
}

void makeSupernode(Graph* g, int *a){
    int n, num_scc,num_nodes, num_edges;
    n = a[0];
    num_scc = a[1];

    for(int i = 2; i < n; i++){                       
        int num_elem_scc = a[i++];                        
        int degree = a[i++];   
        int id = a[i];
        Node new_node = node_create(id, degree);

        int index = i + num_elem_scc ;
        //new_node.num_components = num_elem_scc;

        
        new_node.num_components=num_elem_scc;
        if(num_elem_scc > 1)
            new_node.scc_flag = true;
        for(i; i < index && i < n; i++){              

            new_node.scc_components = listInsert(new_node.scc_components, infoListCreate(a[i],0));
            //new_node.num_components++;
            updateEdges(g,a[i], id);
            
        }

        index = i+degree;

        int c = 0;
        for(i; i < index && i < n; i++){        
            new_node.outgoing_edges[c++] = a[i];
        }
        new_node.graph_index = g->top;

        addNode(g, new_node);
        // addNode(g, new_node, g->top);

        i--;
    }


}

int main(){
    Graph g = graphCreate(10);
    int a[32] = {32, 6, 4, 2, 0, 1, 2, 3, 4, 6, 1, 0, 11, 1, 0, 10, 3, 3, 4, 5, 6, 7, 8, 9, 1, 1, 7, 9, 2, 0, 8, 9};
    
    makeSupernode(&g,a);

    for(int i = 0; i < g.V; i++){
        printf("%d ---->", g.adj[i].id);
        for(int j = 0; j < g.adj[i].degree; j++){
            printf("%d  ", g.adj[i].outgoing_edges[j]);
        }
        printf("\n");
    }
}