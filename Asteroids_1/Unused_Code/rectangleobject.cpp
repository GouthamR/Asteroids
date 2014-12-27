#include "rectangleobject.h"

#include "circleobject.h"

#include <iostream>

RectangleObject::RectangleObject(const int &xPos, const int &yPos, const int &width, const int &height)
    : Object(xPos, yPos)
    , width(width)
    , height(height)
{}

void RectangleObject::handleCollision(CircleObject *other)
{
    other->handleCollision(this);
}

void RectangleObject::handleCollision(RectangleObject *other)
{
    std::cout << "rect.handle(rect)" << std::endl; // note: remove iostream inclusion when removing this.
}
