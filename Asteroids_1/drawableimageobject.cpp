#include "drawableimageobject.h"

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/RenderWindow.hpp>

#include <iostream>

DrawableImageObject::DrawableImageObject(const double &xPos, const double &yPos,
                                         const double &xSize, const double &ySize,
                                         std::shared_ptr<sf::Texture> texture)
    : Object(xPos, yPos)
    , DrawableObject(xPos, yPos)
    , texture(texture)
    , sprite(NULL)
{
    sprite = new sf::Sprite(*texture);
    sf::Vector2u texSize = texture->getSize();
    sprite->setOrigin(texSize.x/2, texSize.y/2);
    sprite->setScale((float)xSize/texSize.x, (float)ySize/texSize.y);
//  sprite->setColor(sf::Color::Green);
}


DrawableImageObject::~DrawableImageObject()
{
    delete sprite; // crash if still null if image not loaded?
//    delete texture;
}

void DrawableImageObject::draw(sf::RenderWindow *window)
{
    sf::Vector2f *windowPos = getWindowCoordinatesPosition(window);
    sprite->setPosition(*windowPos);
    delete windowPos;
    window->draw(*sprite);
}
