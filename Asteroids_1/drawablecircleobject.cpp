#include "drawablecircleobject.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

DrawableCircleObject::DrawableCircleObject(const int &xPos, const int &yPos, const int &radius)
    : Object(xPos, yPos)
    , DrawableObject(xPos, yPos)
    , CircleObject(xPos, yPos, radius)
{}

void DrawableCircleObject::draw(sf::RenderWindow *window)
{
    int radius = getRadius();
    sf::CircleShape shape(radius);
    shape.setOrigin(radius, radius);
    sf::Vector2f *windowPos = getWindowCoordinatesPosition(window);
    shape.setPosition(*windowPos);
    delete windowPos;
    window->draw(shape);
}

