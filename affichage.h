#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include "level.h"


struct offset{
    int xOffset;
    int yOffset;
};


/*********************************
 * FONCTIONS D'IMAGES
 * *******************************/
SDL_Surface *loadImage( std::string filename );

/*********************************
 * Fonctions d'application d'images
 * *******************************/
void applySurface(int x, int y, SDL_Surface* source,SDL_Surface* destination, SDL_Rect* clip);
SDL_Surface * loadImageWithColorKey(std::string filename, int r, int g, int b);


// autre
bool overCircle(int circleX, int circleY, int circleR);


bool dynamicButton(SDL_Surface *imgOver, SDL_Surface *imgDefault, SDL_Surface *screen,
                   int xButton, int yButton, int rButton,
                   int xOverDisplay, int yOverDisplay,
                   int xDefaultDisplay, int yDefaultDisplay,
                   SDL_Rect *overClip, SDL_Rect *defaultClip,
                   SDL_Event event);


// Version 3
void showGrid(offset wallOff, offset iceOff, offset awakeOff, offset sleepOff, offset initialOff,
               int coefx, int coefy,
               SDL_Surface *imgWall, SDL_Surface *imgIce, SDL_Surface *imgSleep, SDL_Surface *imgAwake, SDL_Surface *screen,
               SDL_Rect clipWall, SDL_Rect clipIce, SDL_Rect clipSleep, SDL_Rect clipAwake,
               level grille);

#endif