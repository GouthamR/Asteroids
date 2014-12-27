#include "drawableasteroid.h"

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

#include <iostream>

DrawableAsteroid::DrawableAsteroid(const int &xPos, const int &yPos, const int &radius)
    : Object(xPos, yPos)
    , DrawableCircleObject(xPos, yPos, radius)
    , sprite(NULL)
    , texture(new sf::Texture())
{
    if (!texture->loadFromFile("asteroid.png"))
    {
        std::cout << "Error loading asteroid.png" << std::endl;
    }
    else
    {
        sprite = new sf::Sprite(*texture);
        sf::Vector2u texSize = texture->getSize();
        float xScale = (float)radius*2/texSize.x;
        float yScale = (float)radius*2/texSize.y;
        sprite->setScale(xScale, yScale);
//        sprite->setColor(sf::Color::Green);
    }
}

DrawableAsteroid::~DrawableAsteroid()
{
    delete sprite;
    delete texture;
}

void DrawableAsteroid::draw(sf::RenderWindow *window)
{
//    DrawableCircleObject::draw(window);

    int radius = getRadius();
    sprite->setOrigin(radius, radius);
    sf::Vector2f *windowPos = getWindowCoordinatesPosition(window);
    sprite->setPosition(windowPos->x - radius, windowPos->y - radius);
    delete windowPos;
    window->draw(*sprite);
}
