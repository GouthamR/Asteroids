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

void CircleObject::collision2D(double m1, double m2, double R,
                               double x1, double y1, double x2, double y2,
                               double& vx1, double& vy1, double& vx2, double& vy2)
{

     double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;


     m21=m2/m1;
     x21=x2-x1;
     y21=y2-y1;
     vx21=vx2-vx1;
     vy21=vy2-vy1;

     vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
     vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;


//     *** return old velocities if balls are not approaching ***
     if ( (vx21*x21 + vy21*y21) >= 0) return;


//     *** I have inserted the following statements to avoid a zero divide;
//         (for single precision calculations,
//          1.0E-12 should be replaced by a larger value). **************

     fy21=1.0E-12*fabs(y21);
     if ( fabs(x21)<fy21 ) {
                 if (x21<0) { sign=-1; } else { sign=1;}
                 x21=fy21*sign;
      }

//     ***  update velocities ***
     a=y21/x21;
     dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
     vx2=vx2+dvx2;
     vy2=vy2+a*dvx2;
     vx1=vx1-m21*dvx2;
     vy1=vy1-a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
     vx1=(vx1-vx_cm)*R + vx_cm;
     vy1=(vy1-vy_cm)*R + vy_cm;
     vx2=(vx2-vx_cm)*R + vx_cm;
     vy2=(vy2-vy_cm)*R + vy_cm;

     return;
}

CircleObject::CircleObject(const double &xPos, const double &yPos, const double &radius)
    : Object(xPos, yPos)
    , radius(radius)
{}

double CircleObject::getRadius() const
{
    return radius;
}

void CircleObject::handleCircleCollision(double thisMass, double otherMass, CircleObject *other)
{
    // TODO: redundant from isColliding? Remove isColliding-similar code altogether, assuming that it is colliding.
    double xDist = this->getX() - other->getX();
    double yDist = this->getY() - other->getY();
    double angle = atan2(yDist, xDist); // from other to this
    double radiiSum = this->getRadius() + other->getRadius();
    if(sqrt(pow(xDist,2) + pow(yDist,2)) < radiiSum)
    {
        double xIntersect = radiiSum*cos(angle) - xDist;
        double yIntersect = radiiSum*sin(angle) - yDist;
        this->setX(this->getX() + xIntersect/2);
        other->setX(other->getX() - xIntersect/2);
        this->setY(this->getY() + yIntersect/2);
        other->setY(other->getY() - yIntersect/2);

        double vXO = other->getVelocity().getX();
        double vYO = other->getVelocity().getY();
        double vXT = this->getVelocity().getX();
        double vYT = this->getVelocity().getY();

        collision2D(otherMass,thisMass,1,
                    other->getX(),other->getY(),
                    this->getX(),this->getY(),
                    vXO,vYO,
                    vXT,vYT);

        other->setVelocityXY(round(vXO),round(vYO));
        this->setVelocityXY(round(vXT),round(vYT));
    }
}

void CircleObject::handleCircleCollision(CircleObject *other)
{
    handleCircleCollision(this->getRadius(),other->getRadius(),other);
}

bool CircleObject::isCircleColliding(CircleObject *other)
{
    return this->getIntersect(other) > 0;
}

double CircleObject::getWidth()
{
    return radius * 2;
}

double CircleObject::getHeight()
{
    return getWidth();
}
