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

void World::handleAllCollisions()
{
    for(auto iter1 = objects.begin(); iter1 != objects.end(); ++iter1)
    {
        for(auto iter2 = iter1 + 1; iter2 != objects.end(); ++iter2)
        {
            if((*iter1)->isColliding((*iter2).get()))
                (*iter1)->handleCollision((*iter2).get());
        }
    }
}

double getWrapped(const double &x, const double &min, const double &max)
{
    if(x > max)
        return min;
    else if(x < min)
        return max;
    return x;
}

void World::moveAllByVelocity(float elapsedTimeSeconds)
{
    for(auto iter1 = objects.begin(); iter1 != objects.end(); ++iter1)
    {
        double newX = (*iter1)->getX() + (*iter1)->getVelocity().getX()*elapsedTimeSeconds;
        double newY = (*iter1)->getY() + (*iter1)->getVelocity().getY()*elapsedTimeSeconds;
        if(wrap)
        {
            newX = getWrapped(newX, -(*iter1)->getWidth()/2, width + (*iter1)->getWidth()/2);
            newY = getWrapped(newY, -(*iter1)->getHeight()/2, height + (*iter1)->getHeight()/2);
        }
        (*iter1)->setX(newX);
        (*iter1)->setY(newY);
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
