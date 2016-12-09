#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include <SDL/SDL.h>
#include "level.h"

int absoluteValue(int val);

struct coordCartesiennes{
    int x;
    int y;
};

struct coordGrille{
    int l;
    int c;
};

struct offset{
    int xOffset;
    int yOffset;
};

enum {Null, Left, Right, Up, Down};

int direction(SDL_Event &eventM, coordCartesiennes &mouseDown, coordCartesiennes mouseDownReleased, coordCartesiennes swipe);
void updateLevel(level &grille,int monsterId, int dir, bool &outOfGrid,
                 SDL_Surface *screen, offset initialOff, SDL_Rect clipAwake, SDL_Surface *imgAwake,
                 int coefx, int coefy);
int hitboxMonster(level grille, coordCartesiennes mouse, int coefx, int coefy, int offsetX, int offsetY, int &k);



#endif // DEPLACEMENT_H
