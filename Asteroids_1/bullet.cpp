#include "bullet.h"

#include "spaceship.h"

const double Bullet::SPEED = 300;

Bullet::Bullet(const double &xPos, const double &yPos, const double &radius,
               std::shared_ptr<sf::Texture> texture, const double &targetXPos,
               const double &targetYPos, BoundsChecker &boundsChecker)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
    , boundsChecker{boundsChecker}
{
    setVelocityXY(targetXPos - xPos, targetYPos - yPos); // set angle
    setVelocityPolar(SPEED, getVelocity().getTheta());
}

void Bullet::update(const double &time)
{
    if(boundsChecker.isOutOfBounds(this))
        markToDelete();
}

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
    this->markToDelete();
}

void Bullet::handleCollision(Ufo *first)
{
    // do nothing.
}

void Bullet::handleCollision(Bullet *first)
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

bool Bullet::isColliding(Bullet *first)
{
    return false;
}
