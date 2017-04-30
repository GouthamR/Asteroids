#include "spaceship.h"

#include "vector.h"
#include "ufo.h"
#include "bullet.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>

Spaceship::Spaceship(const double &xPos, const double &yPos, const double &radius, std::shared_ptr<sf::Texture> texture)
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
    std::unique_ptr<Phys::Vector> accel{Phys::Vector::createPolar(magnitude,orientation)};
    Phys::Vector newVelocity = getVelocity();
    newVelocity += *accel;
    setVelocity(newVelocity);
}

void Spaceship::incrementCollisions()
{
    numCollisions++;

    sf::Color color;
    switch (numCollisions)
    { // TODO: make enum for this instead, getting color from index = numCollisions
        case 1: color = sf::Color(255, 150, 0); break;
        case 2: color = sf::Color(255, 75, 0); break;
        case 3: color = sf::Color(255, 0, 0); break;
        default: markToDelete(); break;
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
    // TODO: throw an exception here.
    // SHOULD NEVER BE CALLED
}

void Spaceship::handleCollision(Ufo *first)
{
    first->handleCollision(this);
}

void Spaceship::handleCollision(Bullet *first)
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

bool Spaceship::isColliding(Bullet *first)
{
    return this->isCircleColliding((CircleObject*)first);
}

void Spaceship::draw(sf::RenderWindow *window)
{
    // TODO: orientation does not currently match with sprite
    sprite->setRotation(-(orientation - Phys::Vector::THETA_QUARTER)/3.14*180); 
    DrawableImageObject::draw(window);
}
