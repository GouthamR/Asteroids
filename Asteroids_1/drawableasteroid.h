#ifndef DRAWABLEASTEROID_H
#define DRAWABLEASTEROID_H

#include "drawablecircleobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class DrawableAsteroid : public DrawableCircleObject
{
private:
    sf::Sprite *sprite;
    sf::Texture *texture;
public:
    DrawableAsteroid(const int &xPos, const int &yPos, const int &radius);
    ~DrawableAsteroid();
    virtual void draw(sf::RenderWindow *window); // have client load image to circleobject, pass in there. OR rename this class to drawablecircleimageobject
};

#endif // DRAWABLEASTEROID_H
