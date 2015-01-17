#ifndef WORLD_H
#define WORLD_H

#include <vector> // std::vector
#include <memory> // std::shared_ptr

class Object;

class World
{
private:
    std::vector<std::shared_ptr<Object>> objects;
    int width, height;
    bool wrap;
protected:
    void add(std::shared_ptr<Object> objectPtr);
    void deleteMarked();
public:
    World(const int &numObjects, const int &width, const int &height, bool wrap);
    virtual ~World();
    void handleAllCollisions();
    void moveAllByVelocity(float elapsedTimeSeconds);
    bool isOutOfBounds(Object *obj);
};

#endif // WORLD_H
