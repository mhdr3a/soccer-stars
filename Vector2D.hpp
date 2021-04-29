#ifndef __VECTOR2D_HPP__
#define __VECTOR2D_HPP__

#include <iostream>
#include "RSDL/src/rsdl.hpp"

class Vector2D
{
public:
    Vector2D(double xi, double yi);
    Vector2D() = default;
    double operator%(const Vector2D& b);
    Vector2D operator*(const Vector2D& b);
    Vector2D operator*(const double& c);
    void operator+=(const double& c);
    Vector2D operator-(const Vector2D& b);
    Vector2D operator-(const double& b);
    void operator+=(const Vector2D& b);
    bool operator==(const Vector2D& b);
    Vector2D operator>(const Vector2D& b);
    Vector2D operator<(const Vector2D& b);
    Vector2D sgn();
    Point to_point();
    std::string vector2str();
    double length();
    double x, y;
};

#endif