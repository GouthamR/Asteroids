#include "asteroid.h"

#include "spaceship.h"

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

#include <iostream>

const double Asteroid::LIFETIME = 5;

Asteroid::Asteroid(const double &xPos, const double &yPos, const double &radius, std::shared_ptr<sf::Texture> texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
    , timeElapsed(0)
{}

void Asteroid::update(const double &time)
{
    timeElapsed += time;
    if(timeElapsed >= LIFETIME)
        markToDelete();
}

void Asteroid::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void Asteroid::handleCollision(Asteroid *first)
{
    this->handleCircleCollision((CircleObject*)first);
}

void Asteroid::handleCollision(Spaceship *first)
{
    first->incrementCollisions();
    this->handleCircleCollision((CircleObject*)first);
}

void Asteroid::handleCollision(Ufo *first)
{
    // do nothing.
}

void Asteroid::handleCollision(Bullet *first)
{
    // do nothing.
}

bool Asteroid::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool Asteroid::isColliding(Asteroid *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool Asteroid::isColliding(Spaceship *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool Asteroid::isColliding(Ufo *first)
{
    return false;
}

bool Asteroid::isColliding(Bullet *first)
{
    return false;
}
