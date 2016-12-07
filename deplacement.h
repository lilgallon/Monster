#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include <SDL/SDL.h>
#include "level.h"

int absoluteValue(int val);

struct coord{
    int x;
    int y;
};

struct coord2{
    int l;
    int c;
};

enum {Null, Left, Right, Up, Down};

int direction(SDL_Event &eventM, coord &mouseDown, coord mouseDownReleased, coord swipe);
void updateLevel(level &grille,int monsterId, int dir);


#endif // DEPLACEMENT_H
