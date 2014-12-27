#include "circledrawer.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "circleobject.h"

CircleDrawer::CircleDrawer(CircleObject *circleObject)
    : ObjectDrawer(circleObject)
{}

void CircleDrawer::draw(sf::RenderWindow *window)
{
    CircleObject *object = (CircleObject*)(getObject());
    sf::CircleShape shape(object->getRadius());
    sf::Vector2f *windowPos = getWindowCoordinatesPosition(window);
    shape.setPosition(*windowPos);
    delete windowPos;
    window->draw(shape);
}
