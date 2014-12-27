#ifndef DRAWABLEASTEROID_H
#define DRAWABLEASTEROID_H

#include "circleobject.h"
#include "drawableimageobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class DrawableSpaceship;

class DrawableAsteroid : public DrawableImageObject, public CircleObject
{
public:
    DrawableAsteroid(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture);
    virtual void handleCollision(Object *second);
    virtual void handleCollision(DrawableAsteroid *first);
    virtual void handleCollision(DrawableSpaceship *first);
    virtual bool isColliding(Object *second);
    virtual bool isColliding(DrawableAsteroid *first);
    virtual bool isColliding(DrawableSpaceship *first);
};

#endif // DRAWABLEASTEROID_H
