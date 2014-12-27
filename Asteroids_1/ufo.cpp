#include "ufo.h"

#include "spaceship.h"

const double Ufo::SPEED = 50;

Ufo::Ufo(const double &xPos, const double &yPos, const double &radius, const double &angle, sf::Texture *texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
{
    setVelocityPolar(SPEED,angle);
}

void Ufo::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void Ufo::handleCollision(Asteroid *first)
{
    // Do nothing.
}

void Ufo::handleCollision(Spaceship *first)
{
    first->incrementCollisions();
    // makes Ufo much more massive than Spaceship, causing Ufo to be unaffected by collision:
    handleCircleCollision(9E9,9E-9,(CircleObject*)first);
}

void Ufo::handleCollision(Ufo *first)
{
    // Do nothing. Should never be called.
}

bool Ufo::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool Ufo::isColliding(Asteroid *first)
{
    return false;
}

bool Ufo::isColliding(Spaceship *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool Ufo::isColliding(Ufo *first)
{
    return false;
}

