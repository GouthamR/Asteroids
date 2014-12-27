#include "object.h"

#include <iostream>

#include "vector.h"

Phys::Vector *Object::getDistanceVector(Object *other)
{
    return new Phys::Vector(other->xPos - this->xPos, other->yPos - this->yPos);
}

Object::Object(const int &xPos, const int &yPos)
    : xPos(xPos)
    , yPos(yPos)
    , velocity(new Phys::Vector())
{}

Object::~Object()
{
    delete velocity;
}

void Object::moveBy(const Phys::Vector *moveVector)
{
    xPos += moveVector->getX();
    yPos += moveVector->getY();
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


std::ostream &operator<<(std::ostream &os, const Object &object)
{
    os << "Object - XY: (" << object.xPos << ", " << object.yPos << ")";
    return os;
}
