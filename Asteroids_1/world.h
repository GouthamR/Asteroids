#ifndef WORLD_H
#define WORLD_H

#include <vector> // std::vector

class Object;

class World
{
private:
    std::vector<Object*> objects;
public:
    World(const int &numObjects);
    void add(Object *object);
    void handleAllCollisions();
};

#endif // WORLD_H
