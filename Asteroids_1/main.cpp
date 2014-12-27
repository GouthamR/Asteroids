// split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "circleobject.h"
#include "vector.h"
#include "drawableworld.h"
#include "drawablecircleobject.h"

#include <iostream>
#include <cmath>

// Memory leaks possible - convert raw pointers to smart pointers

int main()
{
//    const double MOVE_SPEED = 20;
    const double FRAMES_PER_SECOND = 60;
    const double WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids!");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    DrawableWorld *worldDrawer = new DrawableWorld(3);

    DrawableCircleObject *circle = new DrawableCircleObject(WINDOW_WIDTH/5,0,5);
    circle->setVelocity(2,2);
    worldDrawer->add(circle); // circle will be deleted by worlddrawer

//    CircleObject *asteroidCircle = new CircleObject(WINDOW_WIDTH,0, 20); // will be deleted by drawer
//    asteroidCircle->setVelocity(-2, 2);
//    worldDrawer->add(new CircleDrawer(asteroidCircle)); // circledrawer will be deleted by worlddrawer
    DrawableCircleObject *asteroidCircle = new DrawableCircleObject(WINDOW_WIDTH,0, 20);
    asteroidCircle->setVelocity(-2,2);
    worldDrawer->add(asteroidCircle); // circle will be deleted by worlddrawer

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

        worldDrawer->moveAllByVelocity(clock.getElapsedTime().asSeconds());

        worldDrawer->handleAllCollisions();

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

