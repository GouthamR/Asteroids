#ifndef DRAWABLESPACESHIP_H
#define DRAWABLESPACESHIP_H

#include "circleobject.h"
#include "drawableimageobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class DrawableAsteroid;

class DrawableSpaceship : public DrawableImageObject, public CircleObject
{
private:
    double orientation; // in radians
    int numCollisions;
public:
    DrawableSpaceship(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture);
    void rotate(const double &angle);
    void accelerate(const double &magnitude);
    void incrementCollisions();
    virtual void handleCollision(CircleObject *other);
    virtual void handleCollision(DrawableAsteroid *other);
    virtual void handleCollision(DrawableSpaceship *other);
    virtual void draw(sf::RenderWindow *window);
};

#endif // DRAWABLESPACESHIP_H
