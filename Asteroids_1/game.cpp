#include "game.h"

#include "circleobject.h"
#include "vector.h"
#include "drawableworld.h"
#include "asteroid.h"
#include "spaceship.h"
#include "ufo.h"
#include "bullet.h"

#include <iostream>
#include <stdexcept>
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
const float Game::ADD_DELAY_MARGIN = 1;

int Game::getRandInt(const int &min, const int &max)
{
    return rand() % (max - min + 1) + min;
}

std::shared_ptr<Asteroid> Game::createAsteroid(const std::shared_ptr<sf::Texture> &asteroidTexture)
{
    int xPos = getRandInt(0, WINDOW_WIDTH);
    int yPos = getRandInt(0, WINDOW_HEIGHT);
    double radius = WINDOW_WIDTH/50;
    int angle = getRandInt(30, 60);
    int velocityX = getRandInt(0, ASTEROID_V_MAX);
    int velocityY = getRandInt(0, ASTEROID_V_MAX);
    auto asteroid = std::make_shared<Asteroid>(xPos, yPos, radius, angle, asteroidTexture);
    asteroid->setVelocityXY(velocityX, velocityY);
    return asteroid;
}

std::shared_ptr<Ufo> Game::createUfo(const std::shared_ptr<sf::Texture> &ufoTexture)
{
    int xPos = getRandInt(0, WINDOW_WIDTH);
    int yPos = getRandInt(0, WINDOW_HEIGHT);
    double radius = WINDOW_WIDTH/40;
    double angle = Phys::Vector::THETA_QUARTER*getRandInt(0, 3);
    double bulletStartTime = 0;
    auto ufo = std::make_shared<Ufo>(xPos,yPos,radius,angle,bulletStartTime,
                                        bulletAdder,boundsChecker, ufoTexture);
    return ufo;
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

bool Game::delayedAdd(const sf::Clock &timeElapsedClock, const float &add_delay, 
                        bool &toAddThisCycle)
{
    float secondsElapsed = timeElapsedClock.getElapsedTime().asSeconds();
    bool withinAddTimeRange = (fmod(secondsElapsed, add_delay) < ADD_DELAY_MARGIN);
    if(withinAddTimeRange && toAddThisCycle)
    {
        toAddThisCycle = false;
        return true;
    }
    else
    {
        if(!withinAddTimeRange)
        {
            toAddThisCycle = true;
        }
        return false;
    }
}

Game::Game()
    : worldDrawer(new DrawableWorld(3, WINDOW_WIDTH, WINDOW_HEIGHT, true))
    , bulletAdder(BulletAdder(this))
    , boundsChecker(BoundsChecker(worldDrawer))
    , bulletTexture(std::make_shared<sf::Texture>())
    , asteroidTexture(std::make_shared<sf::Texture>())
    , spaceshipTexture(std::make_shared<sf::Texture>())
    , ufoTexture(std::make_shared<sf::Texture>())
    , spaceship(NULL)
    , objectsToAdd(std::vector<std::shared_ptr<DrawableObject>>())
{
    srand(time(NULL));
    
    objectsToAdd.reserve(1);

    if (!asteroidTexture->loadFromFile("asteroid.png") 
        || !spaceshipTexture->loadFromFile("spaceship.png")
        || !ufoTexture->loadFromFile("ufo.png") 
        || !bulletTexture->loadFromFile("bullet.png"))
    {
        throw std::runtime_error("Images not loaded");
    }

    spaceship = std::make_shared<Spaceship>(WINDOW_WIDTH/2, WINDOW_WIDTH/2, 
                                            WINDOW_WIDTH/40, spaceshipTexture);
    spaceship->setVelocityPolar(0, Phys::Vector::THETA_UP);
}

Game::~Game()
{
    delete worldDrawer;
}

void Game::addBullet(const double &xPos, const double &yPos)
{
    auto bullet = std::make_shared<Bullet>(xPos, yPos, 4, 
                                            this->bulletTexture, 
                                            this->spaceship->getX(), 
                                            this->spaceship->getY(), 
                                            this->boundsChecker);
    this->objectsToAdd.push_back(bullet);
}

void Game::run()
{
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), 
                                                    "Goutham Rajeev's Asteroids");
    window->setFramerateLimit(FRAMES_PER_SECOND);

    worldDrawer->add(spaceship);
    for (int i = 0; i < INIT_NUM_ASTEROIDS; ++i)
    {
        worldDrawer->add(createAsteroid(asteroidTexture));
    }

    // false, so will not add at beginning:
    bool toAddAsteroid = false;
    bool toAddUfo = false;

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

        float physClockElapsedTime = physClock.getElapsedTime().asSeconds();
        if(physClockElapsedTime >= 1/PHYS_FRAMES_PER_SECOND)
        {
            worldDrawer->updateAll(physClockElapsedTime);
            physClock.restart();
        }

        window->clear();
        worldDrawer->drawAll(window);
        window->display();

        float frameRateClockElapsed = frameRateClock.getElapsedTime().asSeconds();
        sf::Time sleepTime = sf::seconds (1/FRAMES_PER_SECOND - frameRateClockElapsed);
        if(sleepTime.asSeconds() > 0)
            sf::sleep(sleepTime);

        if(delayedAdd(timeElapsedClock, ASTEROID_ADD_DELAY, toAddAsteroid))
        {
            std::cout << "Adding Asteroid" << std::endl;
            objectsToAdd.push_back(createAsteroid(asteroidTexture));            
        }
        if(delayedAdd(timeElapsedClock, UFO_ADD_DELAY, toAddUfo))
        {
            std::cout << "Adding Ufo" << std::endl;
            objectsToAdd.push_back(createUfo(ufoTexture));
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
}