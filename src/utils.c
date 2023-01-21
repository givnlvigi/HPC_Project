#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "Grafo.h"

/**
 * @brief This function generates a random graph (where every node has random degree and adj nodes) of dimension given in input 
 * @param dim   Graph dimensions (number of nodes) 
 * @param output_file  File where to output the graph
 */

void generate_graph(int dim, char* name_output_file, int max_degree, int start_index, int dim_tot_graph){

    FILE* output_file; 
    // strcat(name_output_file, ".bin");

    // printf("%s", name_output_file);

    if (max_degree > dim){
        perror("cannot have nodes with degree > graph_dim!");
        exit(1);
    }

    if ((output_file = fopen(name_output_file, "w")) == NULL){
        perror("error opening file");
        exit(1);
    }

    if ( fseek(output_file, 0, SEEK_SET) != 0){
        perror("Could not move the pointer to the start of the file. Aborting.");
    }

    // fprintf(output_file, "%d", dim);
    fwrite(&dim, sizeof(int), 1, output_file);


    int node_counter = 0; 
    int node_id = 0; 
    int node_index = 0; 
    int degree; 

    srand(time(NULL));  // set the seed


    int* already_node = (int*)malloc(sizeof(int)*dim);

        for (int i = 0; i < dim; i++)
        {
            already_node[i] = 0; 
        }

    int* already_node_index = (int*)malloc(sizeof(int)*dim);

        for (int i = 0; i < dim; i++)
        {
            already_node_index[i] = 0; 
        }

    for (int line = 0; line < dim; line++)
    {
        
        do{
            node_id = rand() % dim + start_index; 
        }while(already_node[node_id - start_index]);
        already_node[node_id - start_index] = 1; 
        // fprintf(output_file, "%d ", node_id);
        fwrite(&node_id, sizeof(int),1,output_file);


        do{
            node_index = rand() % dim + start_index; 
        }while(already_node_index[node_index - start_index]);
        already_node_index[node_index - start_index] = 1; 
        // fprintf(output_file, "%d ", node_index);
        fwrite(&node_index, sizeof(int),1,output_file);


        degree = rand() % max_degree + 1;

        // if (degree != 0)
        // fprintf(output_file, "%d ", degree);
        // else
        // fprintf(output_file, "%d", degree);
        fwrite(&degree, sizeof(int),1,output_file);


        int* already_neighbour = (int*)malloc(sizeof(int)*dim_tot_graph);   // segmentation fault? 

        for (int i = 0; i < max_degree; i++)
        {
            already_neighbour[i] = 0; 
        }

        int neighbour_node;

        for (int neighbour = 0; neighbour < degree; neighbour++)
        {
            do{
                neighbour_node = rand() % dim_tot_graph; 
            }while(already_neighbour[neighbour_node]);  //O(1)

            fwrite(&neighbour_node, sizeof(int), 1, output_file);
            already_neighbour[neighbour_node] = 1; 

            // already_neighbour[neighbour_node] = 1; 

            // if (neighbour == degree-1){
            //     fprintf(output_file, "%d", neighbour_node);

            // }
            // else{
            //     fprintf(output_file, "%d ", neighbour_node);

            // }
        }
        
        free(already_neighbour);

        // if (line != dim-1)
        // fprintf(output_file, "\n");
    }

    free(already_node);
    free(already_node_index);

    printf("file %s generated. Closing it...\n", name_output_file);
    fclose(output_file);

}



/**
 * @brief This function initialize the graph reading from file
 * @param g     Graph to be initialized
 */

void init_from_file(char* input_file, Graph* g){
    int n; 
    FILE* graph_file; 
    if ((graph_file = fopen(input_file, "r")) == NULL){
        perror("error opening file");
        exit(1);
    }

    // measuring file bytes
    if ( fseek(graph_file, 0L, SEEK_END) != 0 ){
        perror("Could not traverse the file. Aborting");
        exit(1);
    }
    long file_size = ftell(graph_file);
    #ifdef DEBUG
    printf("dimension of %s in byte -> %lu\n", input_file, file_size);
    #endif

    if ( fseek(graph_file, 0, SEEK_SET) != 0){
        perror("Could not move the pointer to the start of the file. Aborting.");
    }


    // creating buffer for storing line
    // char* buffer = (char*) malloc(BUFFER_DIM);
    // char buffer[100];
    // if (buffer == NULL){
    //     perror("buffer not created. Aborting.");
    //     exit(1);
    // }
    
    // reading line with fgets
    // fgets(buffer, BUFFER_DIM, graph_file);

    int graph_dim = 0; 

    // input validation with sscanf
    // sscanf(buffer, "%d", &graph_dim);
    // printf("\nsize of buffer: %d", sizeof(buffer));
    fread(&graph_dim, sizeof(int), 1, graph_file);

    #ifdef DEBUG
    printf("Graph dim -> %d\n", graph_dim);
    #endif
    *g = graphCreate(graph_dim);
    
    char *delim = " ";
    char *line; 
    int node_id = 0; 
    int edge = 0;
    int counter = 0; 
    int index = 0; 
    int degree = 0; 
    int edge_counter = 0; 
    Node node; 


    // while (fgets(buffer, BUFFER_DIM, graph_file)){
    //     line = strtok(buffer, delim); // return pointer to the char of the next token
    //     node_id = atoi(line);

    //     line = strtok(NULL, delim);
    //     index = atoi(line);

    //     line = strtok(NULL, delim);
    //     degree = atoi(line);

    //     printf("node_id: %d, index: %d, degree: %d", node_id, index, degree);

    //     node = node_create(node_id, degree);

    //     printf(", edges: ");
    //     edge_counter = 0; 
    //     while ( line = strtok(NULL, delim)){
    //         int edge = atoi(line);
    //         node.outgoing_edges[edge_counter] = edge; 
    //         edge_counter++; 
    //         printf("%d ", edge);
    //     }
    //     addNode(g, node, index);
    //     printf("\n");
    // }

    for (int i = 0; i < graph_dim; i++)
    {
        fread(&node_id, sizeof(int), 1, graph_file);
        #ifdef DEBUG
        printf("id: %d ", node_id);
        #endif

        fread(&index, sizeof(int), 1, graph_file);
        #ifdef DEBUG
        printf("index: %d ", index);
        #endif

        fread(&degree, sizeof(int), 1, graph_file);
        #ifdef DEBUG
        printf("degree: %d ", degree);
        #endif

        node = node_create(node_id, degree);

        edge_counter = 0; 
        #ifdef DEBUG
        printf(" --->");
        #endif
        for (int neighbour = 0; neighbour < degree; neighbour++)
        {
            fread(&edge, sizeof(int), 1, graph_file);
            #ifdef DEBUG
            printf("%d ", edge);
            #endif
            node.outgoing_edges[edge_counter] = edge; 
            edge_counter++; 
        }
        addNode(g, node);
        #ifdef DEBUG
        printf("\n");
        #endif
    }
    
    

    #ifdef DEBUG
    if (feof(graph_file)){
        printf("reached end-of-file\n");
    }

    if (ferror(graph_file)){
        fprintf(stderr, "an error occurred while reading the file");
    }
    #endif 

    // free(buffer);
    
    fclose(graph_file);
}

void set_all_outgoing_edges(Node* node){
    for (int i = 0; i < 10; i++)
    {
        node->outgoing_edges[i] = i; 
    }
}

void create_all_connected_graph(Graph* g){
    Node node0 = node_create(0,10);
    Node node1 = node_create(1,10);
    Node node2 = node_create(2,10);
    Node node3 = node_create(3,10);
    Node node4 = node_create(4,10);
    Node node5 = node_create(5,10);
    Node node6 = node_create(6,10);
    Node node7 = node_create(7,10);
    Node node8 = node_create(8,10);
    Node node9 = node_create(9,10);

    set_all_outgoing_edges(&node0);
    set_all_outgoing_edges(&node1);
    set_all_outgoing_edges(&node2);
    set_all_outgoing_edges(&node3);
    set_all_outgoing_edges(&node4);
    set_all_outgoing_edges(&node5);
    set_all_outgoing_edges(&node6);
    set_all_outgoing_edges(&node7);
    set_all_outgoing_edges(&node8);
    set_all_outgoing_edges(&node9);

    addNode(g, node0);
    addNode(g, node1);
    addNode(g, node2);
    addNode(g, node3);
    addNode(g, node4);
    addNode(g, node5);
    addNode(g, node6);
    addNode(g, node7);
    addNode(g, node8);
    addNode(g, node9);

}

void create_Graph_from_data(Graph* graph, int dim, int* ids, int* indexes, int* degrees, int* neighours){

    // int offset = 0; 
    // *graph = graphCreate(dim);

    // Node* nodes = (Node*)malloc(sizeof(Node)*dim);

    // for (int i = 0; i < dim; i++)
    // {
    //     *nodes = node_create(ids[i], degrees[i]);

    //     for (int j = 0; j < degrees[i]; j++)
    //     {
    //         (*nodes).outgoing_edges[j] = neighours[j + offset];
            
    //     }

    //     offset = offset + degrees[i];

    //     addNode(graph, *nodes, indexes[i]);
    //     nodes++; 
        
    // } 

}


