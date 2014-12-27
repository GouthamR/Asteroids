#include "vector.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>   // srand, rand
#include <time.h>

using namespace Phys;

const double Vector::THETA_MIN = 0;
const double Vector::THETA_MAX = 2*M_PI;

inline double Vector::getR(const int &x, const int &y)
{
    return sqrt(x*x + y*y);
}

inline double Vector::getTheta(const int &x, const int &y)
{
    return atan2(y,x);
}

double Vector::getRandom(const double &min, const double &max)
{
    srand(time(NULL));
    double fraction = (double)rand() / RAND_MAX;
    return fraction * (max - min) + min;
}

Vector::Vector()
    : x(0)
    , y(0)
    , r(0)
    , theta(0)
{}

Vector::Vector(const double &x, const double &y)
    : x(x)
    , y(y)
    , r(getR(x,y))
    , theta(getTheta(x, y))
{}

Vector* Vector::createPolar(const double &r, const double &theta)
{
    return new Vector(r*cos(theta),r*sin(theta));
}

Vector *Vector::createRandomAngle(const double &r)
{
    return createPolar(r, getRandom(THETA_MIN, THETA_MAX));
}

Vector *Vector::getReversed()
{
    return new Vector(-x, -y);
}

void Vector::setX(const double &x)
{
    this->x = x;
    r = getR(x,y);
    theta = getTheta(x,y);
}

void Vector::setY(const double &y)
{
    this->y = y;
    r = getR(x,y);
    theta = getTheta(x,y);
}

void Vector::setR(const double &r)
{
	double oldR = this->r;
    this->r = r;
    x *= r/oldR;
    y *= r/oldR;
}

void Vector::setTheta(const double &theta)
{
    this->theta = theta;
    x = r*cos(theta);
    y = r*sin(theta);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    os << "Vector - XY: (" << vector.getX() << ", " << vector.getY() << ") OR RT:("
		<< vector.getR() << ", " << vector.getTheta() << ")";
    return os;	
}
