#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include <SDL/SDL.h>
#include "level.h"

int absoluteValue(int val);


struct coordCartesiennes{
    int x;
    int y;
};

struct coordgrid{
    int l;
    int c;
};

struct offset{
    int xOffset;
    int yOffset;
};

enum {Null, Left, Right, Up, Down};

int direction(SDL_Event &eventM, coordCartesiennes &mouseDown, coordCartesiennes mouseDownReleased, coordCartesiennes swipe);
void updateLevel(level &grid, int monsterId, int dir, bool &outOfGrid, SDL_Surface *screen, SDL_Surface *imgObject, SDL_Surface *fondJeu);
int hitboxMonster(level grid, coordCartesiennes mouse, int &k);

void suppOccIce(level &grid,int idIce);

#endif