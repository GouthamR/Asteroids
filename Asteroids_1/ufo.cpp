#include "ufo.h"

#include "spaceship.h"

const double Ufo::SPEED = 50;
const double Ufo::BULLET_TIME = 1;

void Ufo::shootBullet()
{
    bulletAdder.addBullet(this->getX(), this->getY());
}

Ufo::Ufo(const double &xPos, const double &yPos, const double &radius,
         const double &angle, const double &bulletStartTime,
         BulletAdder &bulletAdder, BoundsChecker &boundsChecker,
         std::shared_ptr<sf::Texture> texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
    , currentBulletTime{bulletStartTime}
    , bulletAdder{bulletAdder}
    , boundsChecker{boundsChecker}
{
    setVelocityPolar(SPEED,angle);
}

void Ufo::update(const double &time)
{
    currentBulletTime += time;
    if(currentBulletTime >= BULLET_TIME)
    {
        shootBullet();
        currentBulletTime = 0;
    }

    if(boundsChecker.isOutOfBounds(this))
        markToDelete();
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

void Ufo::handleCollision(Bullet *first)
{
    // Do nothing.
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

bool Ufo::isColliding(Bullet *first)
{
    return false;
}
