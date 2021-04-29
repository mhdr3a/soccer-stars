#include "Vector2D.hpp"
using namespace std;

Vector2D::Vector2D(double xi, double yi)
{
    x = xi;
    y = yi;
}

double Vector2D::operator%(const Vector2D& b)
{
    return (this->x) * (b.x) + (this->y) * (b.y);
}

Vector2D Vector2D::operator*(const Vector2D& b)
{
    Vector2D v;
    v.x = (this->x) * b.x;
    v.y = (this->y) * b.y;
    return v;
}

Vector2D Vector2D::operator*(const double& c)
{
    Vector2D v;
    v.x = (this->x) * c;
    v.y = (this->y) * c;
    return v;
}

void Vector2D::operator+=(const double& c)
{
    this->x += c;
    this->y += c;
}

Vector2D Vector2D::operator-(const Vector2D& b)
{
    Vector2D v;
    v.x = (this->x) - (b.x);
    v.y = (this->y) - (b.y);
    return v;
}

Vector2D Vector2D::operator-(const double& b)
{
    Vector2D v;
    v.x = (this->x) - b;
    v.y = (this->y) - b;
    return v;
}

void Vector2D::operator+=(const Vector2D& b)
{
    this->x += (b.x);
    this->y += (b.y);
}

bool Vector2D::operator==(const Vector2D& b)
{
    return (this->x == b.x) && (this->y == b.y);
}

Vector2D Vector2D::operator>(const Vector2D& b)
{
    bool z1 = this->x > b.x;
    bool z2 = this->y > b.y;
    return Vector2D((double) z1, (double) z2);
}

Vector2D Vector2D::operator<(const Vector2D& b)
{
    bool z1 = this->x < b.x;
    bool z2 = this->y < b.y;
    return Vector2D((double) z1, (double) z2);
}

Vector2D Vector2D::sgn()
{
    return (*this > Vector2D(0, 0)) - (*this < Vector2D(0, 0));
}

Point Vector2D::to_point()
{
    Point p;
    p.x = (int) x;
    p.y = (int) y;
    return p;
}

string Vector2D::vector2str()
{
    return "(" + to_string(x) + ", " + to_string(y) + ")";
}

double Vector2D::length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}