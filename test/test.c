#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "Tarjan.h"

#define BUFFER_DIM sizeof(char)*((dim*2) + 3)

typedef void (* decorable_generate_graph)(int, char*, int);
typedef void (* decorable_init_from_file)(char*, Graph*);
typedef void (* decorable_SCC)(Graph*, SCCStack*);


void test_SCC(Graph* test_graph, SCCStack* test_SCC_partition, int** expected_SCC_partition, decorable_SCC SCC_function){






}

void test_generate_graph(int dim, char* name_output_file, int max_degree, decorable_generate_graph graph_generator){
    graph_generator(dim, name_output_file, max_degree);

    char* buffer = (char*)malloc(BUFFER_DIM);

    FILE* fp; 
    fp = fopen(name_output_file, "r");
    assert(fp != NULL);

    int node_count = 0;
    int edge_count = 0;

    int dimension = 0;
    fread(&dimension, sizeof(int), 1, fp);

    int node = -1; 
    int index = -1;
    int degree = -1;  

    int* neighbour = (int*)malloc(sizeof(int)*max_degree);

    for (int i = 0; i < dimension; i++)
    {

        fread(&node, sizeof(int), 1, fp);
        node_count++; 
        fread(&index, sizeof(int), 1, fp);
        fread(&degree, sizeof(int), 1, fp);
        fread(neighbour, sizeof(int), degree, fp);
    }

    assert(dim == node_count);  
    printf("passed.\n");

}


void test_init_from_file(char* input_file, Graph* test_graph, Graph* expected_graph, decorable_init_from_file init){

    FILE* fp; 

    fp = fopen("test_init_file", "w");
    int node_id = 0; 
    int index = 0; 
    int degree = 0; 
    int edge = 0;
    
    /* dimension */
    int dimension = 5;
    fwrite(&dimension, sizeof(int), 1, fp);

    /*  node 0  */
    node_id = 0; 
    index = 0; 
    degree = 2; 
    fwrite(&node_id, sizeof(int), 1, fp);
    fwrite(&index, sizeof(int), 1, fp);
    fwrite(&degree, sizeof(int), 1, fp);
    edge = 1;
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 2; 
    fwrite(&edge, sizeof(int), 1, fp);

    /* node 1 */
    node_id = 1;
    index = 2;
    degree = 0; 
    fwrite(&node_id, sizeof(int), 1, fp);
    fwrite(&index, sizeof(int), 1, fp);
    fwrite(&degree, sizeof(int), 1, fp);

    /* node 2 */
    node_id = 2;
    index = 1; 
    degree = 0; 
    fwrite(&node_id, sizeof(int), 1, fp);
    fwrite(&index, sizeof(int), 1, fp);
    fwrite(&degree, sizeof(int), 1, fp);

    /* node 3 */
    node_id = 3;
    index = 4;
    degree = 4;
    fwrite(&node_id, sizeof(int), 1, fp);
    fwrite(&index, sizeof(int), 1, fp);
    fwrite(&degree, sizeof(int), 1, fp);
    edge = 0;
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 1;
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 2; 
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 3;
    fwrite(&edge, sizeof(int), 1, fp);


    /* node 4 */
    node_id = 4;
    index = 3;
    degree = 3;
    fwrite(&node_id, sizeof(int), 1, fp);
    fwrite(&index, sizeof(int), 1, fp);
    fwrite(&degree, sizeof(int), 1, fp);
    edge = 3;
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 4;
    fwrite(&edge, sizeof(int), 1, fp);
    edge = 2; 
    fwrite(&edge, sizeof(int), 1, fp);

    fclose(fp);


    init("test_init_file", test_graph);

   

    printf("Testing that the tested graph build from test_init_file is equal to the one expected\n");
    for (int i = 0; i < expected_graph->V; i++)
    {
        Node* node_expected = &expected_graph->adj[i];
        Node* node_test = &test_graph->adj[i];

        printf("Confronting: [exp_node_degree: %d, test_node_degree: %d]\n", (*node_expected).degree, (*node_test).degree);
        assert((*node_expected).degree == (*node_test).degree);
        printf("Confronting: [node_exp_id: %d, node_test_id: %d]\n", (*node_expected).id, (*node_test).id);
        assert((*node_expected).id == (*node_test).id);

        for (int j = 0; j < (*node_expected).degree; j++)
        {
            printf("Confronting: [exp_node_outgoing_edge_%d: %d, test_node_outgoing_edge_%d: %d]\n",j,expected_graph->adj[i].outgoing_edges[j],j,(*node_test).outgoing_edges[j]);
            assert((*node_expected).outgoing_edges[j] == (*node_test).outgoing_edges[j]);
        }

    }
    printf("Passed.\n");

}


// typedef struct{
//     int n_SCC;
//     int** partition;
// }Graph_Partition; 

// Graph_Partition create_partition(int n_SCC, ){

// }

// insert_partition(int SCC, int* nodes){

// }


int main(int argc, char const *argv[])
{

    Graph test_graph; 

    test_generate_graph(10,"test1_file", 5, generate_graph);

    Graph expected_graph = graphCreate(5);

    Node node0 = node_create(0,2);
    Node node1 = node_create(1,0);
    Node node2 = node_create(2,0);
    Node node3 = node_create(3,4);
    Node node4 = node_create(4,3);

    node0.outgoing_edges[0] = 1;
    node0.outgoing_edges[1] = 2;
    addNode(&expected_graph, node0);


    addNode(&expected_graph, node1);

    addNode(&expected_graph, node2);


    node3.outgoing_edges[0] = 0;
    node3.outgoing_edges[1] = 1;
    node3.outgoing_edges[2] = 2;
    node3.outgoing_edges[3] = 3;
    addNode(&expected_graph, node3);


    node4.outgoing_edges[0] = 3;
    node4.outgoing_edges[1] = 4;
    node4.outgoing_edges[2] = 2;
    addNode(&expected_graph, node4);


    test_init_from_file("test_init_file", &test_graph, &expected_graph, init_from_file);

    // graphDestroy(&test_graph);
    // graphDestroy(&expected_graph);




    // // Graph test_graph2 = graphCreate(10);
    // test_graph = graphCreate(10);
    // create_all_connected_graph(&test_graph);



    // // int n_partitions = 2; 
    // // int** expected_partition = malloc(sizeof(int*)*n_partitions);
    // // int* SCC1 = malloc(sizeof(int)*5);
    // // for (int i = 0; i < 5; i++)
    // // {
    // //     SCC1[i] = i; 
    // // }
    // // int* SCC2 = malloc(sizeof(int)*5);
    // // for (int i = 0; i < 5; i++)
    // // {
    // //     SCC2[i] = i + 5; 
    // // }
    
    
    // // *expected_partition = SCC1; 
    // // *expected_partition++;
    // // *expected_partition = SCC2; 
    // // *expected_partition--;

    // // for (int i = 0; i < 2; i++)
    // // {
    // //     for (int i = 0; i < 5; i++)
    // //     {
    // //         printf("%d ", (*expected_partition)[i]);
    // //     }
    // //     expected_partition++;
    // //     printf("\n");
    // // }

    // // SCCArray expected_SCC_partition = SCCArrayCreate(10);

    // // SCCNode supernode = SCCNodeCreate();
    // // nodeArrayAdd(&supernode.components, node_create(0,10));
    // // nodeArrayAdd(&supernode.components, node_create(1,10));
    // // nodeArrayAdd(&supernode.components, node_create(2,10));
    // // nodeArrayAdd(&supernode.components, node_create(3,10));
    // // nodeArrayAdd(&supernode.components, node_create(4,10));
    // // nodeArrayAdd(&supernode.components, node_create(5,10));
    // // nodeArrayAdd(&supernode.components, node_create(6,10));
    // // nodeArrayAdd(&supernode.components, node_create(7,10));
    // // nodeArrayAdd(&supernode.components, node_create(8,10));
    // // nodeArrayAdd(&supernode.components, node_create(9,10));

    // // SCCArrayAdd(expected_SCC_partition, )
    
    // // nodeArrayPrint(&supernode.components);

    // int n_part = 1; 
    // SCCNode* expected = (SCCNode*)malloc(sizeof(SCCNode)*n_part);
    // *expected = SCCNodeCreate();
    // nodeArrayAdd(&(*expected).components, node_create(0,10));
    // nodeArrayAdd(&(*expected).components, node_create(1,10));
    // nodeArrayAdd(&(*expected).components, node_create(2,10));
    // nodeArrayAdd(&(*expected).components, node_create(3,10));
    // nodeArrayAdd(&(*expected).components, node_create(4,10));
    // nodeArrayAdd(&(*expected).components, node_create(5,10));
    // nodeArrayAdd(&(*expected).components, node_create(6,10));
    // nodeArrayAdd(&(*expected).components, node_create(7,10));
    // nodeArrayAdd(&(*expected).components, node_create(8,10));
    // nodeArrayAdd(&(*expected).components, node_create(9,10));


    // // nodeArrayPrint(&(*expected).components);

    // for (int i = 0; i < 10; i++)
    // {
    //     printf("%d ", nodeArrayGet(&(*expected).components, i).id);
    // }
    




    // int n_part2 = 4; 
    // SCCNode* expected2 = (SCCNode*)malloc(sizeof(SCCNode)*n_part2);
    // int* partition_sizes = (int*)malloc(sizeof(int)*n_part2);

    // printf("expected2: %p partition_sizes: %p", expected2, partition_sizes);

    // *expected2 = SCCNodeCreate();
    // nodeArrayAdd(&(*expected2).components, node_create(0,10));
    // nodeArrayAdd(&(*expected2).components, node_create(1,10));
    // nodeArrayAdd(&(*expected2).components, node_create(2,10));
    // // partition_sizes[0] = 10;
    // *partition_sizes = 3; 

    // printf("also before %d\n", *partition_sizes);

    // expected2++;
    // partition_sizes++;

    // *expected2 = SCCNodeCreate();
    // nodeArrayAdd(&(*expected2).components, node_create(3,10));
    // nodeArrayAdd(&(*expected2).components, node_create(4,10));
    // nodeArrayAdd(&(*expected2).components, node_create(5,10));
    // // partition_sizes[1] = 11; 
    // *partition_sizes = 3; 

    // partition_sizes--;
    // printf("also before %d\n", *partition_sizes);
    // partition_sizes++;
    

    // expected2++;
    // partition_sizes++;


    // *expected2 = SCCNodeCreate();
    // nodeArrayAdd(&(*expected2).components, node_create(6,10));
    // nodeArrayAdd(&(*expected2).components, node_create(7,10));
    // nodeArrayAdd(&(*expected2).components, node_create(8,10));
    // // partition_sizes[2] = 12;
    // *partition_sizes = 3; 

    // expected2++;
    // partition_sizes++;


    // *expected2 = SCCNodeCreate();
    // nodeArrayAdd(&(*expected2).components, node_create(9,10));
    // // partition_sizes[3] = 13; 
    // *partition_sizes = 1; 

    // expected2 = expected2-3;
    // // expected2--;
    // // expected2--;
    // partition_sizes = partition_sizes-3;
    // // partition_sizes--;
    // // partition_sizes--;


    // nodeArrayPrint(&(*expected2).components);

    // for (int i = 0; i < n_part2; i++)
    // {
    //     printf("part_%d ", i);

    //         for (int j = 0; j < *partition_sizes; j++)
    //         {
    //             printf("%d ", nodeArrayGet(&(*expected2).components, j).id);
                
    //         }
            
    //     partition_sizes++;
    //     expected2++;
        
    //     printf("\n");
    // }
    
    
    






    return 0;
}



