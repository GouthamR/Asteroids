#include "object.h"

#include <iostream>

#include "vector.h"

Object::Object(const double &xPos, const double &yPos)
    : xPos(xPos)
    , yPos(yPos)
    , toDelete(false)
    , velocity()
{}

Object::~Object()
{
    std::cout << "Destructing Object." << std::endl;
}

double Object::getX() const
{
    return xPos;
}

void Object::setX(const double &x)
{
    xPos = x;
}

double Object::getY() const
{
    return yPos;
}

void Object::setY(const double &y)
{
    yPos = y;
}

Phys::Vector Object::getVelocity() const
{
    return velocity;
}

void Object::setVelocityXY(const double &x, const double &y)
{
    velocity.setX(x);
    velocity.setY(y);
}

void Object::setVelocityPolar(const double &speed, const double &angle)
{
    velocity.setR(speed);
    velocity.setTheta(angle);
}

void Object::setVelocity(const Phys::Vector newVelocity)
{
    velocity = newVelocity;
}

void Object::markToDelete()
{
    toDelete = true;
}

bool Object::isToDelete()
{
    return toDelete;
}

void Object::update(const double &time)
{
    // do nothing by default.
}

std::ostream &operator<<(std::ostream &os, const Object &object)
{
    os << "Object - XY: (" << object.xPos << ", " << object.yPos << ")";
    return os;
}
