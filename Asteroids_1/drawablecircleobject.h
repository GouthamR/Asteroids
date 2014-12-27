#ifndef DRAWABLECIRCLEOBJECT_H
#define DRAWABLECIRCLEOBJECT_H

#include "drawableobject.h"
#include "circleobject.h"

class DrawableCircleObject : public DrawableObject, public CircleObject
{
public:
    DrawableCircleObject(const int &xPos, const int &yPos, const int &radius);
    virtual void draw(sf::RenderWindow *window);
};

#endif // DRAWABLECIRCLEOBJECT_H
