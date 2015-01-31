#include "world.h"

#include "object.h"
#include "vector.h"

#include <iostream>
#include <algorithm>

World::~World()
{
    std::cout << "Destruct World: clear vector." << std::endl;
    objects.clear();
}

double getWrapped(const double &x, const double &min, const double &max)
{
    if(x > max)
        return min;
    else if(x < min)
        return max;
    return x;
}

void World::moveByVelocity(std::shared_ptr<Object> obj, float elapsedTimeSeconds)
{
    double newX = obj->getX() + obj->getVelocity().getX()*elapsedTimeSeconds;
    double newY = obj->getY() + obj->getVelocity().getY()*elapsedTimeSeconds;
    if(wrap)
    {
        newX = getWrapped(newX, -obj->getWidth()/2, width + obj->getWidth()/2);
        newY = getWrapped(newY, -obj->getHeight()/2, height + obj->getHeight()/2);
    }
    obj->setX(newX);
    obj->setY(newY);
}

void World::add(std::shared_ptr<Object> objectPtr)
{
    objects.push_back(objectPtr);
}

void World::deleteMarked()
{
    auto deleteFn = [](std::shared_ptr<Object> obj){ return obj->isToDelete(); };
    objects.erase(std::remove_if(objects.begin(), objects.end(), deleteFn), objects.end());
}

World::World(const int &numObjects, const int &width, const int &height, bool wrap)
    : objects(std::vector<std::shared_ptr<Object>>())
    , width(width)
    , height(height)
    , wrap(wrap)
{
    objects.reserve(numObjects);
}

void World::updateAll(float elapsedTimeSeconds)
{
    for(auto iter1 = objects.begin(); iter1 != objects.end(); ++iter1)
    {
        moveByVelocity(*iter1, elapsedTimeSeconds);
        (*iter1)->update(elapsedTimeSeconds);

        for(auto iter2 = iter1 + 1; iter2 != objects.end(); ++iter2)
        {
            if((*iter1)->isColliding((*iter2).get()))
                (*iter1)->handleCollision((*iter2).get());
        }
    }
}

bool World::isOutOfBounds(Object *obj)
{
    double x = obj->getX();
    double y = obj->getY();
    double oHalfWidth = obj->getWidth()/2;
    double oHalfHeight = obj->getHeight()/2;
    // note: need to include equal condition, or else could wrap and will never be out of bounds.
    return x - oHalfWidth >= width || x + oHalfWidth <= 0
            || y - oHalfHeight >= height || y + oHalfHeight <= 0;
}
