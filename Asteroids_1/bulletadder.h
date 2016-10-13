#ifndef BULLETADDER_H
#define BULLETADDER_H

class Game;

class BulletAdder
{
private:
	Game *game;
public:
	BulletAdder(Game *game);
	void addBullet(const double &xPos, const double &yPos);
};

#endif // BULLETADDER_H