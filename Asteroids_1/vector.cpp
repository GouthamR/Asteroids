#include "vector.h"

#include <cmath>
#include <iostream>

using namespace Phys;

const double pi = 3.14159;
const double Vector::THETA_MIN = 0;
const double Vector::THETA_MAX = 2*pi;
const double Vector::THETA_QUARTER = Vector::THETA_MAX/4;
const double Vector::THETA_RIGHT = Vector::THETA_MIN;
const double Vector::THETA_UP = Vector::THETA_QUARTER;
const double Vector::THETA_LEFT = Vector::THETA_QUARTER*2;
const double Vector::THETA_DOWN = Vector::THETA_QUARTER*3;

double Vector::getR(const double &x, const double &y)
{
    return sqrt(pow(x,2) + pow(y,2));
}

double Vector::getT(const double &x, const double &y)
{
    return atan2(y,x);
}

Vector::Vector()
    : r(0)
    , t(0)
{}

Vector::Vector(const double &x, const double &y)
    : r(getR(x,y))
    , t(getT(x,y))
{}

Vector* Vector::createPolar(const double &magnitude, const double &angle)
{
    Vector *vec = new Vector();
    vec->setR(magnitude);
    vec->setTheta(angle);
    return vec;
}

Vector &Vector::operator +=(const Vector &other)
{
    this->setX(this->getX() + other.getX());
    this->setY(this->getY() + other.getY());

    return *this;
}

inline double Vector::getX() const
{
    return r*cos(t);
}

inline double Vector::getY() const
{
    return r*sin(t);
}

double Vector::getR() const // can't inline this.
{
    return r;
}

double Vector::getTheta() const
{
    return t;
}

void Vector::setX(const double &x)
{
    double y = getY();
    r = getR(x,y);
    t = getT(x,y);
}

void Vector::setY(const double &y)
{
    double x = getX();
    r = getR(x,y);
    t = getT(x,y);
}

void Vector::setR(const double &r)
{
    this->r = r;
}

void Vector::setTheta(const double &theta)
{
    this->t = fmod(theta, THETA_MAX); // range: [0, THETA,MAX)
}

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    os << "Vector XY: (" << vector.getX() << ", " << vector.getY() << ")";
    return os;	
}
