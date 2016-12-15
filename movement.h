#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SDL/SDL.h>
#include "level.h"

int absoluteValue(int val);

// More comprehensive to manipulate pixels
struct coordCartesian{
    int x;
    int y;
};

// More comprehensive to manipulate cases
struct coordgrid{
    int l;
    int c;
};

// More comprehensive to manipulate offset for the images
struct offset{
    int xOffset;
    int yOffset;
};

// Different states of a direction
enum {Null, Left, Right, Up, Down};

/****************************************************
 * Functions linked with the interaction of the user
 * **************************************************/
int direction(SDL_Event &eventM, coordCartesian &mouseDown, coordCartesian mouseDownReleased, coordCartesian swipe);
int hitboxMonster(level grid, coordCartesian mouse, int &k);

/***************************************************
 * Functions linked with the update of the level
 * *************************************************/
void updateLevel(level &grid, int monsterId, int dir, bool &outOfGrid, SDL_Surface *screen, SDL_Surface *imgObject, SDL_Surface *fondJeu);
void suppOccIce(level &grid,int idIce);

#endif