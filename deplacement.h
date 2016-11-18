#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include <SDL/SDL.h>

int valAbsolue(int val);

struct coord{
    int x=0;
    int y=0;
};

int deplacement(SDL_Event &eventM, coord &mouseDown, coord &mouseDownReleased, coord &swipe);

#endif // DEPLACEMENT_H
