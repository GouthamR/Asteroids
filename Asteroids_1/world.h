#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

class Object;

class World
{
private:
    std::vector<std::shared_ptr<Object>> objects;
    int width, height;
    bool wrap;
    void moveByVelocity(std::shared_ptr<Object> obj, float elapsedTimeSeconds);
protected:
    void add(std::shared_ptr<Object> objectPtr);
    void deleteMarked();
public:
    World(const int &numObjects, const int &width, const int &height, bool wrap);
    virtual ~World();
    void updateAll(float elapsedTimeSeconds);
    bool isOutOfBounds(Object *obj) const;
};

#endif // WORLD_H
