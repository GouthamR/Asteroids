#ifndef UFO_H
#define UFO_H

#include "circleobject.h"
#include "drawableimageobject.h"
#include "bulletadder.h"
#include "boundschecker.h"

class DrawableObject;
class World;

class Ufo : public DrawableImageObject, public CircleObject
{
private:
    // Note: all time values in units of seconds
    const static double SPEED, BULLET_TIME;
    double currentBulletTime;
    BulletAdder bulletAdder;
    void shootBullet();
    BoundsChecker boundsChecker;
public:
    Ufo(const double &xPos, const double &yPos, const double &radius,
        const double &angle, const double &bulletStartTime,
        BulletAdder &bulletAdder, BoundsChecker &boundsChecker,
        std::shared_ptr<sf::Texture> texture);
    virtual void update(const double &time);
    #include "DispatchFnsMacro.h"
};
#endif // UFO_H
