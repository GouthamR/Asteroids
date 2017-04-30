#include "bulletadder.h"

#include "game.h"

BulletAdder::BulletAdder(Game *game)
	: game{game}
{}

void BulletAdder::addBullet(const double &xPos, const double &yPos)
{
	game->addBullet(xPos, yPos);
}