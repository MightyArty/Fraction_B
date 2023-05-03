#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;
using namespace ariel;

#define EPSILON 0.00001
#define GREAT 1000

namespace ariel
{
    /**
     * @brief main constructor
     * @param top the upper number of the fraction
     * @param bottom the bottom number of the fraction
     */
    Fraction::Fraction(int top, int bottom)
    {
        if (bottom == 0)
        {
            throw invalid_argument("Dividing by zero!");
        }

        this->top = top;
        this->bottom = bottom;
        simplify();
    }

    Fraction::Fraction(float number)
    {
        int temp = number * GREAT;
        int common = __gcd(temp, GREAT);
        int new_top = temp / common;
        int new_bottom = GREAT / common;
        setNumerator(new_top);
        if (new_bottom == 0)
        {
            throw runtime_error("Divide by zero!");
        }
        setDenominator(new_bottom);
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
            throw runtime_error("Divison by zero!");
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
        float first = float(getNumerator()) / (getDenominator());
        float second = float(other.getNumerator()) / (other.getDenominator());
        float result = first + second;
        // check overflow for the Fractions
        if (result < static_cast<float>(INT_MIN) || result > static_cast<float>(INT_MAX) ||
            first < static_cast<float>(INT_MIN) || first > static_cast<float>(INT_MAX) ||
            second < static_cast<float>(INT_MIN) || second > static_cast<float>(INT_MAX))
        {
            throw overflow_error("Overflow in '+' operator");
        }
        int new_top = (getNumerator() * other.getDenominator()) + (other.getNumerator() * getDenominator());
        int new_bot = getDenominator() * other.getDenominator();
        // check overflow for the result
        if (new_top > numeric_limits<int>::max() || new_top < numeric_limits<int>::min() ||
            new_bot > numeric_limits<int>::max() || new_bot < numeric_limits<int>::min())
        {
            throw overflow_error("Overflow in '+' operator");
        }
        int gcd = __gcd(new_top, new_bot);
        Fraction temp(new_top / gcd, new_bot / gcd);
        return temp;
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        float first = float(getNumerator()) / (getDenominator());
        float second = float(other.getNumerator()) / (other.getDenominator());
        float result = first - second;
        // check overflow for the Fractions
        if (result < static_cast<float>(INT_MIN) || result > static_cast<float>(INT_MAX) ||
            first < static_cast<float>(INT_MIN) || first > static_cast<float>(INT_MAX) ||
            second < static_cast<float>(INT_MIN) || second > static_cast<float>(INT_MAX))
        {
            throw overflow_error("Overflow in '-' operator");
        }
        int new_top = (getNumerator() * other.getDenominator()) - (other.getNumerator() * getDenominator());
        int new_bot = getDenominator() * other.getDenominator();
        // check overflow for the result
        if (new_top > numeric_limits<int>::max() || new_top < numeric_limits<int>::min() ||
            new_bot > numeric_limits<int>::max() || new_bot < numeric_limits<int>::min())
        {
            throw overflow_error("Overflow in '+' operator");
        }
        int gcd = __gcd(new_top, new_bot);
        Fraction temp(new_top / gcd, new_bot / gcd);
        return temp;

        // int mul1 = getNumerator() * other.getDenominator();
        // int mul2 = getDenominator() * other.getNumerator();
        // int new_top = mul1 - mul2;
        // int new_bot = getDenominator() * other.getDenominator();
        // // check if overflow exist
        // if (mul1 > 0 && mul2 < 0 && (max(mul1, mul2) >= new_top))
        // {
        //     throw overflow_error("Overflow in '-' operator");
        // }
        // Fraction result(new_top, new_bot);
        // result.simplify();
        // return result;
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.getNumerator() == 0)
        {
            throw runtime_error("Divison by zero!");
        }
        float first = float(getNumerator()) / (getDenominator());
        float second = float(other.getNumerator()) / (other.getDenominator());
        float result = first / second;
        // check overflow for the Fractions
        if (result < static_cast<float>(INT_MIN) || result > static_cast<float>(INT_MAX) || first < static_cast<float>(INT_MIN) || first > static_cast<float>(INT_MAX) || second < static_cast<float>(INT_MIN) || second > static_cast<float>(INT_MAX))
        {
            throw overflow_error("Overflow in '/' operator");
        }
        int new_top = (getNumerator() * other.getDenominator());
        int new_bot = (getDenominator() * other.getNumerator());
        // check overflow for the result
        if (new_top < numeric_limits<int>::min() || new_top > numeric_limits<int>::max() ||
            new_bot < numeric_limits<int>::min() || new_bot > numeric_limits<int>::max())
        {
            throw overflow_error("Overflow in '/' operator");
        }
        Fraction temp(other.getDenominator(), other.getNumerator());
        return *this * temp;
    }

    Fraction Fraction::operator*(const Fraction &other) const
    {
        int new_top = getNumerator() * other.getNumerator();
        int new_bot = getDenominator() * other.getDenominator();
        Fraction result(new_top, new_bot);
        result.simplify();

        // check overflow for the Numerator
        if (getNumerator() > 1 && other.getNumerator() > 1 && (getNumerator() >= new_top || other.getNumerator() >= new_top))
        {
            throw overflow_error("Overflow in '*' operator (Numerator)");
        }

        // check overflow for the Denominator
        if (getDenominator() > 1 && other.getDenominator() > 1 && (getDenominator() >= new_bot || other.getDenominator() >= new_bot))
        {
            throw overflow_error("Overflow in '*' operator (Denominator)");
        }
        return result;
    }

    Fraction operator+(float number, const Fraction &other)
    {
        Fraction to_frac(number);
        return Fraction(to_frac + other);
    }

    Fraction operator-(float number, const Fraction &other)
    {
        Fraction to_frac(number);
        return Fraction(to_frac - other);
    }

    Fraction operator/(float number, const Fraction &other)
    {
        if (other.getNumerator() == 0)
        {
            throw runtime_error("Divison by zero!");
        }
        Fraction to_frac(number);
        return Fraction(to_frac / other);
    }

    Fraction operator*(float number, const Fraction &other)
    {
        Fraction to_frac(number);
        return Fraction(to_frac * other);
    }

    Fraction operator+(const Fraction &other, float number)
    {
        Fraction to_frac(number);
        return Fraction(other + to_frac);
    }

    Fraction operator-(const Fraction &other, float number)
    {
        Fraction to_frac(number);
        return Fraction(other - to_frac);
    }

    Fraction operator/(const Fraction &other, float number)
    {
        if (number == 0 || other.getDenominator() == 0)
        {
            throw runtime_error("Divison by zero!");
        }
        Fraction to_frac(number);
        return Fraction(other / to_frac);
    }

    Fraction operator*(const Fraction &other, float number)
    {
        Fraction to_frac(number);
        return Fraction(other * to_frac);
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

    /**
     * Wanted to call the simplify function but had trouble with it so here is a duplicate code for the simplify
     */
    std::ostream &operator<<(std::ostream &output, const Fraction &other)
    {
        int sign = -1;
        if ((other.getDenominator() < 0 && other.getNumerator() < 0) || other.getDenominator() < 0 && other.getNumerator() > 0)
        {
            output << sign * other.getNumerator() << "/" << sign * other.getDenominator();
        }
        else
        {
            output << other.getNumerator() << "/" << other.getDenominator();
        }
        return output;
    }

    // The hardest part of the assigment was to understand how to work with istream input
    std::istream &operator>>(std::istream &input, Fraction &other)
    {
        int first, second, seperator;

        // read the numerator
        input >> first;
        if (input.fail())
        {
            throw std::runtime_error("Error in reading the numerator");
        }

        // read the seperator
        input >> seperator;
        if (input.fail())
        {
            throw std::runtime_error("Error in reading the seperator");
        }

        if (seperator == '/')
        {
            input >> second;
            if (input.fail())
            {
                throw std::runtime_error("Error in reading the denomenator");
            }
            other.setNumerator(first);
            other.setDenominator(second);
        }
        else
        {
            if (seperator == 0)
            {
                throw std::runtime_error("Error in the seperator");
            }
            other.setNumerator(first);
            other.setDenominator(seperator);
        }
        return input;
    }

    void Fraction::simplify()
    {
        int gcd = abs(__gcd(getNumerator(), getDenominator()));
        // checking if the fraction is (-a/-b) or (a/-b)
        // and updating so the test would pass
        if ((getDenominator() < 0 && getNumerator() < 0) || (getDenominator() < 0 && getNumerator() > 0))
        {
            setNumerator((-getNumerator()) / gcd);
            setDenominator((-getDenominator()) / gcd);
        }
        else
        {
            setNumerator(getNumerator() / gcd);
            setDenominator(getDenominator() / gcd);
        }
    }

}