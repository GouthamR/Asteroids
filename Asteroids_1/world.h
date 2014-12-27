#ifndef WORLD_H
#define WORLD_H

#include <vector> // std::vector

class Object;

class World
{
private:
    std::vector<Object*> objects;
protected:
    void add(Object *object);
public:
    World(const int &numObjects);
    ~World();
    void handleAllCollisions();
    void moveAllByVelocity(float elapsedTime);
};

#endif // WORLD_H
