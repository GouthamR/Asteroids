#include "drawablespaceship.h"

#include "vector.h"
#include<SFML/Graphics/Sprite.hpp>
#include <string>

DrawableSpaceship::DrawableSpaceship(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
    , orientation(Phys::Vector::THETA_UP)
    , numCollisions(0)
{}

void DrawableSpaceship::rotate(const double &angle)
{
    orientation += angle;
}

void DrawableSpaceship::accelerate(const double &magnitude)
{
    Phys::Vector *accel = Phys::Vector::createPolar(magnitude,orientation);
    setVelocity(getVelocity() += *accel);
    delete accel;
}

void DrawableSpaceship::incrementCollisions()
{
    numCollisions++;
}

void DrawableSpaceship::handleCollision(CircleObject *other)
{
    other->handleCollision(this);
}

void DrawableSpaceship::handleCollision(DrawableAsteroid *other)
{
    incrementCollisions();
    CircleObject::handleCollision((CircleObject*)other);
}

void DrawableSpaceship::handleCollision(DrawableSpaceship *other)
{
    // DEFAULT BEHAVIOR. THIS FUNCTION SHOULD NEVER BE CALLED.
    CircleObject::handleCollision((CircleObject*)other);
}

void DrawableSpaceship::draw(sf::RenderWindow *window)
{
    sprite->setRotation(-(orientation - Phys::Vector::THETA_QUARTER)/3.14*180); // orientation does not match with sprite atm
    DrawableImageObject::draw(window);
}
