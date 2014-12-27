#ifndef DRAWABLEWORLD_H
#define DRAWABLEWORLD_H

#include <vector> // std::vector

#include "world.h"

namespace sf { class RenderWindow; }

class DrawableObject;

class DrawableWorld : public World
{
private:
    std::vector<DrawableObject*> drawableObjects;
    // keep reference to window instead of passing by param to drawAll.
public:
    DrawableWorld(const int &numObjects);
    ~DrawableWorld();
    void add(DrawableObject *drawable);
    void drawAll(sf::RenderWindow *window);
};

#endif // DRAWABLEWORLD_H
