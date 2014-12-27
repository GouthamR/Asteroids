#ifndef DRAWABLEIMAGEOBJECT_H
#define DRAWABLEIMAGEOBJECT_H

#include "drawableobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class DrawableImageObject : public DrawableObject
{
private:
    sf::Texture *texture;
protected:
    sf::Sprite *sprite;
public:
    DrawableImageObject(const double &xPos, const double &yPos, const double &xSize, const double &ySize, sf::Texture *texture);
    ~DrawableImageObject();
    virtual void draw(sf::RenderWindow *window);
};

#endif // DRAWABLEIMAGEOBJECT_H
