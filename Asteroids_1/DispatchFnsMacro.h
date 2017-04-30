#include "ClassNamesXMacro.h"
virtual void handleCollision(Object *second) override;
#define X(className) virtual void handleCollision(className *first) override;
CLASS_NAMES_X
#undef X
virtual bool isColliding(Object *second) override;
#define X(className) virtual bool isColliding(className *first) override;
CLASS_NAMES_X
#undef X
