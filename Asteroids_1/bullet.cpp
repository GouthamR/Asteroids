#include "bullet.h"

Bullet::Bullet(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
{}

void Bullet::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void Bullet::handleCollision(Asteroid *first)
{
    // do nothing.
}

void Bullet::handleCollision(Spaceship *first)
{
    first->incrementCollisions();
    this->destroy();
}

void Bullet::handleCollision(Ufo *first)
{
    // do nothing.
}

bool Bullet::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool Bullet::isColliding(Asteroid *first)
{
    return false;
}

bool Bullet::isColliding(Spaceship *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool Bullet::isColliding(Ufo *first)
{
    return false;
}
