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
        Fraction(double number);
        Fraction();

        // Copy Constructor
        Fraction(const Fraction &other);

        // De-Constructor
        ~Fraction() = default;

        // Move Constructor and move assigment operator
        // So the clang-tidy would work
        Fraction(Fraction &&other) noexcept;

        // Getters
        int getTop() const;
        int getBottom() const;

        // Assigment operator
        Fraction &operator=(const Fraction &other);

        Fraction operator-() const;
        Fraction operator+() const;
        Fraction operator++();    // pre-increment
        Fraction operator++(int); // post-increment
        Fraction operator--();    // pre-decrement
        Fraction operator--(int); // post-decrement

        // Binary operators
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;

        // Binary operators using `friend` method
        // This will allow this functions to access the private methods of our class
        friend Fraction operator+(const Fraction &other, const double &number);
        friend Fraction operator-(const Fraction &other, const double &number);
        friend Fraction operator/(const Fraction &other, const double &number);
        friend Fraction operator*(const Fraction &other, const double &number);

        friend Fraction operator+(const Fraction &other, const int &number);
        friend Fraction operator-(const Fraction &other, const int &number);
        friend Fraction operator/(const Fraction &other, const int &number);
        friend Fraction operator*(const Fraction &other, const int &number);

        friend Fraction operator+(const double &number, const Fraction &other);
        friend Fraction operator-(const double &number, const Fraction &other);
        friend Fraction operator/(const double &number, const Fraction &other);
        friend Fraction operator*(const double &number, const Fraction &other);

        // Comparison operators
        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        bool operator==(const double &number) const;
        bool operator!=(const double &number) const;
        bool operator<(const double &number) const;
        bool operator>(const double &number) const;
        bool operator<=(const double &number) const;
        bool operator>=(const double &number) const;

        // I/O operators
        friend std::ostream &operator<<(std::ostream &out, const Fraction &other);

        // Converting to double
        operator double() const;

        // Convetring to int (maybe will not be in use)
        operator int() const;

        /**
         * @brief checking if the top and bottom does not have any common divider
         */
        void simplify();
    };
}

#endif