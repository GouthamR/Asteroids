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
    virtual void handleCollision(CircleObject *other);
    virtual void handleCollision(DrawableAsteroid *other);
    virtual void handleCollision(DrawableSpaceship *other);
};

#endif // DRAWABLEASTEROID_H
