#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "object.h"

class CircleObject : public Object
{
private:
    int radius;
    double getIntersect(CircleObject *other);
public:
    CircleObject(const int &xPos, const int &yPos, const int &radius);
    int getRadius() const { return radius; }
    virtual void handleCollision(Object *other);
    virtual void handleCollision(CircleObject *other);
    virtual bool isColliding(Object *other);
    virtual bool isColliding(CircleObject *other);
};

#endif // CIRCLEOBJECT_H
