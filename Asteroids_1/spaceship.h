#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "circleobject.h"
#include "drawableimageobject.h"

class Spaceship : public DrawableImageObject, public CircleObject
{
private:
    double orientation; // in radians
    int numCollisions;
public:
    Spaceship(const double &xPos, const double &yPos, const double &radius,
              std::shared_ptr<sf::Texture> texture);
    void rotate(const double &angle);
    void accelerate(const double &magnitude);
    void incrementCollisions();
    #include "DispatchFnsMacro.h"
    virtual void draw(sf::RenderWindow *window) override;
};

#endif // SPACESHIP_H
