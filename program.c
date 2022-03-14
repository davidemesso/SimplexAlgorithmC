#include <stdio.h>
#include <stdlib.h>
#include "simplex.h"

int main(int argc, const char *argv[])
{
    if(argc==1) {
        printf("\nMust provide the tableau file.");
        exit(1);
    }
    const char* filename = argv[1];

    // Init
    Simplex simplex = smp_crateFromFile(filename);
    smp_printReduced(simplex);

    printf("%s\n", simplex.opt == OPT_MAXIMIZE ? "Maximizing..." : "Minimizing...");

    // Resolve
    smp_optimize(&simplex);
    smp_printReduced(simplex);
    smp_printSolution(simplex);
}