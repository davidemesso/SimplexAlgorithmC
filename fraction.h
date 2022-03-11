#ifndef FRACTION_H_
#define FRACTION_H_

/** Struct describing a Fraction */
typedef struct Fraction
{
    int num; // numerator
    int den; // denominator
} Fraction;


int frc_gcd(Fraction f);
int frc_lcm(Fraction a, Fraction b);
Fraction frc_prod(Fraction a, Fraction b);
Fraction frc_sum(Fraction a, Fraction b);
Fraction frc_sub(Fraction a, Fraction b);
void frc_simplify(Fraction* f); 
Fraction frc_invert(Fraction f);
void frc_print(Fraction f);

#endif // FRACTION_H_