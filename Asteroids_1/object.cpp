#include "object.h"

#include <iostream>

#include "vector.h"

Phys::Vector *Object::getDistanceVector(Object *other)
{
    return new Phys::Vector(other->xPos - this->xPos, other->yPos - this->yPos);
}

//void Object::temp_velocityIncrement(const double &increment, const double &theta)
//{
//    Phys::Vector *incrementVelocity = Phys::Vector::createPolar(increment, theta);
//    *velocity += *incrementVelocity;
//    delete incrementVelocity;
//    velocity->roundTo0();
//}

Object::Object(const int &xPos, const int &yPos)
    : xPos(xPos)
    , yPos(yPos)
    , velocity(new Phys::Vector())
{}

Object::~Object()
{
    std::cout << "Destruct Object" << std::endl;
    delete velocity;
}

void Object::moveBy(const Phys::Vector *moveVector)
{
    xPos += moveVector->getX();
    yPos += moveVector->getY();
}

void Object::moveByVelocity(float secondsElapsed)
{
    Phys::Vector *dist = Phys::Vector::createPolar(velocity->getR()*secondsElapsed, velocity->getTheta());
    moveBy(dist);
    delete dist;
}

void Object::incrementVelocity(const double &increment, const double &theta)
{
    Phys::Vector *incrementVelocity = Phys::Vector::createPolar(increment, theta);
    *velocity += *incrementVelocity;
    delete incrementVelocity;
    velocity->roundTo0();
}

double Object::distanceTo(Object *other)
{
    Phys::Vector *distVec = this->getDistanceVector(other);
    double dist = distVec->getR();
    delete distVec;
    return dist;
}

double Object::angleTo(Object *other)
{
    Phys::Vector *distVec = getDistanceVector(other);
    double angle = distVec->getTheta();
    delete distVec;
    return angle;
}

void Object::moveBackward(const int &distance)
{
    Phys::Vector* backwardVelocity = velocity->getReversed();
    backwardVelocity->setR(distance);

    moveBy(backwardVelocity);

    delete backwardVelocity;
}

double Object::getVelocityR()
{
    return velocity->getR();
}

void Object::setVelocityTo0()
{
    velocity->setR(0);
}


std::ostream &operator<<(std::ostream &os, const Object &object)
{
    os << "Object - XY: (" << object.xPos << ", " << object.yPos << ")";
    return os;
}
