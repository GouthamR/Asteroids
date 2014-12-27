#include "objectdrawer.h"

#include "object.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

sf::Vector2f *ObjectDrawer::getWindowCoordinatesPosition(sf::RenderWindow *window)
{
    return new sf::Vector2f(object->getX(), window->getSize().y - object->getY());
}

ObjectDrawer::ObjectDrawer(Object *object)
    : object(object)
{}

ObjectDrawer::~ObjectDrawer()
{
    std::cout << "Destruct ObjectDrawer" << std::endl;
    delete object;
}
