#include "fraction.h"
#include <stdio.h>

// typedef struct Fraction
// {
//     int num; // numerator
//     int den; // denominator
// } Fraction;

/** Returns the gcd of the fraction */
int frc_gcd(Fraction f)
{
    int reminder;
    while (f.num != 0)
    {
        reminder = f.num;
        f.num = f.den % f.num;
        f.den = reminder;
    }

    return f.den;
}

/** Returns the lcm of 2 fraction's den */
int frc_lcm(Fraction a, Fraction b)
{
    Fraction f = {a.den, b.den};
    return (a.den * b.den) / frc_gcd(f);
}

/** Returns the product of 2 fractions */
Fraction frc_prod(Fraction a, Fraction b)
{
    Fraction f = {a.num * b.num, a.den * b.den};
    frc_simplify(&f);

    return f;
}

/** Returns the sum of 2 fractions*/
Fraction frc_sum(Fraction a, Fraction b)
{
    const int lcm = frc_lcm(a,b);
    Fraction f = {(a.num * lcm/a.den) + (b.num * lcm/b.den), lcm};
    frc_simplify(&f);

    return f;
}

/** Returns the difference of 2 fractions*/
Fraction frc_sub(Fraction a, Fraction b)
{
    return frc_sum(a, (Fraction){-b.num, b.den});
}

/** Simplify the given fraction 
 *  Both numerator and denominator gets divided by the gcd of them 
 **/
void frc_simplify(Fraction *f)
{
    int gcdValue = frc_gcd(*f);
    f->num = f->num / gcdValue;
    f->den = f->den / gcdValue;

    if(f->den < 0)
    {
        f->den = -f->den;
        f->num = -f->num;
    }
}

/** Prints the fraction formatted
 *  If denominator is 1 it's omitted
 **/
void frc_print(Fraction f)
{
    f.den != 1 ? printf("%d/%d", f.num, f.den) : printf("%d", f.num);
}

/** Inverts the fraction */
Fraction frc_invert(Fraction f)
{
    return (Fraction){f.den, f.num};
}