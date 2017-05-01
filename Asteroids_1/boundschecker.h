#ifndef BOUNDSCHECKER_H
#define BOUNDSCHECKER_H

class World;
class Object;

class BoundsChecker
{
private:
	const World * const world;
public:
	BoundsChecker(const World * const world);
	bool isOutOfBounds(Object *obj);
};

#endif // BOUNDSCHECKER_H