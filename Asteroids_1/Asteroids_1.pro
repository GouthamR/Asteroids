TEMPLATE = app
#CONFIG += console  #adds console.
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    circleobject.cpp \
    object.cpp \
    vector.cpp \
    world.cpp \
    drawableworld.cpp \
    drawableobject.cpp \
    drawableimageobject.cpp \
    asteroid.cpp \
    spaceship.cpp \
    ufo.cpp \
    bullet.cpp

LIBS += -LC:\Users\Goutham\Documents\SFML_Projects\SFML-2.1\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += C:\Users\Goutham\Documents\SFML_Projects\SFML-2.1\include
DEPENDPATH += C:\Users\Goutham\Documents\SFML_Projects\SFML-2.1\include

HEADERS += \
    circleobject.h \
    object.h \
    vector.h \
    world.h \
    drawableworld.h \
    drawableobject.h \
    drawableimageobject.h \
    asteroid.h \
    spaceship.h \
    ufo.h \
    DispatchFnsMacro.h \
    bullet.h \
    ClassNamesXMacro.h \
    ObjectDispatchFnsMacro.h \
    ObjectClassDeclarationMacro.h

OTHER_FILES +=
