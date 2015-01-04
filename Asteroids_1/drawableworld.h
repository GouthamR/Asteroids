#ifndef DRAWABLEWORLD_H
#define DRAWABLEWORLD_H

#include <vector> // std::vector
#include <memory> // std::shared_ptr

#include "world.h"

namespace sf { class RenderWindow; }

class DrawableObject;

class DrawableWorld : public World
{
private:
    std::vector<std::shared_ptr<DrawableObject>> drawableObjects;
    // keep reference to window instead of passing by param to drawAll.
public:
    DrawableWorld(const int &numObjects, const int &width, const int &height, bool wrap);
    ~DrawableWorld();
    void add(std::shared_ptr<DrawableObject> drawablePtr);
    void drawAll(sf::RenderWindow *window);
    void deleteMarked();
};

#endif // DRAWABLEWORLD_H
