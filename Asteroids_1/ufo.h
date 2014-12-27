#ifndef UFO_H
#define UFO_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Ufo : public DrawableImageObject, public CircleObject
{
private:
    const static double SPEED;
public:
    Ufo(const double &xPos, const double &yPos, const double &radius, const double &angle, sf::Texture *texture);
    #include "DispatchFnDefs.txt"
};
#endif // UFO_H
