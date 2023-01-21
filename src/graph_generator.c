#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// #define NUM_NODES 100
// #define NUM_FILE 4


int main(int argc, char *argv[])
{

    if (argc != 3){
        fprintf(stderr, "Usage:\n\t%s [n_nodes] [n_threads]", argv[0]);
        exit(EXIT_FAILURE);
    }

    int size = atoi(argv[1]);
    int n_threads = atoi(argv[2]);
    int max_edges = 20;

    char filename[300];

    // printf("%s\t%s\t\t\t%s\t%s\t%s\n", "psize", "file", "deg", "offset", "size");

    if (n_threads == 0){
        sprintf(filename, "SIZE%d-SEQ-INPUT", size);
        // printf("%s\n", filename);
        generate_graph(size, filename, max_edges, 0, size);
        printf("Created file: %s, n_nodes: %d, max_edges: %d, start_id:%d, total_graph_nodes:%d\n", filename, size, max_edges, 0, size);
        // printf("%d\t%s\t%d\t%d\t%d\n", size, filename, max_edges, 0, size);
        // printf("\n");
    }
    else if (n_threads == 1){
        sprintf(filename, "SIZE%d-NT1-INPUT1", size);
        generate_graph(size, filename, max_edges, 0, size);
        printf("Created file: %s, n_nodes: %d, max_edges: %d, start_id:%d, total_graph_nodes:%d\n", filename, size, max_edges, 0, size);
        // printf("%d\t%s\t%d\t%d\t%d\n", size, filename, max_edges, 0, size);
        // printf("\n");
    }
    else{
        int increment = size/n_threads;
        int size_for_file = size/n_threads; // gestire caso ultimo file
        int offset = 0; 

        for (int th = 1; th <= n_threads; th++)
        {
            sprintf(filename, "SIZE%d-NT%d-INPUT%d", size, n_threads, th);
            // printf("%s\n", filename);

            if (th == n_threads){
                size_for_file = size - offset; 
            }

            generate_graph(size_for_file, filename, max_edges, offset, size);
            printf("Created file: %s, n_nodes: %d, max_edges: %d, start_id:%d, total_graph_nodes:%d\n", filename, size_for_file, max_edges, offset, size);

            // printf("%d\t%s\t%d\t%d\t%d\n", size_for_file, filename, max_edges, offset, size);
            offset += increment; 
            
        }
        printf("\n");
    }

    return 0;
}
