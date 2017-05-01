#include "boundschecker.h"

#include "world.h"

BoundsChecker::BoundsChecker(const World * const world)
	: world{world}
{}

bool BoundsChecker::isOutOfBounds(Object *obj)
{
	return world->isOutOfBounds(obj);
}