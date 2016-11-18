#include "affichage.h"
#include "level.h"

#include <iostream>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>

#include "deplacement.h"

using namespace std;


/*********************************
 * FONCTIONS D'IMAGES
 * *******************************/

/****************** Nom de la fonction **********************
* loadImage                                                 *
******************** Auteur , Dates *************************
* Atelier PONG                                              *
********************* Description ***************************
* Charge une image                                          *
*********************** Entrées *****************************
* Nom de l'image.extension                                  *
*********************** Sorties *****************************
* Retourne l'image chargée                                  *
************************************************************/
SDL_Surface *
loadImage( string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }
    return optimizedImage;
}


/****************** Nom de la fonction **********************
* applySurface                                              *
******************** Auteur , Dates *************************
* Atelier PONG                                              *
********************* Description ***************************
* Applique une image sur une surface                        *
*********************** Entrées *****************************
* Positions x, et y où on veut afficher l'image             *
* La source, l'image à appliquer                            *
* La surface sur laquelle l'appliquer                       *
* La partie de l'image qu'on veut afficher                  *
*********************** Sorties *****************************
* Applique l'image entrée sur la surface désirée            *
************************************************************/
void
applySurface(int x, int y, SDL_Surface* source,
             SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

/****************** Nom de la fonction **********************
* afficheGrille                                             *
******************** Auteur , Dates *************************
* Lilian GALLON                                             *
********************* Description ***************************
* Permet d'afficher à l'écran le contenu du tableau en      *
* images                                                    *
*********************** Entrées *****************************
* Le nombre de lignes et de colonnes, la grille             *
*********************** Sorties *****************************
* -                                                         *
************************************************************/
// -- loadImageWithColorKey ------------
// Auteur: Atelier PONG
// Cette fonction permet de charger une
// image, et de rendre transparent une
// couleur déterminée par le mélange RGB
// entré en paramètres.
// --------------------------------------
SDL_Surface *
loadImageWithColorKey(string filename, int r, int g, int b)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );

        if( optimizedImage != NULL )
        {
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r, g, b );
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }
    return optimizedImage;

}

// Affichage terminal test

void affichageTerminal(grilleLevel grille, int tailleL,int tailleC){
    for (int ligne =0; ligne < tailleL; ligne++) {
        for (int colonne =0; colonne < tailleC; colonne++) {
            cout << grille[ligne][colonne] << " ";
        }
        cout << endl;
    }
}

/****************** Nom de la fonction **********************
* overCircle                                                *
******************** Auteur , Dates *************************
* Lilian GALLON  18/11/16                                   *
********************* Description ***************************
* Permet de savoir quand l'utilisateur a son curseur sur un *
* un bouton rond                                            *
*********************** Entrées *****************************
* Coordonnées X et Y du centre du cercle et son, rayon      *
*********************** Sorties *****************************
* Retourne vrai si le curseur est sur le bouton             *
************************************************************/
bool overCircle(int circleX, int circleY, int circleR){
    int mouseX, mouseY;
    int dist_x_abs;
    int dist_y_abs;

    SDL_GetMouseState(&mouseX, &mouseY);

    int dist_x = circleX - mouseX;
    int dist_y = circleY - mouseY;

    dist_x_abs=valAbsolue(dist_x);
    dist_y_abs=valAbsolue(dist_y);

    if(dist_x_abs<=circleR && dist_y_abs<=circleR){
        return true;
    }else{
        return false;
    }

}