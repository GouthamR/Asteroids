#ifndef GAME_H
#define GAME_H

// TODO: split these into individual imports
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>
#include <vector>

#include "bulletadder.h"
#include "boundschecker.h"
#include "drawableworld.h"

class Spaceship;
class DrawableObject;
class Object;
class Asteroid;
class Ufo;

class Game
{
private:
	const static double WINDOW_WIDTH;
	const static double WINDOW_HEIGHT;
	const static int ASTEROID_V_MAX;
	const static double MOVE_SPEED;
	const static double ROTATION_SPEED;
	const static double FRAMES_PER_SECOND;
	const static double PHYS_FRAMES_PER_SECOND;
	const static float ASTEROID_ADD_DELAY;
	const static float UFO_ADD_DELAY;
	const static int INIT_NUM_ASTEROIDS;
	const static float ADD_DELAY_MARGIN;
	
	std::unique_ptr<DrawableWorld> worldDrawer; // Note: dynamically allocated to avoid storing large data structures on the stack
	BulletAdder bulletAdder;
	BoundsChecker boundsChecker;
	std::shared_ptr<sf::Texture> bulletTexture;
	std::shared_ptr<sf::Texture> asteroidTexture;
	std::shared_ptr<sf::Texture> spaceshipTexture;
	std::shared_ptr<sf::Texture> ufoTexture;
	std::shared_ptr<Spaceship> spaceship;
	std::vector<std::shared_ptr<DrawableObject>> objectsToAdd;
	
	int getRandInt(const int &min, const int &max);
	std::shared_ptr<Asteroid> createAsteroid(const std::shared_ptr<sf::Texture> &asteroidTexture);
	std::shared_ptr<Ufo> createUfo(const std::shared_ptr<sf::Texture> &ufoTexture);
	void controlSpaceship(const sf::Keyboard::Key &key_code);
	bool delayedAdd(const sf::Clock &timeElapsedClock, const float &add_delay, 
					bool &toAddThisCycle);
	void handleWindowEvents(sf::RenderWindow &window);
	void updatePhysics(sf::Clock &physClock);
	void updateDisplay(sf::RenderWindow &window);
	void sleepUntilNextFrame(sf::Clock &frameRateClock);
	void updateObjectsToAdd(const sf::Clock &timeElapsedClock, bool &toAddAsteroid,
							bool &toAddUfo);
	void addFromObjectsToAdd();
	void addInitialObjects();
public:
	Game();
	void addBullet(const double &xPos, const double &yPos);
	void run();
};

#endif // GAME_H