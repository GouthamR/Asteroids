#ifndef UFO_H
#define UFO_H

#include "circleobject.h"
#include "drawableimageobject.h"

class DrawableObject;
class Game;
class World;

class Ufo : public DrawableImageObject, public CircleObject
{
private:
    // all time values in seconds
    const static double SPEED, BULLET_TIME;
    double currentBulletTime;
    Game *game;
    void shootBullet();
    World *world;
public:
    Ufo(const double &xPos, const double &yPos, const double &radius,
        const double &angle, const double &bulletStartTime,
        Game *game,
        World *world,
        std::shared_ptr<sf::Texture> texture);
    virtual void update(const double &time);
    #include "DispatchFnsMacro.h"
};
#endif // UFO_H
