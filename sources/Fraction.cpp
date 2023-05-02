#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

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
            throw invalid_argument("Divide by zero!");
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
        int a = getNumerator();
        int b = getDenominator();
        int c = other.getNumerator();
        int d = other.getDenominator();
        if (checkOverflow(a, d, a * d) || checkOverflow(c, b, c * b))
        {
            throw overflow_error("Overflow in '+' operator");
        }

        int new_top = (getNumerator() * other.getDenominator()) + (other.getNumerator() * getDenominator());
        int new_bot = getDenominator() * other.getDenominator();
        int gcd = __gcd(new_top, new_bot);
        Fraction result(new_top / gcd, new_bot / gcd);
        return result;
    }

    Fraction Fraction::operator-(const Fraction &other) const
    {
        int mul1 = getNumerator() * other.getDenominator();
        int mul2 = getDenominator() * other.getNumerator();
        int new_top = mul1 - mul2;
        int new_bot = getDenominator() * other.getDenominator();
        // check if overflow exist
        if (mul1 > 0 && mul2 < 0 && (max(mul1, mul2) >= new_top))
        {
            throw overflow_error("Overflow in '-' operator");
        }
        Fraction result(new_top, new_bot);
        result.simplify();
        return result;

        // Fraction temp(other);
        // int new_top = (getNumerator() * other.getDenominator()) - (other.getNumerator() * getDenominator());
        // int new_bottom = getDenominator() * other.getDenominator();
        // return Fraction(new_top, new_bottom);
    }

    Fraction Fraction::operator/(const Fraction &other) const
    {
        int a = getNumerator();
        int b = getDenominator();
        int c = other.getNumerator();
        int d = other.getDenominator();
        if (c == 0)
        {
            throw invalid_argument("Dividing by zero!");
        }
        if (checkOverflow(a, d, a * d) || checkOverflow(b, c, b * c))
        {
            throw overflow_error("Overflow error in '/' operator");
        }
        int gcd1 = __gcd(a, c);
        int gcd2 = __gcd(d, b);
        return Fraction((a / gcd1) * (d / gcd2), (b / gcd2) * (c / gcd1));

        // if (other.getDenominator() == 0)
        // {
        //     throw invalid_argument("Divison by zero!");
        // }
        // int new_top = getNumerator() * other.getDenominator();
        // int new_bottom = getDenominator() * other.getNumerator();
        // return Fraction(new_top, new_bottom);
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

        // int a = getNumerator();
        // int b = getDenominator();
        // int c = other.getNumerator();
        // int d = other.getDenominator();
        // if (checkOverflow(a, c, a * c) || checkOverflow(b, d, b * d))
        // {
        //     throw overflow_error("Overflow error in '*' operator");
        // }

        // return Fraction(a * c, b * d);

        // int new_top = getNumerator() * other.getNumerator();
        // int new_bottom = getDenominator() * other.getDenominator();
        // return Fraction(new_top, new_bottom);
    }

    Fraction operator+(float number, const Fraction &other)
    {
        Fraction to_frac(number);
        return Fraction(to_frac + other);

        // float result = number + static_cast<float>(other.getNumerator()) / other.getDenominator();
        // return Fraction(result);
    }

    Fraction operator-(float number, const Fraction &other)
    {
        float result = number - static_cast<float>(other.getNumerator()) / other.getDenominator();
        return Fraction(result);
    }

    Fraction operator/(float number, const Fraction &other)
    {
        if (other.getNumerator() == 0)
        {
            throw invalid_argument("Divison by zero!");
        }
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
            throw invalid_argument("Divison by zero!");
        }
        Fraction to_frac(number);
        return Fraction(other / to_frac);
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

    std::ostream &operator<<(std::ostream &output, const Fraction &other)
    {
        output << other.getNumerator() << "/" << other.getDenominator();
        return output;
    }

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

    /**
     * @brief function to check overflow
     * @return true if there is overflow, false otherwise
     */
    bool Fraction::checkOverflow(int a, int b, int c) const
    {
        // no overflow when top or bottom is zero
        if (a == 0 || b == 0)
        {
            return false;
        }
        // overflow when the result is INT_MAX or INT_MIN
        if (c == numeric_limits<int>::max() || c == numeric_limits<int>::min())
        {
            return true;
        }

        // overflow in case of '*' operator
        if (a != c / b)
        {
            return true;
        }

        // overflow in case of '/' operator
        if (b != c / a)
        {
            return true;
        }

        return false;
    }

    int Fraction::lcm(int a, int b) const
    {
        return abs(a * b) / __gcd(a, b);
    }

    void Fraction::simplify()
    {
        if (getDenominator() < 0)
        {
            setNumerator(-getNumerator());
            setDenominator(-getDenominator());
        }

        int gcd = abs(__gcd(getNumerator(), getDenominator()));
        // int gcd = __gcd(abs(getNumerator()), getDenominator());
        setNumerator(getNumerator() / gcd);
        setDenominator(getDenominator() / gcd);
    }

    int Fraction::roundFraction(double value, int precision)
    {
        double factor = pow(10.0, precision);
        return static_cast<int>(round(value * factor)) / factor;
    }

}