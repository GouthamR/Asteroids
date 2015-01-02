#include "ClassNamesXMacro.h"
virtual void handleCollision(Object *second);
#define X(className) virtual void handleCollision(className *first);
CLASS_NAMES
#undef X
virtual bool isColliding(Object *second);
#define X(className) virtual bool isColliding(className *first);
CLASS_NAMES
#undef X
