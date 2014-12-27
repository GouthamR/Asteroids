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

void DrawableAsteroid::handleCollision(CircleObject *other)
{
    other->handleCollision(this);
}

void DrawableAsteroid::handleCollision(DrawableAsteroid *other)
{
    CircleObject::handleCollision((CircleObject*)other);
}

void DrawableAsteroid::handleCollision(DrawableSpaceship *other)
{
    other->incrementCollisions();
    CircleObject::handleCollision((CircleObject*)other);
}
