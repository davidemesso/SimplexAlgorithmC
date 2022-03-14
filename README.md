## Simplex algorithm in C

Used for solving simple linear optimization problems given the standard form of the model as a tableau.

This implementation uses the Gauss-Jordan method

1. select column with first positive/negative (max/min) in first row
2. find the pivot row, the row selected has the min rhs/coef ratio, coef MUST be positive
3. pivot transformation with gauss-jordan
4. repeat until no more positive/negative (max/min) in first row


#### Tableau
The tableau is given in a file and dinamically loaded

example:
``` dat
3 5 0
80 1 70 1 0 1 0 1 0 1
3 1 2 1 1 1 0 1 15 1
2 1 3 1 0 1 1 1 15 1
```
the format is:
```
rowCount colCount OPT
matrix of values
```
OPT can be 0 for maximize or 1 for minimize, as described in the enum Option in [utils.h](utils.h)
```C
typedef enum Option
{
    OPT_MAXIMIZE = 0,
    OPT_MINIMIZE = 1
} Option;
```
And every value is described by 2 numbers, first the numerator and then the denominator, everything is a fraction, see [fraction.h](./fraction.h)

#### How to use
```batch
.\simple.exe "tableau.dat"
```
In [tableau.dat](tableau.dat) you specify the tableau with his size and option (min/max) in first row.
Modify the tableau.dat with your problem, then run simplex.exe with the filename as parameter.
In case you need to recompile the [Makefile](Makefile) is given