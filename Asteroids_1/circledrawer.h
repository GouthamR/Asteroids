#ifndef CIRCLEDRAWER_H
#define CIRCLEDRAWER_H

#include "objectdrawer.h"

class CircleObject;

class CircleDrawer : public ObjectDrawer
{
public:
    CircleDrawer(CircleObject *circleObject);
    virtual void draw(sf::RenderWindow *window);
};

#endif // CIRCLEDRAWER_H
