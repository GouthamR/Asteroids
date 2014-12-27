// split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "worlddrawer.h"
#include "circledrawer.h"
#include "circleobject.h"
#include "vector.h"

#include <iostream>

// Memory leaks possible - convert raw pointers to smart pointers

int main()
{
    const double MOVE_SPEED = 20;
    const double FRAMES_PER_SECOND = 60;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(600, 600), "Drawing a World!");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    WorldDrawer *worldDrawer = new WorldDrawer(1);
    CircleObject *circleObject = new CircleObject(300, 600, 5); // will be deleted by drawer
    worldDrawer->add(new CircleDrawer(circleObject)); // circledrawer will be deleted by worlddrawer
    CircleObject *asteroidCircle = new CircleObject(300, 200, 20); // will be deleted by drawer
    asteroidCircle->incrementVelocity(20, 0);
    worldDrawer->add(new CircleDrawer(asteroidCircle)); // circledrawer will be deleted by worlddrawer

    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Time elapsedTime = clock.restart();

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
                    case sf::Keyboard::Up:
                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_UP);
                        break;
                    case sf::Keyboard::Down:
                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_DOWN);
                        break;
                    case sf::Keyboard::Left:
                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_LEFT);
                        break;
                    case sf::Keyboard::Right:
                        circleObject->incrementVelocity(MOVE_SPEED, Phys::Vector::THETA_RIGHT);
                        break;
                    default:
                        break;
                }
            }
        }

        circleObject->moveByVelocity(elapsedTime.asSeconds());
        asteroidCircle->moveByVelocity(elapsedTime.asSeconds());
        worldDrawer->handleAllWorldCollisions();

        window->clear();
        worldDrawer->drawAll(window);
        window->display();

        sf::Time sleepTime = sf::seconds (1/FRAMES_PER_SECOND - (clock.getElapsedTime().asSeconds()));
//        std::cout << "sleep = " << sleepTime.asSeconds() << std::endl;
        if(sleepTime.asSeconds() > 0)
            sf::sleep(sleepTime);
    }

    std::cout << "Ending." << std::endl;

    delete window;
    delete worldDrawer;

    return 0;
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
//    sf::CircleShape shape(100.f);
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

