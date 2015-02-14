// split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "circleobject.h"
#include "vector.h"
#include "drawableworld.h"
#include "asteroid.h"
#include "spaceship.h"
#include "ufo.h"
#include "bullet.h"

#include <iostream>
#include <cmath>

const double WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;
DrawableWorld *worldDrawer = new DrawableWorld(3,WINDOW_WIDTH,WINDOW_HEIGHT,true);
auto bulletTexture = std::make_shared<sf::Texture>();
std::shared_ptr<Spaceship> spaceship;
auto objectsToAdd = std::vector<std::shared_ptr<DrawableObject>>();

bool outOfBounds(Object *obj)
{
    return worldDrawer->isOutOfBounds(obj);
}

void addBullet(const double &xPos, const double &yPos)
{
    // should NOT be called unless bullet texture loaded in main:
    objectsToAdd.push_back(std::make_shared<Bullet>(xPos, yPos, 4, bulletTexture, spaceship->getX(), spaceship->getY(), &outOfBounds));
}

int main()
{    
    const double MOVE_SPEED = 5, ROTATION_SPEED = Phys::Vector::THETA_QUARTER/10;
    const double FRAMES_PER_SECOND = 60;
    const double PHYS_FRAMES_PER_SECOND = FRAMES_PER_SECOND * 2;
    const float ASTEROID_ADD_DELAY = 10;
    bool addedAsteroid = false;

    objectsToAdd.reserve(1);

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids!");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    // (textures will be deleted by sprites?
    auto asteroidTexture = std::make_shared<sf::Texture>();
    auto spaceshipTexture = std::make_shared<sf::Texture>();
    auto ufoTexture = std::make_shared<sf::Texture>();
    if (!asteroidTexture->loadFromFile("asteroid.png") || !spaceshipTexture->loadFromFile("spaceship.png")
           || !ufoTexture->loadFromFile("ufo.png") || !bulletTexture->loadFromFile("bullet.png"))
    {
        std::cout << "ERROR: Unable to load images!" << std::endl;
        return 1;
    }

    spaceship = std::make_shared<Spaceship>(WINDOW_WIDTH/2,WINDOW_WIDTH/2,WINDOW_WIDTH/40, spaceshipTexture);
    spaceship->setVelocityPolar(0, Phys::Vector::THETA_UP);
    worldDrawer->add(spaceship);

    for (int i = 0; i < 1; ++i)
    {
        auto asteroid = std::make_shared<Asteroid>(WINDOW_WIDTH/2,0,WINDOW_WIDTH/50, asteroidTexture);
        asteroid->setVelocityXY(0,100);
        worldDrawer->add(asteroid); // circle will be deleted by worlddrawer
    }

    auto ufo = std::make_shared<Ufo>(WINDOW_WIDTH/4,WINDOW_HEIGHT/2,WINDOW_WIDTH/40,Phys::Vector::THETA_LEFT,0,&addBullet,&outOfBounds, ufoTexture);
    worldDrawer->add(ufo);

    sf::Clock frameRateClock, physClock, timeElapsedClock; // starts both automatically
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
            worldDrawer->updateAll(physClock.getElapsedTime().asSeconds());
            physClock.restart();
        }

        window->clear();
        worldDrawer->drawAll(window);
        window->display();

        sf::Time sleepTime = sf::seconds (1/FRAMES_PER_SECOND - (frameRateClock.getElapsedTime().asSeconds()));
        if(sleepTime.asSeconds() > 0)
            sf::sleep(sleepTime);

        float secondsElapsed = timeElapsedClock.getElapsedTime().asSeconds();
        if(secondsElapsed > ASTEROID_ADD_DELAY)
        {
            if(!addedAsteroid && fmod(secondsElapsed, ASTEROID_ADD_DELAY) < 1)
            {
                objectsToAdd.push_back(std::make_shared<Asteroid>(WINDOW_WIDTH/2,0,WINDOW_WIDTH/50, asteroidTexture));
                addedAsteroid = true;
            }
            else if(addedAsteroid && fmod(secondsElapsed, ASTEROID_ADD_DELAY) >= 1)
            {
                addedAsteroid = false;
            }
        }

        for(auto iter = objectsToAdd.begin(); iter != objectsToAdd.end(); ++iter)
            worldDrawer->add(*iter);
        objectsToAdd.clear();

        worldDrawer->deleteMarked();

        frameRateClock.restart();
    }

    std::cout << "Ending." << std::endl;

    delete window;
    delete worldDrawer;
//    delete asteroidTexture;
//    delete spaceshipTexture;

    return 0;
}
