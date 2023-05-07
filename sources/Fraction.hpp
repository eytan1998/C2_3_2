

#ifndef FRACTION_H
#define FRACTION_H
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

namespace ariel{}

class Fraction {
    int a;
    int b;
public:
    explicit Fraction();
    Fraction(int numerator, int denominator);
    Fraction(float f_input);

    int getNumerator();

    int getDenominator();

    string str();

    friend void reduce(Fraction &frc);

    friend Fraction operator+ (const Fraction& frc1, const Fraction& frc2);

    friend Fraction operator- (const Fraction& frc1, const Fraction& frc2);

    friend Fraction operator* (const Fraction& frc1, const Fraction& frc2);

    friend Fraction operator/ (const Fraction& frc1, const Fraction& frc2);


    Fraction operator++();
    const Fraction operator++(int);
    Fraction operator--();
    const Fraction operator--(int);

    friend bool operator==(const Fraction &frc1, const Fraction &frc2);

    friend bool operator!=(const Fraction &frc1, const Fraction &frc2);

    friend bool operator<(const Fraction &frc1, const Fraction &frc2);

    friend bool operator>(const Fraction &frc1, const Fraction &frc2);

    friend bool operator<=(const Fraction &frc1, const Fraction &frc2);

    friend bool operator>=(const Fraction &frc1, const Fraction &frc2);


    friend ostream &operator<<(ostream &output, const Fraction &frc);

    friend istream &operator>>( istream  &input, Fraction &frc );


};
#endif //FRACTION_H
