#ifndef WORLD_H
#define WORLD_H

#include <vector> // std::vector

class Object;

class World
{
private:
    std::vector<Object*> objects;
    int width, height;
    bool wrap;
protected:
    void add(Object *object);
    void deleteMarked();
public:
    World(const int &numObjects, const int &width, const int &height, bool wrap);
    ~World();
    void handleAllCollisions();
    void moveAllByVelocity(float elapsedTimeSeconds);
};

#endif // WORLD_H
