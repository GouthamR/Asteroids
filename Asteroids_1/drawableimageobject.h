#ifndef DRAWABLEIMAGEOBJECT_H
#define DRAWABLEIMAGEOBJECT_H

#include <memory>

#include "drawableobject.h"

namespace sf
{
    class Sprite;
    class Texture;
}

class DrawableImageObject : public DrawableObject
{
private:
    std::shared_ptr<sf::Texture> texture;
protected:
    sf::Sprite *sprite;
public:
    DrawableImageObject(const double &xPos, const double &yPos,
                        const double &xSize, const double &ySize,
                        std::shared_ptr<sf::Texture> texture);
    ~DrawableImageObject();
    virtual void draw(sf::RenderWindow *window);
};

#endif // DRAWABLEIMAGEOBJECT_H
