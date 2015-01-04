#ifndef ASTEROID_H
#define ASTEROID_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Asteroid : public DrawableImageObject, public CircleObject
{
public:
    Asteroid(const double &xPos, const double &yPos, const double &radius, std::shared_ptr<sf::Texture> texture);
    #include "DispatchFnsMacro.h"
};

#endif // ASTEROID_H
