#ifndef BULLET_H
#define BULLET_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Bullet : public DrawableImageObject, public CircleObject
{
private:
    const static double SPEED;
    bool (*outOfBounds)(Object *);
public:
    Bullet(const double &xPos, const double &yPos, const double &radius, std::shared_ptr<sf::Texture> texture,
           const double &targetXPos, const double &targetYPos, bool (*outOfBounds)(Object *));
    virtual void update(const double &time);
    #include "DispatchFnsMacro.h"
};

#endif // BULLET_H
