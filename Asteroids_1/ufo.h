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
    void (*addBullet)(const double &xPos, const double &yPos);
    void shootBullet();
public:
    Ufo(const double &xPos, const double &yPos, const double &radius,
        const double &angle, const double &bulletStartTime,
        void (*addBullet)(const double &xPos, const double &yPos),
        std::shared_ptr<sf::Texture> texture);
    void addTime(const double &time);
    #include "DispatchFnsMacro.h"
};
#endif // UFO_H
