#include "Fraction.hpp"
#include <string>
#include <cmath>
#include <iostream>

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
        this->top = top;
        if (bottom == 0)
        {
            throw invalid_argument("The bottom part of the fraction cannot be zero!");
        }
        this->bottom = bottom;
        simplify();
    }

    /**
     * @brief constructor for Fraction that getting one number
     * @return a new fraction from the given double
     */
    Fraction::Fraction(double number)
    {
        this->top = number * GREAT;
        this->bottom = GREAT;
        simplify();
    }

    /**
     * @brief empty constructor
     */
    Fraction::Fraction()
    {
        top = 0;
        bottom = 1;
    }

    /**
     * @brief Copy constructor
     * @return new Fraction object
     */
    Fraction::Fraction(const Fraction &other)
    {
        this->top = other.top;
        this->bottom = other.bottom;
    }

    int Fraction::getTop() const
    {
        return top;
    }

    int Fraction::getBottom() const
    {
        return bottom;
    }

    /**
     * @brief assigment operator
     * @param other the other fraction object
     * @return new Fraction object
     */
    Fraction &Fraction::operator=(const Fraction &other)
    {
        if (this != &other)
        {
            this->top = other.top;
            this->bottom = other.bottom;
        }
        return *this;
    }

    Fraction Fraction::operator-() const
    {
        return Fraction(-top, bottom);
    }

    Fraction Fraction::operator+() const
    {
        return *this;
    }

    /**
     * @brief Pre-Increment
     */
    Fraction Fraction::operator++()
    {
        top = top + bottom;
        simplify();
        return *this;
    }

    /**
     * @brief Post-Increment
     */
    Fraction Fraction::operator++(int)
    {
        Fraction result(*this);
        ++(*this);
        return result;
    }

    /**
     * @brief Pre-Decrement
     */
    Fraction Fraction::operator--()
    {
        top = top - bottom;
        simplify();
        return *this;
    }

    /**
     * @brief Post-Decrement
     */
    Fraction Fraction::operator--(int)
    {
        Fraction result(*this);
        --(*this);
        return result;
    }

    // 1/2 + 2/3 = (1*3+2*2)/6

    /**
     * @brief Adds two given fractions
     * @param other the second fraction
     * @return new fraction after addition
     */
    Fraction Fraction::operator+(const Fraction &other) const
    {
        int new_top = (top * other.bottom) + (other.top * bottom);
        int new_bottom = bottom * other.bottom;
        return Fraction(new_top, new_bottom);
    }

    /**
     * @brief Subtract two given fractions by calling the addition with the (-) sign
     * @param other the second fraction
     * @return new fraction after subtraction
     */
    Fraction Fraction::operator-(const Fraction &other) const
    {
        return (*this) + (-other);
    }

    /**
     * @brief Divide two given fractions by calling the * operator with the opposite fraction
     * @param other the second fraction
     * @return new fraction after dividing
     */
    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.top == 0)
        {
            throw invalid_argument("Can't divide by zero!");
        }
        return (*this) * Fraction(other.bottom, other.top);
    }

    /**
     * @brief Multiply two given fractions
     * @param other the second fraction
     * @return new fraction after multiplying
     */
    Fraction Fraction::operator*(const Fraction &other) const
    {
        int new_top = top * other.top;
        int new_bottom = bottom * other.bottom;
        return Fraction(new_top, new_bottom);
    }

    // -------- Binary operators using Friend method --------
    Fraction operator+(const Fraction &other, const double &number)
    {
        return other + Fraction(number);
    }

    Fraction operator-(const Fraction &other, const double &number)
    {
        return other - Fraction(number);
    }

    Fraction operator/(const Fraction &other, const double &number)
    {
        return other / Fraction(number);
    }

    Fraction operator*(const Fraction &other, const double &number)
    {
        return other * Fraction(number);
    }

    Fraction operator+(const Fraction &other, const int &number)
    {
        return other + Fraction(number);
    }

    Fraction operator-(const Fraction &other, const int &number)
    {
        return other - Fraction(number);
    }

    Fraction operator/(const Fraction &other, const int &number)
    {
        return other / Fraction(number);
    }

    Fraction operator*(const Fraction &other, const int &number)
    {
        return other * Fraction(number);
    }

    Fraction operator+(const double &number, const Fraction &other)
    {
        return Fraction(number) + other;
    }

    Fraction operator-(const double &number, const Fraction &other)
    {
        return Fraction(number) - other;
    }

    Fraction operator/(const double &number, const Fraction &other)
    {
        return Fraction(number) / other;
    }

    Fraction operator*(const double &number, const Fraction &other)
    {
        return Fraction(number) * other;
    }

    // -------- Comparison operators --------
    bool Fraction::operator==(const Fraction &other) const
    {
        return top == other.top && bottom == other.bottom;
    }

    bool Fraction::operator!=(const Fraction &other) const
    {
        return !(*this == other);
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return (top * other.bottom) < (other.top * bottom);
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return (top * other.bottom) > (other.top * bottom);
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return (*this < other) || (*this == other);
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return (*this > other) || (*this == other);
    }

    bool Fraction::operator==(const double &number) const
    {
        return fabs(number - double(*this)) < EPSILON;
    }

    bool Fraction::operator!=(const double &number) const
    {
        return !(*this == number);
    }

    bool Fraction::operator<(const double &number) const
    {
        return double(*this) < number;
    }

    bool Fraction::operator>(const double &number) const
    {
        return double(*this) > number;
    }

    bool Fraction::operator<=(const double &number) const
    {
        return (*this < number) || (*this == number);
    }

    bool Fraction::operator>=(const double &number) const
    {
        return (*this > number) || (*this == number);
    }

    std::ostream &operator<<(std::ostream &out, const Fraction &other)
    {
        out << other.getTop() << "/" << other.getBottom();
        return out;
    }

    /**
     * @brief Converting the fraction object to a double
     * @return new Fraction as a double
     */
    Fraction::operator double() const
    {
        double result = static_cast<double>(top) / static_cast<double>(bottom);
        return result;
    }

    Fraction::operator int() const
    {
        return this->top / this->bottom;
    }

    void Fraction::simplify()
    {
        int gcd = 1;
        for (int i = 1; i <= top && i <= bottom; i++)
        {
            if (top % i == 0 && bottom % i == 0)
            {
                gcd = i;
            }
        }
        top = top / gcd;
        bottom = bottom / gcd;
    }
}