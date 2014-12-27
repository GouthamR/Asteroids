#include "circleobject.h"

#include <iostream>
#include <cmath>
#include "vector.h"

double CircleObject::getIntersect(CircleObject *other)
{
    double xDist = this->getX() - other->getX();
    double yDist = this->getY() - other->getY();
    double distance = sqrt(pow(xDist, 2) + pow(yDist, 2));
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
//    double intersect = this->getIntersect(other);
//    std::cout << "intersect = " << intersect << std::endl;
//    if(intersect <= 0)
//        return;
//    //else, is colliding:
//    std::cout << "handling circle collision" << std::endl;

//    double moveDist = intersect/2 + 1; // for each circle. adding 1 to make sure it moves out of collision.

////    if(this->getVelocityR() == 0 && other->getVelocityR() == 0)
//    if(this->getVelocity().getR() == 0 && other->getVelocity().getR() == 0)
//    {
//        Phys::Vector *otherBack = Phys::Vector::createPolar(moveDist, atan2(other->getY() - this->getY(), other->getX() - this->getX()));
//        other->setX(other->getX() + otherBack->getX());
//        other->setY(other->getY() + otherBack->getY());
//        Phys::Vector *thisBack = otherBack->getReversed();
//        this->moveBy(thisBack);
//        delete thisBack;
//        delete otherBack;
//    }
//    else // if at least one is moving
//    {
//        double increment = 0;
//        do
//        {
//            this->moveBackward(moveDist + increment);
//            other->moveBackward(moveDist + increment);
//            ++increment;
//        }
//        while(this->getIntersect(other) > 0);
//    }

//    this->setVelocity(0,0);
//    other->setVelocity(0,0);

    std::cout << "SHOULD NOT BE HERE" << std::endl;
}

bool CircleObject::isColliding(Object *other)
{
    return other->isColliding(this);
}

bool CircleObject::isColliding(CircleObject *other)
{
    return this->getIntersect(other) > 0;
}
