#ifndef ASTEROID_H
#define ASTEROID_H

#include "circleobject.h"
#include "drawableimageobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class Spaceship;

class Asteroid : public DrawableImageObject, public CircleObject
{
public:
    Asteroid(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture);
    virtual void handleCollision(Object *second);
    virtual void handleCollision(Asteroid *first);
    virtual void handleCollision(Spaceship *first);
    virtual bool isColliding(Object *second);
    virtual bool isColliding(Asteroid *first);
    virtual bool isColliding(Spaceship *first);
};

#endif // ASTEROID_H
