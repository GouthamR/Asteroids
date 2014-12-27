#define CLASS_NAMES \
    X(Asteroid) \
    X(Spaceship) \
    X(Ufo)
virtual void handleCollision(Object *second);
#define X(className) virtual void handleCollision(className *first);
CLASS_NAMES
#undef X
virtual bool isColliding(Object *second);
#define X(className) virtual bool isColliding(className *first);
CLASS_NAMES
#undef X
#undef CLASS_NAMES
// def all the above as a single DISPATCH_FNS_DEF macro. include this file once in Object. Invoke macro where necessary.
// ifdef VIRTUAL -> #define SUFFIX =0
