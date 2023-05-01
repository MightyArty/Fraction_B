#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace ariel;

#define EPSILON 0.00001
#define GREAT 1000000

namespace ariel
{
    /**
     * @brief main constructor
     * @param top the upper number of the fraction
     * @param bottom the bottom number of the fraction
     */
    Fraction::Fraction(int top, int bottom)
    {
        int gcd = __gcd(top, bottom);
        setNumerator(top / gcd);
        setDenominator(bottom / gcd);
    }

    Fraction::Fraction(float number)
    {
        int den = 1;
        while (abs(number * den - round(number * den)) > EPSILON)
        {
            den++;
        }
        setNumerator(round(number * den));
        setDenominator(den);
    }

    Fraction::Fraction()
    {
        setNumerator(0);
        setDenominator(1);
    }

    int Fraction::getNumerator() const
    {
        return top;
    }

    int Fraction::getDenominator() const
    {
        return bottom;
    }

    int Fraction::setNumerator(int top)
    {
        this->top = top;
        return this->top;
    }

    int Fraction::setDenominator(int bottom)
    {
        if (bottom == 0)
        {
            throw invalid_argument("Divison by zero!");
        }
        this->bottom = bottom;
        return this->bottom;
    }

    Fraction Fraction::operator++()
    {
        setNumerator(getNumerator() + getDenominator());
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction old = *this;
        setNumerator(getNumerator() + getDenominator());
        return old;
    }

    Fraction Fraction::operator--()
    {
        setNumerator(getNumerator() - getDenominator());
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction old = *this;
        setNumerator(getNumerator() - getDenominator());
        return old;
    }

    Fraction Fraction::operator+(const Fraction &other) const
    {
        int new_top = (getNumerator() * other.getDenominator()) + (other.getNumerator() * getDenominator());
        int new_bottom = getDenominator() * other.getDenominator();
        return Fraction(new_top, new_bottom);
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        int new_top = (getNumerator() * other.getDenominator()) - (other.getNumerator() * getDenominator());
        int new_bottom = getDenominator() * other.getDenominator();
        return Fraction(new_top, new_bottom);
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.getDenominator() == 0)
        {
            throw invalid_argument("Divison by zero!");
        }
        int new_top = getNumerator() * other.getDenominator();
        int new_bottom = getDenominator() * other.getNumerator();
        return Fraction(new_top, new_bottom);
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int new_top = getNumerator() * other.getNumerator();
        int new_bottom = getDenominator() * other.getDenominator();
        return Fraction(new_top, new_bottom);
    }

    Fraction operator+(float number, const Fraction &other)
    {
        float result = number + static_cast<float>(other.getNumerator()) / other.getDenominator();
        return Fraction(result);
    }

    Fraction operator-(float number, const Fraction &other)
    {
        float result = number - static_cast<float>(other.getNumerator()) / other.getDenominator();
        return Fraction(result);
    }

    Fraction operator/(float number, const Fraction &other)
    {
        float result = number / (static_cast<float>(other.getNumerator()) / other.getDenominator());
        return Fraction(result);
    }

    Fraction operator*(float number, const Fraction &other)
    {
        float result = number * static_cast<float>(other.getNumerator()) / other.getDenominator();
        return Fraction(result);
    }

    Fraction operator+(const Fraction &other, float number)
    {
        float result = static_cast<float>(other.getNumerator()) / other.getDenominator() + number;
        return Fraction(result);
    }

    Fraction operator-(const Fraction &other, float number)
    {
        float result = static_cast<float>(other.getNumerator()) / other.getDenominator() - number;
        return Fraction(result);
    }

    Fraction operator/(const Fraction &other, float number)
    {
        float result = (static_cast<float>(other.getNumerator()) / other.getDenominator()) / number;
        return Fraction(result);
    }

    Fraction operator*(const Fraction &other, float number)
    {
        float result = static_cast<float>(other.getNumerator()) / other.getDenominator() * number;
        return Fraction(result);
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return (this->top * other.getDenominator()) < (other.getNumerator() * this->bottom);
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return (this->top * other.getDenominator()) <= (other.getNumerator() * this->bottom);
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return (this->top * other.getDenominator()) > (other.getNumerator() * this->bottom);
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return (this->top * other.getDenominator()) >= (other.getNumerator() * this->bottom);
    }

    bool operator<(float number, const Fraction &other)
    {
        return (number * other.getDenominator()) < other.getNumerator();
    }

    bool operator<=(float number, const Fraction &other)
    {
        return (number * other.getDenominator()) <= other.getNumerator();
    }

    bool operator>(float number, const Fraction &other)
    {
        return (number * other.getDenominator()) > other.getNumerator();
    }

    bool operator>=(float number, const Fraction &other)
    {
        return (number * other.getDenominator()) >= other.getNumerator();
    }

    bool operator<(const Fraction &other, float number)
    {
        return other.getNumerator() < (number * other.getDenominator());
    }

    bool operator<=(const Fraction &other, float number)
    {
        return other.getNumerator() <= (number * other.getDenominator());
    }

    bool operator>(const Fraction &other, float number)
    {
        return other.getNumerator() > (number * other.getDenominator());
    }

    bool operator>=(const Fraction &other, float number)
    {
        return other.getNumerator() >= (number * other.getDenominator());
    }

    bool operator==(const Fraction &left, const Fraction &right)
    {
        return left.getNumerator() * right.getDenominator() == right.getNumerator() * left.getDenominator();
    }

    std::ostream &operator<<(std::ostream &out, const Fraction &other)
    {
        out << other.getNumerator() << "/" << other.getDenominator();
        return out;
    }

    std::istream &operator>>(std::istream &in, Fraction &other)
    {
        int first, second;
        char seperator;
        in >> first >> seperator >> second;
        if (in && seperator == '/')
        {
            other = Fraction(first, second);
        }
        else
        {
            in.setstate(std::ios_base::failbit);
        }
        return in;
    }
    // void Fraction::simplify()
    // {
    //     int gcd = 1;
    //     for (int i = 1; i <= this->top && i <= this->bottom; i++)
    //     {
    //         if (this->top % i == 0 && this->bottom % i == 0)
    //         {
    //             gcd = i;
    //         }
    //     }
    //     this->top = this->top / gcd;
    //     this->bottom = this->bottom / gcd;
    // }

}