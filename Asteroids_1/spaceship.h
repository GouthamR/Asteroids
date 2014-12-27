#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "circleobject.h"
#include "drawableimageobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class Asteroid;

class Spaceship : public DrawableImageObject, public CircleObject
{
private:
    double orientation; // in radians
    int numCollisions;
public:
    Spaceship(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture);
    void rotate(const double &angle);
    void accelerate(const double &magnitude);
    void incrementCollisions();
    virtual void handleCollision(Object *second);
    virtual void handleCollision(Asteroid *first);
    virtual void handleCollision(Spaceship *first);
    virtual bool isColliding(Object *second);
    virtual bool isColliding(Asteroid *first);
    virtual bool isColliding(Spaceship *first);
    virtual void draw(sf::RenderWindow *window);
};

#endif // SPACESHIP_H
