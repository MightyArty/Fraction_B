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
            throw invalid_argument("Cannot divide by zero!");
        }
        this->bottom = bottom;
    }

}