#include "drawableworld.h"

#include "world.h"
#include "object.h"
#include "drawableobject.h"

#include <iostream>

DrawableWorld::DrawableWorld(const int &numObjects, const int &width, const int &height, bool wrap)
    : World(numObjects,width,height, wrap)
    , drawableObjects(std::vector<DrawableObject*>())
{}

DrawableWorld::~DrawableWorld()
{
    std::cout << "Destruct DrawableWorld" << std::endl;

    for(std::vector<DrawableObject*>::iterator iter = drawableObjects.begin();
        iter != drawableObjects.end(); ++iter)
    {
        // CHECK IF THIS WORKS!
        delete (*iter);
    }
    drawableObjects.clear();
}

void DrawableWorld::add(DrawableObject *drawable)
{
    World::add(drawable);
    drawableObjects.push_back(drawable);
}

void DrawableWorld::drawAll(sf::RenderWindow *window)
{
    for(std::vector<DrawableObject*>::iterator iter = drawableObjects.begin();
        iter != drawableObjects.end(); ++iter)
    {
        (*iter)->draw(window);
    }
}
