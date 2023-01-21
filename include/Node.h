#ifndef NODE_H
#define NODE_H


#include <stdbool.h>

#include "TList.h"
#include "THT.h"
#include "TStack.h"

typedef struct {
    int id;
    int degree;
    TList scc_components;
    int *outgoing_edges;
    int num_components;
    bool scc_flag;
    int low;
    int disc;
    bool stackMember;
    int graph_index;
    
} Node;

Node node_create(int id, int degree);
void node_destroy(Node* node);
void makeSupenode(int num_nodes, Node *node, Node* adj, THT* ht);
void util(int num_nodes, Node* adj, THT* ht);


#endif