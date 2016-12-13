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
             SDL_Surface* destination, const SDL_Rect* clip)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, (SDL_Rect*)clip, destination, &offset );
}

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
* Lilian GALLON & Tristan RENAUDON      18/11/16            * ********************* Description ***************************
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
* Permet d'afficher la grid avec les images               *
*********************** Entrées *****************************
* Les images, le décalages des images, le clip de chaque    *
* image, et la gridLevel                                  *
*********************** Sorties *****************************
* -                                                          *
* ***********************************************************/

void showGrid(SDL_Surface *imgObject, SDL_Surface *screen,level grid){


    for(int i=0; i<grid.nbIce ; i++){
        applySurface(grid.tabIce[i].c*coefx+initialOff.xOffset,grid.tabIce[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipIce);
    }
    for(int i=0; i<grid.nbWall; i++){
        applySurface(grid.tabWall[i].c*coefx+wallOff.xOffset,grid.tabWall[i].l*coefy+wallOff.yOffset,imgObject,screen,&clipWall);
    }
    for(int i=0; i<grid.nbArrow; i++){
        if(grid.tabArrow[i].type==Left){
        applySurface(grid.tabArrow[i].c*coefx+initialOff.xOffset,grid.tabArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowLeft);
        }else if(grid.tabArrow[i].type==Up){
        applySurface(grid.tabArrow[i].c*coefx+initialOff.xOffset,grid.tabArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowUp);
        }else if(grid.tabArrow[i].type==Down){
        applySurface(grid.tabArrow[i].c*coefx+initialOff.xOffset,grid.tabArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowDown);
        }else if(grid.tabArrow[i].type==Right){
        applySurface(grid.tabArrow[i].c*coefx+initialOff.xOffset,grid.tabArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowRight);
        }
    }
    for(int i=0; i<grid.nbMonster+grid.nbMonsterSleeping ; i ++){
        if(grid.tabMonster[i].type==SLEEPING){
            applySurface(grid.tabMonster[i].c*coefx+sleepOff.xOffset,grid.tabMonster[i].l*coefy+sleepOff.yOffset,imgObject,screen,&clipSleep);
        }else if (grid.tabMonster[i].type==STANDARD){
            applySurface(grid.tabMonster[i].c*coefx+initialOff.xOffset,grid.tabMonster[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipAwake);
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
* le niveau (grid), la position finale, la position       *
* initiale, le clip du monstre, le coef x et y (longeur et  *
* hauteur d'une case de la grid, le décalage initial,     *
* car al grid commence pas à 0,0, l'id du monstre qui va  *
* etre animé, et la direction                               *
*********************** Sorties *****************************
* -                                                          *
*************************************************************/

void anime(level grid, coordgrid posArrivalGrid,SDL_Surface *screen, SDL_Surface *imgObject,int dir, int idMonster, SDL_Surface *fondJeu){

    coordCartesiennes posInit;
    posInit.x=grid.tabMonster[idMonster].c;
    posInit.y=grid.tabMonster[idMonster].l;

    coordCartesiennes posArrival;
    posArrival.x=posArrivalGrid.c;
    posArrival.y=posArrivalGrid.l;


    // Convertir lines et columns en pixel
    coordCartesiennes posInitPixel;
    posInitPixel.x=posInit.x*coefx+initialOff.xOffset;
    posInitPixel.y=posInit.y*coefy+initialOff.yOffset;

    coordCartesiennes posArrivalPixel;
    posArrivalPixel.x=posArrival.x*coefx+initialOff.xOffset;
    posArrivalPixel.y=posArrival.y*coefy+initialOff.yOffset;
    // Fin convertion

   // Tant que la pos initiale n'a pas atteint la pos finale, ..
    grid.tabMonster[idMonster].l = -2;
    grid.tabMonster[idMonster].c = -2;

    if(dir==Right){
        while(posInitPixel.x<posArrivalPixel.x){
            posInitPixel.x ++;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }

    }else if(dir==Left){

        while(posInitPixel.x>posArrivalPixel.x){
            posInitPixel.x --;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }

    }else if(dir==Down){

        while(posInitPixel.y<posArrivalPixel.y){
            posInitPixel.y ++;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }

    }else if(dir==Up){

        while(posInitPixel.y>posArrivalPixel.y){
            posInitPixel.y --;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
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
