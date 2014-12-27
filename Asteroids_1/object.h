#ifndef OBJECT_H
#define OBJECT_H

#include <iosfwd>

namespace Phys { class Vector; }
class CircleObject;

class Object
{
private:
    int xPos, yPos;
    Phys::Vector *velocity;
    Phys::Vector *getDistanceVector(Object *other);
public:
    Object(const int &xPos, const int &yPos);
    ~Object();
    void moveBy(const Phys::Vector *moveVector);
    double distanceTo(Object *other);
    double angleTo(Object *other);
    void moveBackward(const int &distance);
    double getVelocityR();
    virtual void handleCollision(Object *other) = 0;
    virtual void handleCollision(CircleObject *other) = 0;
    virtual bool isColliding(Object *other) = 0;
    virtual bool isColliding(CircleObject *other) = 0;
    friend std::ostream &operator<<(std::ostream &os, const Object &object);
};

#endif // OBJECT_H
