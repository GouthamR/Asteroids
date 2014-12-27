#ifndef OBJECT_H
#define OBJECT_H

#include <iosfwd>
#include "vector.h"

class CircleObject;
class Asteroid;
class Spaceship;
class Ufo;

class Object
{
private:
    double xPos, yPos;
    Phys::Vector velocity;
public:
    Object(const double &xPos, const double &yPos);
    virtual ~Object();
    // replace following with macro:
    virtual void handleCollision(Object *second) = 0;
    virtual void handleCollision(Asteroid *first) = 0;
    virtual void handleCollision(Spaceship *first) = 0;
    virtual void handleCollision(Ufo *first) = 0;
    virtual bool isColliding(Object *second) = 0;
    virtual bool isColliding(Asteroid *first) = 0;
    virtual bool isColliding(Spaceship *first) = 0;
    virtual bool isColliding(Ufo *first) = 0;
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
