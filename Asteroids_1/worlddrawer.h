#ifndef WORLDDRAWER_H
#define WORLDDRAWER_H

#include <vector> // std::vector

namespace sf { class RenderWindow; }

class World;
class Object;
class ObjectDrawer;

class WorldDrawer
{
private:
    World *world;
    std::vector<ObjectDrawer*> objectDrawers;
    // keep reference to window instead of passing by param to drawAll.
public:
    WorldDrawer(const int &numObjects);
    ~WorldDrawer();
    void add(ObjectDrawer *objectDrawer);
    void drawAll(sf::RenderWindow *window);
    void handleAllWorldCollisions();
};

#endif // WORLDDRAWER_H
