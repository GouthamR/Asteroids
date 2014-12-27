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

    sf::Color color;
    switch (numCollisions)
    { // make enum for this instead, getting color from index = numCollisions
        case 1: color = sf::Color::Yellow; break;
        case 2: color = sf::Color::Magenta; break;
        case 3: color = sf::Color::Red; break;
        default: color = sf::Color::White; break;
    }
    sprite->setColor(color);
}

void DrawableSpaceship::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void DrawableSpaceship::handleCollision(DrawableAsteroid *first)
{
    this->incrementCollisions();
    this->handleCircleCollision((CircleObject*)first);
}

void DrawableSpaceship::handleCollision(DrawableSpaceship *first)
{
    // SHOULD NEVER BE CALLED
    this->handleCircleCollision((CircleObject*)first);
}

bool DrawableSpaceship::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool DrawableSpaceship::isColliding(DrawableAsteroid *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool DrawableSpaceship::isColliding(DrawableSpaceship *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

void DrawableSpaceship::draw(sf::RenderWindow *window)
{
    sprite->setRotation(-(orientation - Phys::Vector::THETA_QUARTER)/3.14*180); // orientation does not match with sprite atm
    DrawableImageObject::draw(window);
}
