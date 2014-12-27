#include "world.h"

#include "object.h"
#include "vector.h"

#include <iostream>

World::World(const int &numObjects)
    : objects(std::vector<Object*>())
{
    objects.reserve(numObjects);
}

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

void World::handleAllCollisions()
{
    for(std::vector<Object*>::iterator iter1 = objects.begin();
        iter1 != objects.end(); ++iter1)
    {
        for(std::vector<Object*>::iterator iter2 = iter1+1;
            iter2 != objects.end(); ++iter2)
        {
            (*iter1)->handleCollision(*iter2);
        }
    }
}

void World::moveAllByVelocity(float elapsedTime)
{
    for(std::vector<Object*>::iterator iter1 = objects.begin();
        iter1 != objects.end(); ++iter1)
    {
        (*iter1)->setX((*iter1)->getX() + (*iter1)->getVelocity().getX());
        (*iter1)->setY((*iter1)->getY() + (*iter1)->getVelocity().getY());
    }
}
