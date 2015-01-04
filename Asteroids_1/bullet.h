#ifndef BULLET_H
#define BULLET_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Bullet : public DrawableImageObject, public CircleObject
{
private:
    const static double SPEED;
public:
    Bullet(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture,
           const double &targetXPos, const double &targetYPos);
    #include "DispatchFnsMacro.h"
};

#endif // BULLET_H
