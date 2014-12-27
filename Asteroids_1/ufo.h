#ifndef UFO_H
#define UFO_H

#include "circleobject.h"
#include "drawableimageobject.h"

class DrawableObject;

class Ufo : public DrawableImageObject, public CircleObject
{
private:
    // all time values in seconds
    const static double SPEED, BULLET_TIME;
    double currentBulletTime;
    void (*addToWorld)(DrawableObject *drawable);
    void shootBullet();
public:
    Ufo(const double &xPos, const double &yPos, const double &radius,
        const double &angle, const double &bulletStartTime,
        void (*addToWorld)(DrawableObject *drawable),sf::Texture *texture);
    void addTime(const double &time);
    #include "DispatchFnsMacro.h"
};
#endif // UFO_H
