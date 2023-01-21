#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Grafo.h"
#include "NodeStack.h"
#include "TList.h"
#include "NodeArray.h"
#include "SCCNode.h"
#include "SCCStack.h"
#include "utils.h"
#include "Tarjan.h"
#include <mpi.h>
#include <string.h>

/*
L'array ha: 
    - numero di interi inviati, 
    - numero di scc trovate; 
dopo questi primi due numeri per ogni scc ha: 
    - numero di nodi dell'scc, 
    - numero archi uscenti dall'scc, 
    - nodi presenti nell'scc, 
    - archi uscenti dall'scc ( gli archi sono rappresentati con l'id del nodo destinazione )
*/

void makeMPIArray(SCCStack * scc, TArray*a,int rank){
    int n = 0;
    arrayAdd(a, n);
    arrayAdd(a, scc->a.length);
    while(!SCCStackIsEmpty(scc)){
        SCCNode node = SCCStackPop(scc);
        int length_index = a->length;
        int len = 0 ;
        arrayAdd(a,node.components.length);

        arrayAdd(a,node.out_degree);

        for(int i = 0; i < node.components.length; i++){

            int flag = 0;
            THLNode *list = node.components.items[i].scc_components;
            if(!node.components.items[i].scc_flag){
                list = node.components.items[i].scc_components;
                arrayAdd(a,node.components.items[i].id);
            }    

            else{
                while (list != NULL && node.components.items[i].scc_components->link != NULL) {

                    arrayAdd(a,list->info.key);

                    len++;
                    list = list->link;
                    flag = 1;
                }
                len--;
            }

            if(flag == 1){
                arraySet(a,length_index, a->items[length_index] + len);
            }
        }
        THLNode *nodeList = node.outgoing;
        while (nodeList != NULL) {
            arrayAdd(a, nodeList->info.key);
            nodeList = nodeList->link;
        }
        arraySet(a, 0, a->length);
    }

}

void updateEdges(Graph * g, int id, int new_id){
    for(int i = 0; i < g->V; i++){
        for(int j = 0; j < g->adj[i].degree; j++){
            if( g->adj[i].outgoing_edges[j] == id &&  g->adj[i].outgoing_edges[j] != new_id){
                 g->adj[i].outgoing_edges[j] = new_id;
            }
        }
    }
}

void makeSupernode(Graph* g, int *a, int rank){
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
        i--;
    }
}




void tree_communication(Graph *g,SCCStack * sccStack, int rank, int size, int *recvcount, int*sendcount, int *recv_message) {
    int remain = size, half, rm, executed = 0, executed_send=0;

    MPI_Status status;

    TArray mpi_array = arrayCreate(0);
    while(remain != 1) {
        half = remain/2;
        rm = remain%2;
        if(rank < half) {
            MPI_Recv(recvcount, 1, MPI_INT,rank+half, 0, MPI_COMM_WORLD, &status);
            int num_elem_scc = recvcount[0];
            MPI_Recv(recv_message, num_elem_scc, MPI_INT, rank+half, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

           // printf("Processo %d ---------- Messaggio ricevuto da %d\n", rank, rank+half);
            //graphResize(g, g->V + recv_message[1]);
            makeSupernode(g, recv_message, rank);

            if(rank != 0){
                SCC(g, sccStack);
                executed = 1;
            }
            if(rank == 0){
                SCCArray a = SCCArrayCreate(0);
                sccStack->a = a;
                SCC(g, sccStack);
                for(int i = 0; i < g->V; i++){
                    g->adj[i].disc = -1;
                    g->adj[i].low = -1;
                }
            }
        }   

        else if(rank >= half+rm && rank < remain ) { // oppure else if ma senza condizione && executed_send != 1
            //TArray mpi_array = arrayCreate(0);
            if(executed != 1)
                SCC(g, sccStack);


            makeMPIArray(sccStack,&mpi_array,rank);

            sendcount[0] = mpi_array.length;

            MPI_Send(sendcount,1,MPI_INT, rank-half,0,MPI_COMM_WORLD);

            MPI_Send(mpi_array.items, mpi_array.length, MPI_INT,rank-half, 0, MPI_COMM_WORLD);
            executed_send = 1;

            return;
        }
        remain = half+rm;
    }

    if(rank == 0){
        TArray mpi_result = arrayCreate(0);
        // printf("sono il processo 0 questo è l'array risultato:\n");
        // SCCArrayPrint(&sccStack->a);
        makeMPIArray(sccStack,&mpi_result,rank);
        // printf("Number of elements of mpi_result: %d\n",mpi_result.items[0]); // n elementi
        // printf("SCC found: %d\n",mpi_result.items[1]); // n SCC trovati
        // arrayPrint(&mpi_result);    // ris stampato: [n_elementi] [n_SCC] [for n_SCC (n_components) (outgoing_edges) (c1 .. c_n_components)]
        makeSupernode(g,mpi_result.items,0);
    }
}





int main(int argc, char** argv){


    if (argc != 3){
        fprintf(stderr, "Usage:\n\t%s [file_name] [size]", argv[0]);
    }

    char *filename = argv[1];
    int size = atoi(argv[2]);

    int rank, n_ranks;
    int n_numbers = 5000000;

    int *recv_message;
    int * recvcount;
    int* sendcount;
    MPI_Status status;

    int return_value;

    recv_message = malloc(n_numbers*sizeof(int));
    recvcount = malloc(sizeof(int)) ;
    sendcount = malloc(sizeof(int)) ;
    
    // First call MPI_Init
    MPI_Init(&argc, &argv);

    // Get my rank and the number of ranks
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

    char file_index[20];

    sprintf(file_index, "%d", rank+1);

    // char filename[20] = "INPUT_FILE";
    strcat(filename, file_index);   

    // printf("%s\n", filename);
    
    SCCStack sccStack;
    sccStack = SCCStackCreate();
    Graph g1 = graphCreate(1);


    /*------------------------------------ READ PHASE -------------------------------------------*/
	double read_start_time = MPI_Wtime();
    
    init_from_file(filename, &g1);

	double read_end_time = MPI_Wtime();

    #ifdef DEBUG
    graphPrint(&g1);
    #endif
    
    SCC(&g1, &sccStack);

    /*------------------------------------ EXEC OF TARJAN PHASE ----------------------------------*/
	double tarjan_start_time = MPI_Wtime();	
    tree_communication(&g1, &sccStack, rank, n_ranks,recvcount,sendcount,recv_message);
	double tarjan_end_time = MPI_Wtime();

    /*------------------------------------ WRITE PHASE -------------------------------------------*/
	double write_start_time = MPI_Wtime();
	double write_end_time = MPI_Wtime();


    /*------------------------------------ MEASURING ELAPSED TIMES -------------------------------------------*/
	double read_time = read_end_time - read_start_time;
	double tarjan_time = tarjan_end_time - tarjan_start_time;
	double write_time = write_end_time - write_start_time;


    double global_read_time, global_tarjan_time, global_write_time;
	MPI_Reduce(&read_time,&global_read_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
	MPI_Reduce(&tarjan_time,&global_tarjan_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
	MPI_Reduce(&write_time,&global_write_time,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);

	double global_elapsed = global_read_time + global_tarjan_time + global_write_time;
	if(rank == 0) printf("%d,%d,%.3f,%.3f,%.3f,%.3f\n",size, n_ranks, global_read_time, global_tarjan_time, global_write_time, global_elapsed);

    return_value = MPI_Finalize();

    free(recv_message);
    free(sendcount);
    free(recvcount);

    return return_value;
    
}





