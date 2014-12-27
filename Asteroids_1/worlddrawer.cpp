#include "worlddrawer.h"

#include "world.h"
#include "object.h"
#include "objectdrawer.h"

#include <iostream>

WorldDrawer::WorldDrawer(const int &numObjects)
    : world(new World(numObjects))
    , objectDrawers(std::vector<ObjectDrawer*>())
{}

WorldDrawer::~WorldDrawer()
{
    std::cout << "Destruct WorldDrawer" << std::endl;

    delete world;

    for(std::vector<ObjectDrawer*>::iterator iter = objectDrawers.begin();
        iter != objectDrawers.end(); ++iter)
    {
        // CHECK IF THIS WORKS!
        delete (*iter);
    }
    objectDrawers.clear();
}

void WorldDrawer::add(ObjectDrawer *objectDrawer)
{
    world->add(objectDrawer->getObject());
    objectDrawers.push_back(objectDrawer);
}

void WorldDrawer::drawAll(sf::RenderWindow *window)
{
    for(std::vector<ObjectDrawer*>::iterator iter = objectDrawers.begin();
        iter != objectDrawers.end(); ++iter)
    {
        (*iter)->draw(window);
    }
}

void WorldDrawer::handleAllWorldCollisions()
{
    world->handleAllCollisions();
}

void WorldDrawer::moveAllByVelocity(float elapsedTime)
{
    world->moveAllByVelocity(elapsedTime);
}
