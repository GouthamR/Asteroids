// split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "worlddrawer.h"
#include "circledrawer.h"
#include "circleobject.h"
#include "vector.h"

#include <iostream>
#include <cmath>

// Memory leaks possible - convert raw pointers to smart pointers

//******************************************************************************
//  Source: http://www.plasmaphysics.org.uk/programs/coll2d_cpp.htm
//  Simplified Version
//  The advantage of the 'remote' collision detection in the program above is
//  that one does not have to continuously track the balls to detect a collision.
//  The program needs only to be called once for any two balls unless their
//  velocity changes. However, if somebody wants to use a separate collision
//  detection routine for whatever reason, below is a simplified version of the
//  code which just calculates the new velocities, assuming the balls are already
//  touching (this condition is important as otherwise the results will be incorrect)
//****************************************************************************
void collision2D(double m1, double m2, double R,
                 double x1, double y1, double x2, double y2,
                 double& vx1, double& vy1, double& vx2, double& vy2);

int main()
{
//    const double MOVE_SPEED = 20;
    const double FRAMES_PER_SECOND = 60;
    const double WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids!");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    WorldDrawer *worldDrawer = new WorldDrawer(1);
    CircleObject *circleObject = new CircleObject(WINDOW_WIDTH/5, 0, 5); // will be deleted by drawer
    worldDrawer->add(new CircleDrawer(circleObject)); // circledrawer will be deleted by worlddrawer
    CircleObject *asteroidCircle = new CircleObject(WINDOW_WIDTH,0, 20); // will be deleted by drawer
//    asteroidCircle->incrementVelocity(20, 0);
    circleObject->setVelocity(1, 2);
    asteroidCircle->setVelocity(-2, 2);
    worldDrawer->add(new CircleDrawer(asteroidCircle)); // circledrawer will be deleted by worlddrawer

//    const int EDGE_RADIUS = 1E10;
//    CircleObject *topEdgeCircle = new CircleObject(WINDOW_WIDTH/2, WINDOW_HEIGHT + EDGE_RADIUS, EDGE_RADIUS);
//    CircleObject *bottomEdgeCircle = new CircleObject(WINDOW_WIDTH/2, 0 - EDGE_RADIUS, EDGE_RADIUS);
//    CircleObject *rightEdgeCircle = new CircleObject(WINDOW_WIDTH + EDGE_RADIUS, WINDOW_HEIGHT + EDGE_RADIUS, EDGE_RADIUS);
//    CircleObject *leftEdgeCircle = new CircleObject(WINDOW_WIDTH/2, 0 - EDGE_RADIUS, EDGE_RADIUS);

    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            // move the following into a method. And create Game class for this stuff.
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
//                    case sf::Keyboard::Up:
//                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_UP);
//                        break;
//                    case sf::Keyboard::Down:
//                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_DOWN);
//                        break;
//                    case sf::Keyboard::Left:
//                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_LEFT);
//                        break;
//                    case sf::Keyboard::Right:
//                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_RIGHT);
//                        break;
                    default:
                        break;
                }
            }
        }

//        circleObject->moveByVelocity(elapsedTime.asSeconds());
        circleObject->setX(circleObject->getX() + circleObject->getVelocity().getX());
        circleObject->setY(circleObject->getY() + circleObject->getVelocity().getY());
//        asteroidCircle->moveByVelocity(elapsedTime.asSeconds());
        asteroidCircle->setX(asteroidCircle->getX() + asteroidCircle->getVelocity().getX());
        asteroidCircle->setY(asteroidCircle->getY() + asteroidCircle->getVelocity().getY());

//        worldDrawer->handleAllWorldCollisions();
        double xDist = circleObject->getX() - asteroidCircle->getX();
        double yDist = circleObject->getY() - asteroidCircle->getY();
        double angle = atan2(yDist, xDist); // from asteroid to circle
        double radiiSum = circleObject->getRadius() + asteroidCircle->getRadius();
        if(sqrt(pow(xDist,2) + pow(yDist,2)) < radiiSum)
        {
            double xIntersect = radiiSum*cos(angle) - xDist;
            double yIntersect = radiiSum*sin(angle) - yDist;
            circleObject->setX(circleObject->getX() + xIntersect/2);
            asteroidCircle->setX(asteroidCircle->getX() - xIntersect/2);
            circleObject->setY(circleObject->getY() + yIntersect/2);
            asteroidCircle->setY(asteroidCircle->getY() - yIntersect/2);

            double vXA = asteroidCircle->getVelocity().getX();
            double vYA = asteroidCircle->getVelocity().getY();
            double vXC = circleObject->getVelocity().getX();
            double vYC = circleObject->getVelocity().getY();

            printf("b: vXA=%f,vYA=%f,vXC=%f,vYC=%f\n",vXA, vYA, vXC, vYC);

            collision2D(10,2,1,
                        asteroidCircle->getX(),asteroidCircle->getY(),
                        circleObject->getX(),circleObject->getY(),
                        vXA,vYA,
                        vXC,vYC);

            printf("a: vXA=%f,vYA=%f,vXC=%f,vYC=%f\n",vXA, vYA, vXC, vYC);

            asteroidCircle->setVelocity(round(vXA),round(vYA));
            circleObject->setVelocity(round(vXC),round(vYC));
        }

        window->clear();
        worldDrawer->drawAll(window);

        window->display();

        sf::Time sleepTime = sf::seconds (1/FRAMES_PER_SECOND - (clock.getElapsedTime().asSeconds()));
//        std::cout << "sleep = " << sleepTime.asSeconds() << std::endl;
        if(sleepTime.asSeconds() > 0)
            sf::sleep(sleepTime);

        clock.restart();
    }

    std::cout << "Ending." << std::endl;

    delete window;
    delete worldDrawer;

    return 0;
}

void collision2D(double m1, double m2, double R,
                 double x1, double y1, double x2, double y2,
                 double& vx1, double& vy1, double& vx2, double& vy2)
{

       double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;


       m21=m2/m1;
       x21=x2-x1;
       y21=y2-y1;
       vx21=vx2-vx1;
       vy21=vy2-vy1;

       vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
       vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;


//     *** return old velocities if balls are not approaching ***
       if ( (vx21*x21 + vy21*y21) >= 0) return;


//     *** I have inserted the following statements to avoid a zero divide;
//         (for single precision calculations,
//          1.0E-12 should be replaced by a larger value). **************

       fy21=1.0E-12*fabs(y21);
       if ( fabs(x21)<fy21 ) {
                   if (x21<0) { sign=-1; } else { sign=1;}
                   x21=fy21*sign;
        }

//     ***  update velocities ***
       a=y21/x21;
       dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
       vx2=vx2+dvx2;
       vy2=vy2+a*dvx2;
       vx1=vx1-m21*dvx2;
       vy1=vy1-a*m21*dvx2;

//     ***  velocity correction for inelastic collisions ***
       vx1=(vx1-vx_cm)*R + vx_cm;
       vy1=(vy1-vy_cm)*R + vy_cm;
       vx2=(vx2-vx_cm)*R + vx_cm;
       vy2=(vy2-vy_cm)*R + vy_cm;

       return;
}

//#include <iostream>
//using namespace std;

//#include "circleobject.h"
//#include "world.h"

//int main ()
//{
//    CircleObject circle1(0, 0, 5);
//    CircleObject circle2(5, 0, 5);

//    cout << circle1 << "\t" << circle2 << endl;

//    World world(2);
//    world.add(&circle1);
//    world.add(&circle2);

//    world.handleAllCollisions();

//    cout << circle1 << "\t" << circle2 << endl;

//    return 0;
//}

//#include <SFML/Graphics.hpp>

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(10);
//    shape.setPosition(0,0);
//    shape.setFillColor(sf::Color::Green);

//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }

//        window.clear();
//        window.draw(shape);
//        window.display();
//    }

//    return 0;
//}

