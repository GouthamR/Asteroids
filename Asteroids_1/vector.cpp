#include "vector.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>   // srand, rand
#include <time.h>

using namespace Phys;

const double Vector::THETA_MIN = 0;
const double Vector::THETA_MAX = 2*M_PI;
const double Vector::THETA_QUARTER = Vector::THETA_MAX/4;
const double Vector::THETA_RIGHT = Vector::THETA_MIN;
const double Vector::THETA_UP = Vector::THETA_QUARTER;
const double Vector::THETA_LEFT = Vector::THETA_QUARTER*2;
const double Vector::THETA_DOWN = Vector::THETA_QUARTER*3;

double Vector::getRandom(const double &min, const double &max)
{
    srand(time(NULL));
    double fraction = (double)rand() / RAND_MAX;
    return fraction * (max - min) + min;
}

Vector::Vector()
    : x(0)
    , y(0)
{}

Vector::Vector(const double &x, const double &y)
    : x(x)
    , y(y)
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

Vector &Vector::operator +=(const Vector &other)
{
    this->setX(this->getX() + other.getX());
    this->setY(this->getY() + other.getY());

    return *this;
}

inline double Vector::getX() const
{
    return x;
}

inline double Vector::getY() const
{
    return y;
}

inline double Vector::getR() const
{
    return sqrt(pow(x,2) + pow(y,2));
}

inline double Vector::getTheta() const
{
    return atan2(y,x);
}

void Vector::setX(const double &x)
{
    this->x = x;
}

void Vector::setY(const double &y)
{
    this->y = y;
}

void Vector::setR(const double &r)
{
   double oldR = getR();

   if(oldR == 0)
   {
       double theta = getTheta();
       x = r*cos(theta);
       y = r*sin(theta);
   }
   else
   {
       x *= r/oldR;
       y *= r/oldR;
   }
}

void Vector::setTheta(const double &theta)
{
    double rangedTheta = fmod(theta, THETA_MAX); // range: [0, THETA,MAX)

    double r = getR();

    if(r == 0)
        std::cout << "UNRELIABLE OPERATION: setTheta on 0 vector." << std::endl;

    if(fmod(rangedTheta, THETA_QUARTER) == 0) // if quadrantal angle
    {
        if(rangedTheta == 0) // right
        {
            x = r;
            y = 0;
        }
        else if(rangedTheta == THETA_QUARTER) // up
        {
            x = 0;
            y = r;
        }
        else if(rangedTheta == THETA_QUARTER * 2) // left
        {
            x = -r;
            y = 0;
        }
        else // down
        {
            x = 0;
            y = -r;
        }
    }
    else
    {
        x = r*cos(rangedTheta);
        y = r*sin(rangedTheta);
    }
}

void Vector::roundTo0()
{
    // rounds to 0 if less than EPSILON, to prevent movements from values that should be 0
    const double EPSILON = 0.5;

    if(abs(getX()) < EPSILON)
        setX(0);
    if(abs(getY()) < EPSILON)
        setY(0);
}

void Vector::roundToInt()
{
    setX(round(getX()));
    setY(round(getY()));
}

std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    os << "Vector XY: (" << vector.getX() << ", " << vector.getY() << ")";
    return os;	
}
