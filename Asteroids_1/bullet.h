#ifndef BULLET_H
#define BULLET_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Bullet : public DrawableImageObject, public CircleObject
{
public:
    Bullet(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture);
    #include "DispatchFnsMacro.h"
};

#endif // BULLET_H
