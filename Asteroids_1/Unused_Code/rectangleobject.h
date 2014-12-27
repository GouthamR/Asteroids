#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H

#include "object.h"

class CircleObject;

class RectangleObject : public Object
{
private:
    int width, height;
public:
    RectangleObject(const int &xPos, const int &yPos, const int &width, const int &height);
    virtual void handleCollision(Object *other) { other->handleCollision(this); }
    virtual void handleCollision(CircleObject *other);
    virtual void handleCollision(RectangleObject *other);
};

#endif // RECTANGLEOBJECT_H
