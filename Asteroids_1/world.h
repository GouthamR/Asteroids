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
    ~World();
    void add(Object *object);
    void handleAllCollisions();
    void moveAllByVelocity(float elapsedTime);
};

#endif // WORLD_H
