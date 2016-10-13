#ifndef UFO_H
#define UFO_H

#include "circleobject.h"
#include "drawableimageobject.h"
#include "bulletadder.h"

class DrawableObject;
class World;

class Ufo : public DrawableImageObject, public CircleObject
{
private:
    // all time values in seconds
    const static double SPEED, BULLET_TIME;
    double currentBulletTime;
    BulletAdder bulletAdder;
    void shootBullet();
    World *world;
public:
    Ufo(const double &xPos, const double &yPos, const double &radius,
        const double &angle, const double &bulletStartTime,
        BulletAdder &bulletAdder, World *world,
        std::shared_ptr<sf::Texture> texture);
    virtual void update(const double &time);
    #include "DispatchFnsMacro.h"
};
#endif // UFO_H
