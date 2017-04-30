#include "drawableworld.h"

#include "world.h"
#include "object.h"
#include "drawableobject.h"

#include <iostream>
#include <algorithm>

DrawableWorld::DrawableWorld(const int &numObjects, const int &width, const int &height, bool wrap)
    : World{numObjects,width,height, wrap}
    // default-construct drawableObjects
{
    drawableObjects.reserve(numObjects);
}

DrawableWorld::~DrawableWorld()
{
    std::cout << "Destruct DrawableWorld: clear vector." << std::endl;
    drawableObjects.clear();
}

void DrawableWorld::add(std::shared_ptr<DrawableObject> drawablePtr)
{
    World::add(drawablePtr);
    drawableObjects.push_back(drawablePtr);
}

void DrawableWorld::drawAll(sf::RenderWindow *window)
{
    for(auto iter = drawableObjects.begin(); iter != drawableObjects.end(); ++iter)
    {
        (*iter)->draw(window);
    }
}

void DrawableWorld::deleteMarked()
{
    World::deleteMarked();
    auto deleteFn =  [](std::shared_ptr<DrawableObject> obj){ return obj->isToDelete(); };
    drawableObjects.erase(std::remove_if(drawableObjects.begin(), drawableObjects.end(), deleteFn), drawableObjects.end());
}
