#include "game.h"

#include "circleobject.h"
#include "vector.h"
#include "drawableworld.h"
#include "asteroid.h"
#include "spaceship.h"
#include "ufo.h"
#include "bullet.h"

#include <iostream>
#include <cmath>

const double Game::WINDOW_WIDTH = 600;
const double Game::WINDOW_HEIGHT = 600;
const int Game::ASTEROID_V_MAX = 100;
const double Game::MOVE_SPEED = 5;
const double Game::ROTATION_SPEED = Phys::Vector::THETA_QUARTER/10;
const double Game::FRAMES_PER_SECOND = 60;
const double Game::PHYS_FRAMES_PER_SECOND = FRAMES_PER_SECOND * 2;
const float Game::ASTEROID_ADD_DELAY = 5;
const float Game::UFO_ADD_DELAY = 20;
const int Game::INIT_NUM_ASTEROIDS = 10;

int Game::getRandInt(const int &min, const int &max)
{
    return rand() % (max - min + 1) + min;
}

std::shared_ptr<Asteroid> Game::createAsteroid(const std::shared_ptr<sf::Texture> &asteroidTexture)
{
    auto asteroid = std::make_shared<Asteroid>(getRandInt(0, WINDOW_WIDTH), getRandInt(0, WINDOW_HEIGHT),
                                                WINDOW_WIDTH/50, getRandInt(30, 60), asteroidTexture);
    asteroid->setVelocityXY(getRandInt(0, ASTEROID_V_MAX), getRandInt(0, ASTEROID_V_MAX));
    return asteroid;
}

void Game::controlSpaceship(const sf::Keyboard::Key &key_code)
{
    switch (key_code)
    {
        case sf::Keyboard::Up:
            spaceship->accelerate(MOVE_SPEED);
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

Game::Game()
	: worldDrawer(new DrawableWorld(3, WINDOW_WIDTH, WINDOW_HEIGHT, true))
	, bulletTexture(std::make_shared<sf::Texture>())
	, spaceship(NULL)
	, objectsToAdd(std::vector<std::shared_ptr<DrawableObject>>())
{}

Game::~Game()
{
	delete worldDrawer;
}

void Game::addBullet(const double &xPos, const double &yPos)
{
    this->objectsToAdd.push_back(std::make_shared<Bullet>(xPos, yPos, 4, this->bulletTexture, 
                                                            this->spaceship->getX(), this->spaceship->getY(), 
                                                            this->worldDrawer));
}

int Game::run()
{
	srand (time(NULL));

    bool addedAsteroid = false;
    bool addedUfo = false;

    objectsToAdd.reserve(1);

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                                                    "Goutham Rajeev's Asteroids");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    auto asteroidTexture = std::make_shared<sf::Texture>();
    auto spaceshipTexture = std::make_shared<sf::Texture>();
    auto ufoTexture = std::make_shared<sf::Texture>();
    if (!asteroidTexture->loadFromFile("asteroid.png") 
        || !spaceshipTexture->loadFromFile("spaceship.png")
        || !ufoTexture->loadFromFile("ufo.png") 
        || !bulletTexture->loadFromFile("bullet.png"))
    {
        std::cout << "ERROR: Unable to load images!" << std::endl;
        return 1;
    }

    spaceship = std::make_shared<Spaceship>(WINDOW_WIDTH/2, WINDOW_WIDTH/2, 
                                            WINDOW_WIDTH/40, spaceshipTexture);
    spaceship->setVelocityPolar(0, Phys::Vector::THETA_UP);
    worldDrawer->add(spaceship);

    for (int i = 0; i < INIT_NUM_ASTEROIDS; ++i)
    {
        worldDrawer->add(createAsteroid(asteroidTexture));
    }

    sf::Clock frameRateClock, physClock, timeElapsedClock; // starts all timers
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                controlSpaceship(event.key.code);
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
        // TODO: parametrize these:
        if(secondsElapsed > ASTEROID_ADD_DELAY)
        {
            if(!addedAsteroid && fmod(secondsElapsed, ASTEROID_ADD_DELAY) < 1)
            {
                objectsToAdd.push_back(createAsteroid(asteroidTexture));
                addedAsteroid = true;
            }
            else if(addedAsteroid && fmod(secondsElapsed, ASTEROID_ADD_DELAY) >= 1)
            {
                addedAsteroid = false;
            }
        }
        if(secondsElapsed > UFO_ADD_DELAY)
        {
            if(!addedUfo && fmod(secondsElapsed, UFO_ADD_DELAY) < 1)
            {
                objectsToAdd.push_back(std::make_shared<Ufo>(getRandInt(0, WINDOW_WIDTH),getRandInt(0, WINDOW_HEIGHT),WINDOW_WIDTH/40,Phys::Vector::THETA_QUARTER*getRandInt(0, 3),0,this,worldDrawer, ufoTexture));
                addedUfo = true;
            }
            else if(addedUfo && fmod(secondsElapsed, UFO_ADD_DELAY) >= 1)
            {
                addedUfo = false;
            }
        }

        for(auto iter = objectsToAdd.begin(); iter != objectsToAdd.end(); ++iter)
        {
            worldDrawer->add(*iter);
        }
        objectsToAdd.clear();

        worldDrawer->deleteMarked();

        frameRateClock.restart();
    }

    std::cout << "Ending." << std::endl;

    delete window;

	return 0;
}