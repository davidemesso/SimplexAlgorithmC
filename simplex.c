#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "simplex.h"

// typedef Fraction** Tableau;

// typedef struct Simplex
// {
//     Tableau tableau;
//     int rowCount;
//     int colCount;
// } Simplex;

/** Allocate the simplex and load tableau values from a file */
Simplex smp_crateFromFile(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    int rows, cols;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);

    // ALLOCATION
    Tableau tableau = (Tableau)malloc(rows * sizeof(Fraction *));
    for (int i = 0; i < rows; ++i)
        tableau[i] = (Fraction *)malloc(cols * sizeof(Fraction));

    // READING AND SETTING VALUES
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int num, den;

            fscanf(file, "%d", &num);
            fscanf(file, "%d", &den);

            tableau[i][j].num = num;
            tableau[i][j].den = den;
        }
    }
    fclose(file);

    Simplex simplex = {tableau, rows, cols};
    return simplex;
}

// Simplify and print the tableau
void smp_printReduced(Simplex simplex)
{
    for (int i = 0; i < simplex.rowCount; i++)
    {
        for (int j = 0; j < simplex.colCount; j++)
        {
            frc_simplify(&simplex.tableau[i][j]);
            frc_print(simplex.tableau[i][j]);
            printf("\t");
        }
        printf("\n");
    }
    printf("\n");
}

/** Maximize the objective function of the given simplex */
void smp_optimize(Simplex *simplex, Option opt)
{
    /** SIMPLEX ALGORITHM
     * 1. select column with first positive/negative (max/min) in first row
     * 2. find the pivot row
     * 3. pivot with gauss-jordan
     * 4. repeat until no more positive/negative (max/min) in first row
     **/

    int pivotCol = 0;
    while (pivotCol != -1) // Step 4
    {
        // Step 1
        pivotCol = smp_getPivotCol(*simplex, opt);

        if(pivotCol != -1)
        {
            // Step 2
            int pivotRow = smp_getPivotRow(*simplex, pivotCol);

            // Step 3
            smp_pivotTransform(simplex, pivotRow, pivotCol);
        }
    } 
}

/** Get the col index of pivot
 *  
 * select column with first positive/negative (max/min) in first row
 * -1 means the algorithm is finished, cant optimize anymore
 **/
int smp_getPivotCol(Simplex simplex, Option opt)
{
    Fraction *f = simplex.tableau[0];
    for (int i = 0; i < simplex.colCount-1; i++)
    {
        if (opt == OPT_MAXIMIZE && f[i].num > 0)
            return i;
        if (opt == OPT_MINIMIZE && f[i].num < 0)
            return i;
    }
    return -1;
}

/** Get the row index of pivot
 *  
 * find the pivot row
 * the row selected has the min rhs/coef ratio, coef MUST be positive
 * if no positive coef is found, the solution is infinite
 **/
int smp_getPivotRow(Simplex simplex, int pivotCol)
{
    int rowIdx = -1;
    float min = INT_MAX;
    for (int i = 1; i < simplex.rowCount; i++)
    {
        // No negative coeff, impossible optimization
        if (simplex.tableau[i][pivotCol].num > 0)
        {
            // RHS/coeff -> [i][simplex.colcount-1]*inv([i][pivotCol])
            Fraction ratio = frc_prod(
                simplex.tableau[i][simplex.colCount - 1],
                frc_invert(simplex.tableau[i][pivotCol]));

            // Update min and idx if new min is found
            double val = ratio.num / ratio.den;
            if (val < min)
            {
                min = val;
                rowIdx = i;
            }
        }
    }
    return rowIdx;
}

/** Performs the pivot operation given row and column index on the simplex */
void smp_pivotTransform(Simplex* simplex, int pivotRow, int pivotCol) 
{    
    Fraction pivotValue = simplex->tableau[pivotRow][pivotCol];

    // Putting 1 in pivot position
    for (int i = 0; i < simplex->colCount; i++)
        simplex->tableau[pivotRow][i] = frc_prod(simplex->tableau[pivotRow][i], frc_invert(pivotValue));

    // Use linear combination of pivot row for putting zeros all over and under the pivot
    for (int i = 0; i < simplex->rowCount; i++)
    {   
        if(i!=pivotRow)
        {
            // Alpha*coeff in linear combination, is the value in the pivotcol for that row
            Fraction alpha = simplex->tableau[i][pivotCol];
            for (int j = 0; j < simplex->colCount; j++)
                simplex->tableau[i][j] = frc_sub(simplex->tableau[i][j], frc_prod(alpha, simplex->tableau[pivotRow][j]));
        }
    }
}

/** Prints the solution parsing the tableau */
void smp_printSolution(Simplex simplex)
{
    // Z value is always first row last column, negated
    printf("Z= ");
    Fraction z = simplex.tableau[0][simplex.colCount - 1];
    z = (Fraction){-z.num, z.den};
    frc_print(z);

    printf("\n( ");
    for (int j = 0; j < simplex.colCount-1; j++)
    {
        if (simplex.tableau[0][j].num != 0)
            printf("0 ");
        else
        {
            for (int i = 0; i < simplex.rowCount; i++)
            {
                if (simplex.tableau[i][j].num == 1 &&
                    simplex.tableau[i][j].den == 1)
                {
                    frc_print(simplex.tableau[i][simplex.colCount - 1]);
                    printf(" ");
                }
            }
        }
    }
    printf(")");
}