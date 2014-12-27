#include "drawableasteroid.h"

#include "drawablespaceship.h"

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

#include <iostream>

DrawableAsteroid::DrawableAsteroid(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
{}

void DrawableAsteroid::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void DrawableAsteroid::handleCollision(DrawableAsteroid *first)
{
    this->handleCircleCollision((CircleObject*)first);
}

void DrawableAsteroid::handleCollision(DrawableSpaceship *first)
{
    first->incrementCollisions();
    this->handleCircleCollision((CircleObject*)first);
}

bool DrawableAsteroid::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool DrawableAsteroid::isColliding(DrawableAsteroid *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool DrawableAsteroid::isColliding(DrawableSpaceship *first)
{
    return this->isCircleColliding((CircleObject*)first);
}
