#ifndef OBJECTDRAWER_H
#define OBJECTDRAWER_H

class Object;
namespace sf
{
    class RenderWindow;
    template <typename T> class Vector2;
    typedef Vector2<float> Vector2f;
}

class ObjectDrawer
{
private:
    Object *object;
protected:
    sf::Vector2f *getWindowCoordinatesPosition(sf::RenderWindow *window);
public:
    ObjectDrawer(Object *object);
    virtual ~ObjectDrawer();
    Object *getObject() { return object; }
    virtual void draw(sf::RenderWindow *window)=0;
};

#endif // OBJECTDRAWER_H
