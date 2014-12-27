#include "world.h"

#include "object.h"

World::World(const int &numObjects)
    : objects(std::vector<Object*>())
{
    objects.reserve(numObjects);
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
