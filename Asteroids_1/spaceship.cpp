#include "spaceship.h"

#include "vector.h"
#include "ufo.h"
#include<SFML/Graphics/Sprite.hpp>
#include <string>

Spaceship::Spaceship(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture)
    : Object(xPos, yPos)
    , DrawableImageObject(xPos, yPos, radius*2, radius*2, texture)
    , CircleObject(xPos, yPos, radius)
    , orientation(Phys::Vector::THETA_UP)
    , numCollisions(0)
{}

void Spaceship::rotate(const double &angle)
{
    orientation += angle;
}

void Spaceship::accelerate(const double &magnitude)
{
    Phys::Vector *accel = Phys::Vector::createPolar(magnitude,orientation);
    setVelocity(getVelocity() += *accel);
    delete accel;
}

void Spaceship::incrementCollisions()
{
    numCollisions++;

    sf::Color color;
    switch (numCollisions)
    { // make enum for this instead, getting color from index = numCollisions
        case 1: color = sf::Color::Yellow; break;
        case 2: color = sf::Color::Magenta; break;
        case 3: color = sf::Color::Red; break;
        default: color = sf::Color::Blue; break;
    }
    sprite->setColor(color);
}

void Spaceship::handleCollision(Object *second)
{
    second->handleCollision(this);
}

void Spaceship::handleCollision(Asteroid *first)
{
    this->incrementCollisions();
    this->handleCircleCollision((CircleObject*)first);
}

void Spaceship::handleCollision(Spaceship *first)
{
    // SHOULD NEVER BE CALLED
}

void Spaceship::handleCollision(Ufo *first)
{
    first->handleCollision(this);
}

bool Spaceship::isColliding(Object *second)
{
    return second->isColliding(this);
}

bool Spaceship::isColliding(Asteroid *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

bool Spaceship::isColliding(Spaceship *first)
{
    return false;
}

bool Spaceship::isColliding(Ufo *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

void Spaceship::draw(sf::RenderWindow *window)
{
    sprite->setRotation(-(orientation - Phys::Vector::THETA_QUARTER)/3.14*180); // orientation does not match with sprite atm
    DrawableImageObject::draw(window);
}
