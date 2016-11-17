TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf
INCLUDEPATH+=-I/usr/include/SDL/

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra
SOURCES += \
    level.cc \
    monster.cc \
    affichage.cc \
    main.cc

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    level.h \
    monster.h \
    affichage.h

