#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include <SDL/SDL.h>
#include "level.h"

int absoluteValue(int val);

struct coord{
    int x=0;
    int y=0;
};

enum {Null, Left, Right, Up, Down};

int direction(SDL_Event &eventM, coord &mouseDown, coord mouseDownReleased, coord swipe);
bool monsterMovement(grilleLevel &grille, int dir, int ligne, int colonne);


#endif // DEPLACEMENT_H
