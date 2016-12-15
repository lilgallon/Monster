#ifndef _DISPLAY_H
#define _DIPLAY_H_

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

#include "level.h"
#include "movement.h"

/********************************************
 * Initializations of constant variables
 * *******************************************/

const SDL_Rect clipWall{70,68,55,62};
const SDL_Rect clipIce{9,71,55,62};
const SDL_Rect clipAwake{16,147,43,45};
const SDL_Rect clipSleep{0,0,72,64};
const SDL_Rect clipArrowLeft{159,224,43,38};
const SDL_Rect clipArrowRight{107,224,43,38};
const SDL_Rect clipArrowUp{62,224,43,38};
const SDL_Rect clipArrowDown{15,224,43,38};

const offset initialOff{16,33};
const offset sleepOff{9,23};
const offset wallOff{9,25};

const int coefy = 52;
const int coefx = 60;

// Delay for the animation
// 0 = very fast animation
// 1 = fast animation
// 2 = smooth animation
// The value is in miliseconds
const int DELAY = 2;

/*********************************
 * Image functions
 * *******************************/
SDL_Surface *loadImage( std::string filename );
SDL_Surface * loadImageWithColorKey(std::string filename, int r, int g, int b);

/*********************************
 * Fonctions d'application d'images
 * *******************************/
void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, const SDL_Rect *clip);

/***************************************************
 * Functions linked with the interation of the user
 * *************************************************/

bool overCircle(int circleX, int circleY, int circleR);
bool dynamicButton(SDL_Surface *imgOver, SDL_Surface *imgDefault, SDL_Surface *screen,
                   int xButton, int yButton, int rButton,
                   int xOverDisplay, int yOverDisplay,
                   int xDefaultDisplay, int yDefaultDisplay,
                   SDL_Rect *overClip, SDL_Rect *defaultClip,
                   SDL_Event event);

/*******************************************
 * Functions linked to the level & animation
 * *****************************************/

void anime(level grid, coordgrid posFin2, SDL_Surface *screen, SDL_Surface *imgObject, int dir, int idMonster, SDL_Surface *fondJeu);
void showGrid(SDL_Surface *imgObject, SDL_Surface *screen,level grid);

#endif