#ifndef _AFFICHAGE_H_
#define _AFFICHAGE_H_

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <string>

#include "level.h"

using namespace std;



/*********************************
 * FONCTIONS D'IMAGES
 * *******************************/
SDL_Surface *loadImage( string filename );

/*********************************
 * Fonctions d'application d'images
 * *******************************/
void applySurface(int x, int y, SDL_Surface* source,SDL_Surface* destination, SDL_Rect* clip);
SDL_Surface * loadImageWithColorKey(string filename, int r, int g, int b);

void affichageTerminal(grilleLevel grille, int tailleL,int tailleC);



#endif