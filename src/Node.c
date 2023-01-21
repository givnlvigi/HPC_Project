#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Node.h"






Node node_create(int id, int degree){
    Node node;
    node.degree = degree;
    node.id = id;
    node.num_components = 0;
    node.scc_components = listCreate(0);
    node.outgoing_edges = malloc(sizeof(int) * degree);
    node.scc_flag =  false;
    node.stackMember = false;
    node.disc = -1;
    node.low = -1;
    return node;
}

// void makeSupenode(int num_nodes, Node *node, Node* adj, THT* ht){
//     node->scc_flag = true;
//     THLNode* list = node->scc_components;
//     while(list != NULL){
//         //Scorro tutta la lista dei componenti dell'SCC
//         int id = list->info.key;
//         list = list->link;

//         for(int i = 0; i< num_nodes; i++){
//             int *rename_id = HTsearch(ht, id);
//             TInfoList info = infoListCreate(id,0);
//             THLNode *search_node = listSearch(node->scc_components,info);
//             if(id != (*rename_id)){ // se il nodo non appartiene all'scc
//                 // aggiorno lista adiacenza
//                 for(int j=0; j<adj[i].degree;j++){
//                             //TInfoList infoID = infoListCreate((*new_id),0);
//                         //THLNode * scc_member = listSearch(node->scc_components,infoID);
//                     if(adj[i].outgoing_edges[j] == id){
//                         int *new_id = HTsearch(ht, id);
//                         //TInfoList infoID = infoListCreate((*new_id),0);
//                         //THLNode * scc_member = listSearch(node->scc_components,infoID);
//                         //if(scc_member == NULL){
//                         adj[i].outgoing_edges[j] = (*new_id);
//                         //}
                        
//                     }
//                 }
//             }// per ogni nodo del grafo vedo se il nodo corrente appartiene ad un scc
            // else{
                 // scorro tutti gli archi uscenti da quel nodo che appartiene all'scc
                // int l;
                // for(int k=0; k<adj[i].degree;k++){
                //     int *edge_id = HTsearch(ht, adj[i].outgoing_edges[k]);
                //     if(edge_id == NULL){
                //          int prova = adj[i].outgoing_edges[k];
                //         edge_id = &prova;
                //     }

                    
                //     if(*rename_id == *edge_id){
                //         adj[i].outgoing_edges[k] = adj[i].outgoing_edges[adj[i].degree - 1];
                //         adj[i].outgoing_edges[adj[i].degree - 1] = NULL; // metto l'id di quel nodo in ultima posizione
                       
                //         adj[i].degree -= 1; // decremento il degree in maniera tale che nei cicli for non arriverò all'ultima  posizione dove si trova il nodo "eliminato"                        
                //     }
                //     l = k ;
                    // TInfoList info = infoListCreate(*edge_id,0);
                    // // elimino gli archi uscenti dai nodi dell'scc aventi come destinazione altri nodi appartenenti all'scc stesso
                    // THLNode *search_node = listSearch(node->scc_components,info);
                    // if(search_node != NULL){
                    //     adj[i].outgoing_edges[k] = adj[i].outgoing_edges[adj[i].degree - 1];
                    //     adj[i].outgoing_edges[adj[i].degree - 1] = NULL; // metto l'id di quel nodo in ultima posizione
                       
                    //     adj[i].degree -= 1; // decremento il degree in maniera tale che nei cicli for non arriverò all'ultima  posizione dove si trova il nodo "eliminato"
                    // }
               // }
                // if(adj[i].degree == 1){
                //     if(rename_id == edge_id){
                //         adj[i].outgoing_edges[k] = adj[i].outgoing_edges[adj[i].degree - 1];
                //         adj[i].outgoing_edges[adj[i].degree - 1] = NULL; // metto l'id di quel nodo in ultima posizione
                       
                //         adj[i].degree -= 1; // decremento il degree in maniera tale che nei cicli for non arriverò all'ultima  posizione dove si trova il nodo "eliminato"                        
                //     }                    
                // }
                
//            }
//         }
//     }

//     util(num_nodes,adj,ht);


// }



// void util(int num_nodes, Node* adj, THT* ht){
//     TStack new_adj = stackCreate();
    
//     for(int i = 0; i<num_nodes; i++){
//         int top = 0;
        
//         int *id = &adj[i].id;
//         if(HTsearch(ht, adj[i].id) != NULL){
//             *id = HTsearch(ht,(*id));
//             printf("ht search   :%d\n", *id);
//         }else{
//             printf(" normale :     %d\n", *id);
//         }
        
//         for(int j = 0; j<adj[i].degree; j++){
//             //printf("%d         %d\n",adj[i].id, adj[i].outgoing_edges[j]);
//             TKey prova = adj[i].outgoing_edges[j];
//             int *edge_id = &adj[i].outgoing_edges[j];
//             if(HTsearch(ht, prova) != NULL){
//                 *edge_id =  HTsearch(ht, prova);
//             }
//             //printf("%d         %d\n",adj[i].id,*edge_id);
            


//             if((*id) != (*edge_id)){
//                 stackPush(&new_adj,adj[i].outgoing_edges[j]);
//             }
//         }
//         for( int j=0; i< new_adj.a.length; j++)
//             adj[i].outgoing_edges[j] = stackPop(&new_adj);
        
//     }

// }

// void makeSupenode2(int num_nodes, Node *node, Node* adj, THT* ht){
//     node->scc_flag = true;
//     THLNode* list = node->scc_components;
//     while(list != NULL){
//         //Scorro tutta la lista dei componenti dell'SCC
//         int id = list->info.key;
//         list = list->link;

//         for(int i = 0; i< num_nodes; i++){
//             int *rename_id = HTsearch(ht, id);
//             TInfoList info = infoListCreate(id,0);
//             THLNode *search_node = listSearch(node->scc_components,info);
//             if(id != (*rename_id)){ // se il nodo non appartiene all'scc
//                 // aggiorno lista adiacenza
//                 for(int j=0; j<adj[i].degree;j++){
//                             //TInfoList infoID = infoListCreate((*new_id),0);
//                         //THLNode * scc_member = listSearch(node->scc_components,infoID);
//                     if(adj[i].outgoing_edges[j] == id){
//                         int *new_id = HTsearch(ht, id);
//                         //TInfoList infoID = infoListCreate((*new_id),0);
//                         //THLNode * scc_member = listSearch(node->scc_components,infoID);
//                         //if(scc_member == NULL){
//                         adj[i].outgoing_edges[j] = (*new_id);
//                         //}
                        
//                     }
//                 }
//             }// per ogni nodo del grafo vedo se il nodo corrente appartiene ad un scc
//              else{
//                  // scorro tutti gli archi uscenti da quel nodo che appartiene all'scc
//                  for(int k=0; k<adj[i].degree;k++){
//                     int *edge_id = HTsearch(ht, adj[i].outgoing_edges[k]);
//                     if(edge_id == NULL){
//                          int prova = adj[i].outgoing_edges[k];
//                         edge_id = &prova;
//                     }
//                     TInfoList info = infoListCreate(*edge_id,0);
//                     // elimino gli archi uscenti dai nodi dell'scc aventi come destinazione altri nodi appartenenti all'scc stesso
//                     THLNode *search_node = listSearch(node->scc_components,info);
//                     if(search_node != NULL){
//                         adj[i].outgoing_edges[k] = adj[i].outgoing_edges[adj[i].degree - 1];
//                         adj[i].outgoing_edges[adj[i].degree - 1] = NULL; // metto l'id di quel nodo in ultima posizione
                       
//                         adj[i].degree -= 1; // decremento il degree in maniera tale che nei cicli for non arriverò all'ultima  posizione dove si trova il nodo "eliminato"
//                     }
//                 }
                
//             }
//         }
//     }


// }




TList addNodeToSCC(TList scc_components, TInfoList nodeToAdd){
    scc_components = listInsert(scc_components,nodeToAdd);
}

void node_destroy(Node *node){
    free(node->outgoing_edges);
}



// Graph* makeSupernode(int *a, int *top){
//     Graph *g;
//     int n, num_scc,num_nodes, num_edges,id=0, outgoing_index=0;
//     n = a[0];
//     num_scc = a[1];
//     num_nodes = a[2];
//     num_edges = a[3];
//     g->V = num_scc;
//     int index = num_edges+num_nodes;
//     for(int i = 4; i < n; i + index){
//         int j = index;
//         index = num_nodes=a[i] + a[i+1];
//         int id, degree, num_components;
//         degree = a[j];
//         num_components = a[j+1];
//         Node new_node = node_create(id,degree);
//         new_node.num_components = num_components;
//         if(num_components>1)
//             new_node.scc_flag = true;
            
            

//         j += 2;
//         for(j; j < index; j++){
//             new_node.graph_index = *top;
//             new_node.scc_components = listInsert(new_node.scc_components,infoListCreate(a[j],0));
//             new_node.id = new_node.scc_components->info.key;
//             addNode(g,new_node,*top);
//             (*top)++;
            
//         }
//         j++;
//         for(j; j < degree; j++){
//             new_node.outgoing_edges[outgoing_index] = a[j];
//             outgoing_index++;
//         }
//         outgoing_index = 0;
        
//     }
//     return g;
// }
