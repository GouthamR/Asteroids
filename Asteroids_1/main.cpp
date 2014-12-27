// split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "circleobject.h"
#include "vector.h"
#include "drawableworld.h"
#include "asteroid.h"
#include "spaceship.h"

#include <iostream>
#include <cmath>

int main()
{
    const double MOVE_SPEED = 5, ROTATION_SPEED = M_PI/20;
    const double FRAMES_PER_SECOND = 60;
    const double PHYS_FRAMES_PER_SECOND = FRAMES_PER_SECOND * 2;
    const double WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids!");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    DrawableWorld *worldDrawer = new DrawableWorld(3,WINDOW_WIDTH,WINDOW_HEIGHT,true);

    // (textures will be deleted by sprites?
    sf::Texture *asteroidTexture = new sf::Texture();
    sf::Texture *spaceshipTexture = new sf::Texture();
    if (!asteroidTexture->loadFromFile("asteroid.png") || !spaceshipTexture->loadFromFile("spaceship.png"))
    {
        std::cout << "ERROR: Unable to load images!" << std::endl;
        return 1;
    }

    Spaceship *spaceship = new Spaceship(WINDOW_WIDTH/2,WINDOW_WIDTH/2,WINDOW_WIDTH/40, spaceshipTexture);
    spaceship->setVelocityPolar(0, Phys::Vector::THETA_UP);
    worldDrawer->add(spaceship);

    for (int i = 0; i < 1; ++i)
    {
        Asteroid *asteroid = new Asteroid(WINDOW_WIDTH/2,0,WINDOW_WIDTH/50, asteroidTexture);
        asteroid->setVelocityXY(0,100);
        worldDrawer->add(asteroid); // circle will be deleted by worlddrawer
    }

    sf::Clock frameRateClock, physClock;
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
                    case sf::Keyboard::Up:
                        spaceship->accelerate(MOVE_SPEED);
//                        spaceship->setY(spaceship->getY() + 0.5);
                        break;
                    case sf::Keyboard::Down:
                        break;
                    case sf::Keyboard::Left:
                        spaceship->rotate(ROTATION_SPEED);
                        break;
                    case sf::Keyboard::Right:
                        spaceship->rotate(-ROTATION_SPEED);
                        break;
                    default:
                        break;
                }
            }
        }

        if(physClock.getElapsedTime().asSeconds() >= 1/PHYS_FRAMES_PER_SECOND)
        {
            worldDrawer->moveAllByVelocity(physClock.getElapsedTime().asSeconds());
            worldDrawer->handleAllCollisions();
            physClock.restart();
        }

        window->clear();
        worldDrawer->drawAll(window);
        window->display();

        sf::Time sleepTime = sf::seconds (1/FRAMES_PER_SECOND - (frameRateClock.getElapsedTime().asSeconds()));
        if(sleepTime.asSeconds() > 0)
            sf::sleep(sleepTime);

        frameRateClock.restart();
    }

    std::cout << "Ending." << std::endl;

    delete window;
    delete worldDrawer;
//    delete asteroidTexture;
//    delete spaceshipTexture;

    return 0;
}
