#ifndef ASTEROID_H
#define ASTEROID_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Asteroid : public DrawableImageObject, public CircleObject
{
private:
    const double LIFETIME;
    double timeElapsed;
public:
    Asteroid(const double &xPos, const double &yPos, const double &radius, const double &lifetime, std::shared_ptr<sf::Texture> texture);
    virtual void update(const double &time) override;
    #include "DispatchFnsMacro.h"
};

#endif // ASTEROID_H
