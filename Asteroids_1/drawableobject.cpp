#include "drawableobject.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

sf::Vector2f *DrawableObject::getWindowCoordinatesPosition(sf::RenderWindow *window)
{
    return new sf::Vector2f(getX(), window->getSize().y - getY());
}

DrawableObject::DrawableObject(const int &xPos, const int &yPos)
    : Object(xPos, yPos)
{}
