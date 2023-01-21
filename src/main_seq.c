#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

#include "Tarjan.h"

int main(int argc, char** argv){

    if (argc != 3){
        fprintf(stderr, "Usage:\n\t%s [file_name] [size]", argv[0]);
    }

    char *filename = argv[1];
    int size = atoi(argv[2]);
   
    //generate_graph(11, "out3", 2);
    SCCStack sccStack;
    sccStack = SCCStackCreate();
    Graph g;
    g = graphCreate(3);

    /*------------------------------------ READ PHASE -------------------------------------------*/


    struct tms read_start_times;
	clock_t read_start_etime;
	read_start_etime = times(&read_start_times);	// real elapsed time in clock ticks

    init_from_file(filename, &g);

    struct tms read_end_times;
	clock_t read_end_etime;
	read_end_etime = times(&read_end_times);

    #ifdef DEBUG
    graphPrint(&g);
    #endif
    /*------------------------------------ EXEC OF TARJAN PHASE ----------------------------------*/
    struct tms tarjan_start_times;
	clock_t tarjan_start_etime;
	tarjan_start_etime = times(&tarjan_start_times);

    SCC(&g, &sccStack);

    struct tms tarjan_end_times;
	clock_t tarjan_end_etime;
	tarjan_end_etime = times(&tarjan_end_times);

    // SCCArrayPrint(&sccStack.a);

    /*------------------------------------ WRITE PHASE -------------------------------------------*/

    char* out_file_str = malloc(sizeof(char)*100);
    sprintf(out_file_str, "SIZE%d-SEQ-OUTPUT", size);

    struct tms write_start_times;
	clock_t write_start_etime;
	write_start_etime = times(&write_start_times);

    FILE* out_file = fopen(out_file_str, "w");

    // printf("Number of SCC: %d\n", sccStack.a.length);
    fwrite(&sccStack.a.length, sizeof(int), 1, out_file);
    for (int i = 0; i < sccStack.a.length; i++) // per ogni SCC
    {
        // printf("SCC)%d\t length%d:", i, sccStack.a.items[i].components.length);
        fwrite(&sccStack.a.items[i].components.length, sizeof(int), 1, out_file);
        for (int j = 0; j < sccStack.a.items[i].components.length; ++j) // per tutti gli elementi dell'SCC
        {
            fwrite(&sccStack.a.items[i].components.items[j].id, sizeof(int), 1, out_file);
            // printf("%d ", sccStack.a.items[i].components.items[j].id); // stampa id del componente
        }
        // printf("\n");
    }

    struct tms write_end_times;
	clock_t write_end_etime;
	write_end_etime = times(&write_end_times);


    /*------------------------------------ MEASURING ELAPSED TIMES -------------------------------------------*/
    
	long clktck = 0;
	if((clktck = sysconf(_SC_CLK_TCK)) < 0){	// get clock ticks per sec
		fprintf(stderr,"ERROR: filed to get slock ticks per sec\n");
		exit(EXIT_FAILURE);
	}

    double tarjan_elapsed = (tarjan_end_etime - tarjan_start_etime) / (double) clktck;
	double read_elapsed = (read_end_etime - read_start_etime) / (double) clktck;
	double write_elapsed = (write_end_etime - write_start_etime) / (double) clktck;
	double elapsed = tarjan_elapsed + read_elapsed + write_elapsed;
	printf("%d,%.3f,%.3f,%.3f,%.3f\n",size,read_elapsed,tarjan_elapsed,write_elapsed,elapsed);	

    fclose(out_file);
    free(out_file_str);

    return 0;
    
}