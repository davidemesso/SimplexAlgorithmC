#include <stdio.h>
#include "simplex.h"

int main(int argc, const char *argv[])
{
    // Init
    Simplex simplex = smp_crateFromFile("./tableau.dat");
    smp_printReduced(simplex);

    // Resolve
    smp_optimize(&simplex, OPT_MAXIMIZE);
    smp_printReduced(simplex);
    smp_printSolution(simplex);
}