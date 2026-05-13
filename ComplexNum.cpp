#include "ComplexNum.hpp"

ComplexNum& ComplexNum::operator+=(const ComplexNum& other)
{
    real += other.real;
    imag += other.imag;

    return *this;
}

ComplexNum& ComplexNum::operator-=(const ComplexNum& other)
{
    real -= other.real;
    imag -= other.imag;

    return *this;
}

ComplexNum& ComplexNum::operator*=(const ComplexNum& other)
{
    real = real * other .real - imag * other.imag;
    imag = real * other.imag + imag * other.real;

    return *this;
}

ComplexNum& ComplexNum::operator/=(const ComplexNum& other)
{
    real = (real * other.real + imag * other.imag) / (other.real * other.real + other.imag * other.imag);
    imag = (imag * other.real - real * other.imag) / (other.real * other.real + other.imag * other.imag);

    return *this;
}

bool ComplexNum::operator==(const ComplexNum& other) const
{
    return (real == other.real && imag == other.imag);
}

double ComplexNum::operator()() const
{
    return sqrt(real * real + imag * imag);
}
