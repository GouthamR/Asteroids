#include "circleobject.h"

#include <iostream>
#include <cmath>
#include "vector.h"

double CircleObject::getIntersect(CircleObject *other)
{
    double distance = this->distanceTo(other);
    double radiusSum = this->getRadius() + other->getRadius();
    return radiusSum - distance;
}

CircleObject::CircleObject(const int &xPos, const int &yPos, const int &radius)
    : Object(xPos, yPos)
    , radius(radius)
{}

void CircleObject::handleCollision(Object *other)
{
    other->handleCollision(this);
}

void CircleObject::handleCollision(CircleObject *other)
{
    double intersect = this->getIntersect(other);
    if(intersect <= 0)
        return;
    //else, is colliding:

    double moveDist = intersect/2 + 1; // for each circle. adding 1 to make sure it moves out of collision.

    if(this->getVelocityR() == 0 && other->getVelocityR() == 0)
    {
        Phys::Vector *otherBack = Phys::Vector::createPolar(moveDist, this->angleTo(other));
        other->moveBy(otherBack);
        Phys::Vector *thisBack = otherBack->getReversed();
        this->moveBy(thisBack);
        delete thisBack;
        delete otherBack;
    }
    else // if at least one is moving
    {
        do
        {
            this->moveBackward(moveDist);
            other->moveBackward(moveDist);
        }
        while(this->getIntersect(other) > 0);
    }
}

bool CircleObject::isColliding(Object *other)
{
    return other->isColliding(this);
}

bool CircleObject::isColliding(CircleObject *other)
{
    return this->getIntersect(other) > 0;
}
