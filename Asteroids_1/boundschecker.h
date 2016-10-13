#ifndef BOUNDSCHECKER_H
#define BOUNDSCHECKER_H

class World;
class Object;

class BoundsChecker
{
private:
	World *world;
public:
	BoundsChecker(World *world);
	bool isOutOfBounds(Object *obj);
};

#endif // BOUNDSCHECKER_H