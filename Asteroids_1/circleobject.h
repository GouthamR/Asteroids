#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "object.h"

class CircleObject : public virtual Object
{
private:
    double radius;
    double getIntersect(CircleObject *other);
    //******************************************************************************
    //  Source: http://www.plasmaphysics.org.uk/programs/coll2d_cpp.htm
    //  Simplified Version
    //  The advantage of the 'remote' collision detection in the program above is
    //  that one does not have to continuously track the balls to detect a collision.
    //  The program needs only to be called once for any two balls unless their
    //  velocity changes. However, if somebody wants to use a separate collision
    //  detection routine for whatever reason, below is a simplified version of the
    //  code which just calculates the new velocities, assuming the balls are already
    //  touching (this condition is important as otherwise the results will be incorrect)
    //****************************************************************************
    void collision2D(double m1, double m2, double R,
                     double x1, double y1, double x2, double y2,
                     double& vx1, double& vy1, double& vx2, double& vy2);
public:
    CircleObject(const double &xPos, const double &yPos, const double &radius);
    double getRadius() const;
    virtual void handleCircleCollision(CircleObject *other);
    virtual bool isCircleColliding(CircleObject *other);
    virtual double getWidth();
    virtual double getHeight();
};

#endif // CIRCLEOBJECT_H
