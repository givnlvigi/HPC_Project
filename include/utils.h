#ifndef UTILS_H
#define UTILS_H

#include "Grafo.h"

void generate_graph(int dim, char* name_output_file, int max_degree, int start_index, int dim_tot_graph);
void init_from_file(char* input_file, Graph* g);
void create_all_connected_graph(Graph* g);
void set_all_outgoing_edges(Node* node);
void create_Graph_from_data(Graph* graph, int dim, int* ids, int* indexes, int* degrees, int* neighours);

#endif