#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define NUM_NODES 10
#define NUM_FILE 1


int main(int argc, char const *argv[])
{

    #if NUM_NODES == 10000
    #if NUM_FILE == 4
    generate_graph(2500, "INPUT_FILE1", 500, 0, 10000);
    generate_graph(2500, "INPUT_FILE2", 500, 2500, 10000);
    generate_graph(2500, "INPUT_FILE3", 500, 5000, 10000);
    generate_graph(2500, "INPUT_FILE4", 500, 7500, 10000);

    #elif NUM_FILE == 8
    generate_graph(1250, "INPUT_FILE1", 500, 0, 10000);
    generate_graph(1250, "INPUT_FILE2", 500, 1250, 10000);
    generate_graph(1250, "INPUT_FILE3", 500, 2500, 10000);
    generate_graph(1250, "INPUT_FILE4", 500, 3750, 10000);
    generate_graph(1250, "INPUT_FILE5", 500, 5000, 10000);
    generate_graph(1250, "INPUT_FILE6", 500, 6250, 10000);
    generate_graph(1250, "INPUT_FILE7", 500, 7500, 10000);
    generate_graph(1250, "INPUT_FILE8", 500, 8750, 10000);

    #elif NUM_FILE == 16
    generate_graph(625, "INPUT_FILE1", 500, 0, 10000);
    generate_graph(625, "INPUT_FILE2", 500, 625, 10000);
    generate_graph(625, "INPUT_FILE3", 500, 1250, 10000);
    generate_graph(625, "INPUT_FILE4", 500, 1875, 10000);
    generate_graph(625, "INPUT_FILE5", 500, 2500, 10000);
    generate_graph(625, "INPUT_FILE6", 500, 3125, 10000);
    generate_graph(625, "INPUT_FILE7", 500, 3750, 10000);
    generate_graph(625, "INPUT_FILE8", 500, 4375, 10000);
    generate_graph(625, "INPUT_FILE9", 500, 5000, 10000);
    generate_graph(625, "INPUT_FILE10", 500, 5625, 10000);
    generate_graph(625, "INPUT_FILE11", 500, 6250, 10000);
    generate_graph(625, "INPUT_FILE12", 500, 6875, 10000);
    generate_graph(625, "INPUT_FILE13", 500, 7500, 10000);
    generate_graph(625, "INPUT_FILE14", 500, 8125, 10000);
    generate_graph(625, "INPUT_FILE15", 500, 8750, 10000);
    generate_graph(625, "INPUT_FILE16", 500, 9375, 10000);
    #endif


    #elif NUM_NODES == 10
    #if NUM_FILE == 1
    generate_graph(10, "INPUT_FILE1", 2, 0, 10);
    #endif

    #elif NUM_NODES == 100000

    printf("100000");

    #endif

    return 0;
}
