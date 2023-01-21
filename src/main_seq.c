#include <stdio.h>
#include <stdlib.h>

#include "Tarjan_sequential.h"


int main(int argc, char** argv){

    char filename[20] = "INPUT_FILE1";
   
    //generate_graph(11, "out3", 2);
    SCCStack sccStack;
    sccStack = SCCStackCreate();
    Graph g;
    g = graphCreate(3);

    init_from_file(filename, &g);

    graphPrint(&g);

    SCC(&g, &sccStack);
    SCCArrayPrint(&sccStack.a);

    return 0;
    
}