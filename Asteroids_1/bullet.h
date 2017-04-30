#ifndef BULLET_H
#define BULLET_H

#include "circleobject.h"
#include "drawableimageobject.h"
#include "boundschecker.h"

class Bullet : public DrawableImageObject, public CircleObject
{
private:
    const static double SPEED;
    BoundsChecker boundsChecker;
public:
    Bullet(const double &xPos, const double &yPos, const double &radius, 
    		std::shared_ptr<sf::Texture> texture, const double &targetXPos, 
    		const double &targetYPos, BoundsChecker &boundsChecker);
    virtual void update(const double &time) override;
    #include "DispatchFnsMacro.h"
};

#endif // BULLET_H
