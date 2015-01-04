#ifndef BULLET_H
#define BULLET_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Bullet : public DrawableImageObject, public CircleObject
{
private:
    const static double SPEED;
    void (*destroyObject)(DrawableObject *dObj);
    void destroy();
public:
    Bullet(const double &xPos, const double &yPos, const double &radius, sf::Texture *texture,
           void (*destroyObject)(DrawableObject *dObj),
           const double &targetXPos, const double &targetYPos);
    #include "DispatchFnsMacro.h"
};

#endif // BULLET_H
