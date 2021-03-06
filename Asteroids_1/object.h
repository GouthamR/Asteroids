#ifndef OBJECT_H
#define OBJECT_H

#include <iosfwd>
#include "vector.h"

#include "ObjectClassDeclarationMacro.h"

class Object
{
private:
    double xPos, yPos;
    bool toDelete;
    Phys::Vector velocity;
public:
    Object(const double &xPos, const double &yPos);
    virtual ~Object();
    #include "ObjectDispatchFnsMacro.h"
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
    void setVelocity(const Phys::Vector &newVelocity);
    void markToDelete();
    bool isToDelete();
    virtual void update(const double &time);
};

#endif // OBJECT_H
