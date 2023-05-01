#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <string>
using namespace std;

namespace ariel
{
    class Fraction
    {
    private:
        int top;    // represent the top part of the fraction, 3/4 --> 3 is the top
        int bottom; // represent the bottom part of the fraction, 3/4 --> 4 is the bottom

    public:
        // Constructors
        Fraction(int top, int bottom);
        Fraction(float number);
        Fraction();

        // getters and setters for the top and bottom part
        int getNumerator() const;
        int getDenominator() const;
        int setNumerator(int top);
        int setDenominator(int bottom);

        // increment/decrement operators
        Fraction operator-() const;
        Fraction operator++();
        Fraction operator++(int);
        Fraction operator--();
        Fraction operator--(int);

        // binary operators with two Fractions
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;

        // binary operators with float and Fraction object
        friend Fraction operator+(float number, const Fraction &other);
        friend Fraction operator-(float number, const Fraction &other);
        friend Fraction operator/(float number, const Fraction &other);
        friend Fraction operator*(float number, const Fraction &other);

        // binary operators with Fraction object and float
        friend Fraction operator+(const Fraction &other, float number);
        friend Fraction operator-(const Fraction &other, float number);
        friend Fraction operator/(const Fraction &other, float number);
        friend Fraction operator*(const Fraction &other, float number);

        // comparison operator with other Fraction object
        bool operator<(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        // comparison operator with float and other Fraction object
        friend bool operator<(float number, const Fraction &other);
        friend bool operator<=(float number, const Fraction &other);
        friend bool operator>(float number, const Fraction &other);
        friend bool operator>=(float number, const Fraction &other);

        // comparison operators with other Fraction object and float
        friend bool operator<(const Fraction &other, float number);
        friend bool operator<=(const Fraction &other, float number);
        friend bool operator>(const Fraction &other, float number);
        friend bool operator>=(const Fraction &other, float number);

        // comparison operator for two fraction to be equal
        friend bool operator==(const Fraction &my_frac, const Fraction &other);

        // I/O operators
        friend std::ostream &operator<<(std::ostream &out, const Fraction &other);
        friend std::istream &operator>>(std::istream &in, const Fraction &other);
    };
}

#endif