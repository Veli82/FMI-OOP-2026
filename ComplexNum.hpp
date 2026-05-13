#pragma once
#include <iostream>

class ComplexNum {
public:
    ComplexNum() = default;
    ComplexNum& operator+=(const ComplexNum& other);
    ComplexNum& operator-=(const ComplexNum& other);
    ComplexNum& operator*=(const ComplexNum& other);
    ComplexNum& operator/=(const ComplexNum& other);
    bool operator==(const ComplexNum& other) const;
    double operator()() const;


    friend ComplexNum operator+(ComplexNum& lhs, const ComplexNum& rhs);
    friend ComplexNum operator-(ComplexNum& lhs, const ComplexNum& rhs);
    friend ComplexNum operator*(ComplexNum& lhs, const ComplexNum& rhs);
    friend ComplexNum operator/(ComplexNum& lhs, const ComplexNum& rhs);
    friend std::ostream& operator<<(std::ostream& out, const ComplexNum& rhs);
    friend std::istream& operator>>(std::istream& in, ComplexNum& rhs);
    friend bool operator!=(const ComplexNum& lhs, const ComplexNum& rhs);

private:
    double real = 0.0, imag = 0.0;
};

inline ComplexNum operator+(ComplexNum& lhs, const ComplexNum& rhs)
{
    lhs += rhs;
    return lhs;
}

inline ComplexNum operator-(ComplexNum& lhs, const ComplexNum& rhs)
{
    lhs -= rhs;
    return lhs;
}

inline ComplexNum operator*(ComplexNum& lhs, const ComplexNum& rhs)
{
    lhs *= rhs;
    return lhs;
}

inline ComplexNum operator/(ComplexNum& lhs, const ComplexNum& rhs)
{
    lhs /= rhs;
    return lhs;
}

inline std::ostream& operator<<(std::ostream& out, const ComplexNum& rhs)
{
    out << rhs.real << "+" << rhs.imag << "i";
    return out;
}

inline std::istream& operator>>(std::istream& in, ComplexNum& rhs)
{
    in >> rhs.real >> rhs.imag;
    return in;
}

inline bool operator!=(const ComplexNum& lhs, const ComplexNum& rhs)
{
    return !(lhs == rhs);
}

