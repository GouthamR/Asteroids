#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "object.h"

namespace sf
{
    class RenderWindow;
    template <typename T> class Vector2;
    typedef Vector2<float> Vector2f;
}

class DrawableObject : public virtual Object
{
protected:
    sf::Vector2f *getWindowCoordinatesPosition(sf::RenderWindow *window);
public:
    DrawableObject(const double &xPos, const double &yPos);
    virtual void draw(sf::RenderWindow *window)=0;
};

#endif // DRAWABLEOBJECT_H
