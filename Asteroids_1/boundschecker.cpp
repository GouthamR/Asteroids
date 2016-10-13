#include "boundschecker.h"

#include "world.h"

BoundsChecker::BoundsChecker(World *world)
	: world(world)
{}

bool BoundsChecker::isOutOfBounds(Object *obj)
{
	return world->isOutOfBounds(obj);
}