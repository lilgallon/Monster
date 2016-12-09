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
SDL_Surface *loadImage( string filename ){
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

    dist_x_abs=absoluteValue(dist_x);
    dist_y_abs=absoluteValue(dist_y);

    if(dist_x_abs<=circleR && dist_y_abs<=circleR){
        return true;
    }else{
        return false;
    }

}


/****************** Nom de la fonction **********************
* showGrid                                                  *
******************** Auteur , Dates *************************
* Lilian GALLON  20/11/16                                   *
********************* Description ***************************
* Permet d'afficher la grille avec les images               *
*********************** Entrées *****************************
* Les images, le décalages des images, le clip de chaque    *
* image, et la grilleLevel                                  *
*********************** Sorties *****************************
* -                                                          *
* ***********************************************************/

void showGrid(offset wallOff, offset iceOff, offset awakeOff, offset sleepOff, offset initialOff, offset arrowOff,
              int coefx, int coefy,
              SDL_Surface *imgWall, SDL_Surface *imgIce, SDL_Surface *imgSleep, SDL_Surface *imgAwake, SDL_Surface *screen,
              SDL_Surface *imgaLeft, SDL_Surface *imgaRight, SDL_Surface *imgaUp, SDL_Surface *imgaDown,
              SDL_Rect clipWall, SDL_Rect clipIce, SDL_Rect clipSleep, SDL_Rect clipAwake,
              SDL_Rect clipArrowRight, SDL_Rect clipArrowLeft, SDL_Rect clipArrowDown, SDL_Rect clipArrowUp,
              level grille){

    for(int i=0; i<grille.nbMonster ; i ++){
        if(grille.tabMonster[i].type==SLEEPING){
            applySurface(grille.tabMonster[i].c*coefx+sleepOff.xOffset,grille.tabMonster[i].l*coefy+sleepOff.yOffset,imgSleep,screen,&clipSleep);
        }else if (grille.tabMonster[i].type==STANDARD){
            applySurface(grille.tabMonster[i].c*coefx+initialOff.xOffset,grille.tabMonster[i].l*coefy+initialOff.yOffset,imgAwake,screen,&clipAwake);
        }
    }
    for(int i=0; i<grille.nbIce ; i++){
        applySurface(grille.tabIce[i].c*coefx+initialOff.xOffset,grille.tabIce[i].l*coefy+initialOff.yOffset,imgIce,screen,&clipIce);
    }
    for(int i=0; i<grille.nbWall; i++){
        applySurface(grille.tabWall[i].c*coefx+wallOff.xOffset,grille.tabWall[i].l*coefy+wallOff.yOffset,imgWall,screen,&clipWall);
    }
    for(int i=0; i<grille.nbArrow; i++){
        if(grille.tabArrow[i].type==Left){
        applySurface(grille.tabArrow[i].c*coefx+initialOff.xOffset,grille.tabArrow[i].l*coefy+initialOff.yOffset,imgaLeft,screen,&clipArrowLeft);
        }else if(grille.tabArrow[i].type==Up){
        applySurface(grille.tabArrow[i].c*coefx+initialOff.xOffset,grille.tabArrow[i].l*coefy+initialOff.yOffset,imgaUp,screen,&clipArrowUp);
        }else if(grille.tabArrow[i].type==Down){
        applySurface(grille.tabArrow[i].c*coefx+initialOff.xOffset,grille.tabArrow[i].l*coefy+initialOff.yOffset,imgaDown,screen,&clipArrowDown);
        }else if(grille.tabArrow[i].type==Right){
        applySurface(grille.tabArrow[i].c*coefx+initialOff.xOffset,grille.tabArrow[i].l*coefy+initialOff.yOffset,imgaRight,screen,&clipArrowRight);
        }
    }
}

/****************** Nom de la fonction **********************
* anime                                                     *
******************** Auteur , Dates *************************
* Lilian GALLON,  09/12/16                                  *
********************* Description ***************************
* Anime un objet à partir de sa position initiale et de sa  *
* position finale                                           *
************************ Entrées ****************************
* le niveau (grille), la position finale, la position       *
* initiale, le clip du monstre, le coef x et y (longeur et  *
* hauteur d'une case de la grille, le décalage initial,     *
* car al grille commence pas à 0,0, l'id du monstre qui va  *
* etre animé, et la direction                               *
*********************** Sorties *****************************
* -                                                          *
*************************************************************/

void anime(level grille, coordGrille posFin2,
           offset initialOff, SDL_Rect clipAwake,
           int coefx, int coefy,
           SDL_Surface *screen, SDL_Surface *imgAwake,
           int dir, int idMonster){

    coordCartesiennes posInit;
    posInit.x=grille.tabMonster[idMonster].c;
    posInit.y=grille.tabMonster[idMonster].l;

    coordCartesiennes posFin;
    posFin.x=posFin2.c;
    posFin.y=posFin2.l;


    // Convertir lignes et colonnes en pixel
    coordCartesiennes posInitPixel;
    posInitPixel.x=posInit.x*coefx+initialOff.xOffset;
    posInitPixel.y=posInit.y*coefy+initialOff.yOffset;

    coordCartesiennes posFinPixel;
    posFinPixel.x=posFin.x*coefx+initialOff.xOffset;
    posFinPixel.y=posFin.y*coefy+initialOff.yOffset;
    // Fin convertion

   // Tant que la pos initiale n'a pas atteint la pos finale, ..

    if(dir==Right){
        while(posInitPixel.x<posFinPixel.x){
            SDL_Flip(screen);
            posInitPixel.x ++;
            applySurface(posInitPixel.x,posInitPixel.y,imgAwake,screen,&clipAwake);
        }

    }else if(dir==Left){

        while(posInitPixel.x>posFinPixel.x){
            SDL_Flip(screen);
            posInitPixel.x --;
            applySurface(posInitPixel.x,posInitPixel.y,imgAwake,screen,&clipAwake);
        }

    }else if(dir==Down){

        while(posInitPixel.y<posFinPixel.y){
            SDL_Flip(screen);
            posInitPixel.y ++;
            applySurface(posInitPixel.x,posInitPixel.y,imgAwake,screen,&clipAwake);
        }

    }else if(dir==Up){

        while(posInitPixel.y>posFinPixel.y){
            SDL_Flip(screen);
            posInitPixel.y --;
            applySurface(posInitPixel.x,posInitPixel.y,imgAwake,screen,&clipAwake);
        }
    }

}


/****************** Nom de la fonction **********************
* dynamicButton                                             *
******************** Auteur , Dates *************************
* Lilian GALLON  22/11/16                                   *
********************* Description ***************************
* Affiche une image de bouton différente lorsque le curseur *
* n'est pas dessus, et une autre si il est dessus.          *
*********************** Entrées *****************************
* Coordonnées en x et y où afficher l'image, l'image si le  *
* curseur est sur le bouton. Coodonnées en x et y où afficher
* l'image si le curseur n'est pas sur le bouton. Coordonnées*
* en x et y du milieu du bouton ainsi que son milieu. Le clip
* des deux images, et une variable évenement                *
*********************** Sorties *****************************
* Retourne vrai si le curseur est sur le bouton             *
************************************************************/
bool dynamicButton(SDL_Surface *imgOver, SDL_Surface *imgDefault, SDL_Surface *screen,
                   int xButton, int yButton, int rButton,
                   int xOverDisplay, int yOverDisplay,
                   int xDefaultDisplay, int yDefaultDisplay,
                   SDL_Rect *overClip, SDL_Rect *defaultClip,
                   SDL_Event event){

    if(overCircle(xButton,yButton,rButton)){
        applySurface(xOverDisplay,yOverDisplay,imgOver,screen,overClip);
        if(event.type==SDL_MOUSEBUTTONUP){
            return true;
        }else{
            return false;
        }
    }else{
        applySurface(xDefaultDisplay,yDefaultDisplay,imgDefault,screen,defaultClip);
        return false;
    }
}
