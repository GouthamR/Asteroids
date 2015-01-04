#include "world.h"

#include "object.h"
#include "vector.h"

#include <iostream>
#include <algorithm>

//World::World(const int &numObjects, const int &width, const int &height)
//    : objects(std::vector<Object*>())
//{
//    objects.reserve(numObjects);
//}

World::~World()
{
    std::cout << "Destruct World: Do nothing." << std::endl;

//    for(std::vector<Object*>::iterator iter = objects.begin();
//        iter != objects.end(); ++iter)
//    {
//        delete (*iter);
//    }
//    objects.clear();
}

void World::add(Object *object)
{
    objects.push_back(object);
}

void World::remove(Object *object)
{
    objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
}

World::World(const int &numObjects, const int &width, const int &height, bool wrap)
    : objects(std::vector<Object*>())
    , width(width)
    , height(height)
    , wrap(wrap)
{
    objects.reserve(numObjects);
}

void World::handleAllCollisions()
{
    for(std::vector<Object*>::iterator iter1 = objects.begin();
        iter1 != objects.end(); ++iter1)
    {
        for(std::vector<Object*>::iterator iter2 = iter1+1;
            iter2 != objects.end(); ++iter2)
        {
            if((*iter1)->isColliding((*iter2)))
                (*iter1)->handleCollision(*iter2);
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
    for(std::vector<Object*>::iterator iter1 = objects.begin();
        iter1 != objects.end(); ++iter1)
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
