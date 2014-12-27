#ifndef OBJECT_H
#define OBJECT_H

#include <iosfwd>
#include "vector.h"

class CircleObject;
class DrawableAsteroid;
class DrawableSpaceship;

class Object
{
private:
    double xPos, yPos;
    Phys::Vector velocity;
public:
    Object(const double &xPos, const double &yPos);
    virtual ~Object();
    virtual void handleCollision(Object *second) = 0;
    virtual void handleCollision(DrawableAsteroid *first) = 0;
    virtual void handleCollision(DrawableSpaceship *first) = 0;
    virtual bool isColliding(Object *second) = 0;
    virtual bool isColliding(DrawableAsteroid *first) = 0;
    virtual bool isColliding(DrawableSpaceship *first) = 0;
    virtual double getWidth() = 0;
    virtual double getHeight() = 0;
    double getX() const;
    void setX(const double &x);
    double getY() const;
    void setY(const double &y);
    friend std::ostream &operator<<(std::ostream &os, const Object &object);
    Phys::Vector getVelocity() const;
    void setVelocityXY(const double &x, const double &y);
    void setVelocityPolar(const double &speed, const double &angle);
    void setVelocity(const Phys::Vector newVelocity);
};

#endif // OBJECT_H
