#ifndef SIMPLEX_H_
#define SIMPLEX_H_

#include "utils.h"
#include "fraction.h"

/** Alias for readability */
typedef Fraction** Tableau;

/** Struct describing a Tableau with his own size */
typedef struct Simplex
{
    Tableau tableau;
    int rowCount;
    int colCount;
} Simplex;

Simplex smp_crateFromFile(const char *file_name);
void smp_printReduced(Simplex simplex);
void smp_optimize(Simplex* simplex, Option opt);
int smp_getPivotCol(Simplex simplex, Option opt);
int smp_getPivotRow(Simplex simplex, int pivotCol);
void smp_pivotTransform(Simplex* simplex, int pivotRow, int pivotCol);
void smp_printSolution(Simplex simplex);

#endif // SIMPLEX_H_