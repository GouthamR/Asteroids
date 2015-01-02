#include "ClassNamesXMacro.h"
virtual void handleCollision(Object *second)=0;
#define X(className) virtual void handleCollision(className *first)=0;
CLASS_NAMES_X
#undef X
virtual bool isColliding(Object *second)=0;
#define X(className) virtual bool isColliding(className *first)=0;
CLASS_NAMES_X
#undef X
