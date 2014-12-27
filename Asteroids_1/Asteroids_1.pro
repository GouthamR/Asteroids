TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    circleobject.cpp \
    object.cpp \
    vector.cpp \
    world.cpp \
    drawableworld.cpp \
    drawableobject.cpp \
    drawableimageobject.cpp \
    asteroid.cpp \
    spaceship.cpp

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
    spaceship.h
