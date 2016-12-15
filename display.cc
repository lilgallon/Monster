#include "display.h"
#include "level.h"

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;


/****************** Function's name *************************
* loadImage                                                 *
******************** Author , Dates *************************
* Atelier PONG                                              *
********************* Description ***************************
* Load an image                                             *
*********************** Entries *****************************
* The filename of the image to load                         *
*********************** Output ******************************
* Return the loaded image                                   *
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


/****************** Function's name *************************
* applySurface                                              *
******************** Author , Dates *************************
* Atelier PONG                                              *
********************* Description ***************************
* Applies an image on a surface                             *
*********************** Entries *****************************
* Positions x, and y where we want to put the image         *
* The source, and the image to apply                        *
* The surface where to put the image                        *
* The clip of the image to display                          *
*********************** Output ******************************
* -                                                         *
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

/****************** Function's name *************************
* loadImageWithColorKey                                     *
******************** Author , Dates *************************
* Atelier PONG                                              *
********************* Description ***************************
* Loads an image on a surface without a specified color     *
*********************** Entries *****************************
* The filename of the image to load                         *
* The red value (0 to 255)                                  *
* The green value (0 to 255)                                *
* The blue value (0 to 255)                                 *
*********************** Output ******************************
* -                                                         *
************************************************************/
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

/****************** Function's name *************************
* overCircle                                                *
******************** Authors , Dates ************************
* Lilian GALLON & Tristan RENAUDON      18/11/16            *
* Allows to know when the cursor is on a circle             *
*********************** Entries *****************************
* X and Y  positions of the center of the circle and its    *
* radius                                                    *
*********************** Output *****************************
* Returns true when the cursor is on the circle             *
************************************************************/
bool overCircle(int circleX, int circleY, int circleR){
    int mouseX, mouseY;
    int dist_x_abs;
    int dist_y_abs;

    // Stores x pos of the cursor in "mouseX"
    // Stores y pos of the cursor in "mouseY"
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


/****************** Function's name *************************
* showGrid                                                  *
******************** Authors , Dates ************************
* Lilian GALLON  20/11/16                                   *
********************* Description ***************************
* Displays the level                                        *
*********************** Entries *****************************
* The images, the images' offset, the clip of every images  *
* and the grid                                              *
*********************** Output ******************************
* -                                                         *
* ***********************************************************/

void showGrid(SDL_Surface *imgObject, SDL_Surface *screen,level grid){

    // Browses the array of the ices
    for(int i=0; i<grid.nbIce ; i++){
        applySurface(grid.aryIce[i].c*coefx+initialOff.xOffset,grid.aryIce[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipIce);
    }
    // Browses the array of the walls
    for(int i=0; i<grid.nbWall; i++){
        applySurface(grid.aryWall[i].c*coefx+wallOff.xOffset,grid.aryWall[i].l*coefy+wallOff.yOffset,imgObject,screen,&clipWall);
    }
    // Browses the array of the arrows
    for(int i=0; i<grid.nbArrow; i++){
        if(grid.aryArrow[i].type==Left){
        applySurface(grid.aryArrow[i].c*coefx+initialOff.xOffset,grid.aryArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowLeft);
        }else if(grid.aryArrow[i].type==Up){
        applySurface(grid.aryArrow[i].c*coefx+initialOff.xOffset,grid.aryArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowUp);
        }else if(grid.aryArrow[i].type==Down){
        applySurface(grid.aryArrow[i].c*coefx+initialOff.xOffset,grid.aryArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowDown);
        }else if(grid.aryArrow[i].type==Right){
        applySurface(grid.aryArrow[i].c*coefx+initialOff.xOffset,grid.aryArrow[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipArrowRight);
        }
    }
    // Browses the array of the monsters
    for(int i=0; i<grid.nbMonster+grid.nbMonsterSleeping ; i ++){
        if(grid.aryMonster[i].type==SLEEPING){
            applySurface(grid.aryMonster[i].c*coefx+sleepOff.xOffset,grid.aryMonster[i].l*coefy+sleepOff.yOffset,imgObject,screen,&clipSleep);
        }else if (grid.aryMonster[i].type==STANDARD){
            applySurface(grid.aryMonster[i].c*coefx+initialOff.xOffset,grid.aryMonster[i].l*coefy+initialOff.yOffset,imgObject,screen,&clipAwake);
        }
    }

    // Explainations:
    // grid.aryMonster[i].c * coefx = x position in PIXELS of the monster
    // we add "+ initialOff.xOffset", it corresponds to the initial gap of
    // the level (the origin isn't at 0,0, but at initialOff.xOffset,initialOff.yOffset
}

/****************** Function's name *************************
* anime                                                     *
******************** Authors , Dates ************************
* Lilian GALLON,  09/12/16                                  *
********************* Description ***************************
* Animates an object according to its initial position and  *
* its final position                                        *
************************ Entries ****************************
* The level (grid), the final position, the initial position*
* the monster's clip, the x & y coefficient, the initial    *
* offset, the id of the monster which will be animated, and *
* the direction                                             *
*********************** Output ******************************
* -                                                          *
*************************************************************/

void anime(level grid, coordgrid posArrivalGrid,SDL_Surface *screen, SDL_Surface *imgObject,int dir, int idMonster, SDL_Surface *fondJeu){

    coordCartesian posInit;
    posInit.x=grid.aryMonster[idMonster].c;
    posInit.y=grid.aryMonster[idMonster].l;

    coordCartesian posArrival;
    posArrival.x=posArrivalGrid.c;
    posArrival.y=posArrivalGrid.l;


    // Converts the lines and columns in pixels
    coordCartesian posInitPixel;
    posInitPixel.x=posInit.x*coefx+initialOff.xOffset;
    posInitPixel.y=posInit.y*coefy+initialOff.yOffset;

    coordCartesian posArrivalPixel;
    posArrivalPixel.x=posArrival.x*coefx+initialOff.xOffset;
    posArrivalPixel.y=posArrival.y*coefy+initialOff.yOffset;
    // End of conversion

    // Hide the monster that will be animated
    grid.aryMonster[idMonster].l = -2;
    grid.aryMonster[idMonster].c = -2;

    // According to the direction, the monster be displayed with different
    // x and y positions
    if(dir==Right){
        while(posInitPixel.x<posArrivalPixel.x){
            // A little delay to get a smoother animation
            SDL_Delay(2);
            // The x position of the monster will increments because it goes right
            posInitPixel.x ++;
            // Clear the screen by displaying the level, and the background
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            // End of the screen clear
            // Applies the image of the monster
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            // Displays everything
            SDL_Flip(screen);
        }
    // Same instructions, but the condition changes because of the direction
    }else if(dir==Left){

        while(posInitPixel.x>posArrivalPixel.x){
            SDL_Delay(2);
            posInitPixel.x --;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }

    }else if(dir==Down){

        while(posInitPixel.y<posArrivalPixel.y){
            SDL_Delay(2);
            posInitPixel.y ++;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }

    }else if(dir==Up){

        while(posInitPixel.y>posArrivalPixel.y){
            SDL_Delay(2);
            posInitPixel.y --;
            applySurface(0,0,fondJeu,screen,NULL);
            showGrid(imgObject,screen,grid);
            applySurface(posInitPixel.x,posInitPixel.y,imgObject,screen,&clipAwake);
            SDL_Flip(screen);
        }
    }

}


/****************** Function's name *************************
* dynamicButton                                             *
******************** Authors , Dates ************************
* Lilian GALLON  22/11/16                                   *
********************* Description ***************************
* Displays a different image of button when the cursor isn't*
* on it, and an other otherwise. Moreover it returns true   *
* when the user is on it and clicked                        *
*********************** Entries *****************************
* x and y positions where to display the image, the image to*
* display the button if the cursor is on it. Positions x and*
* y where to display the button if the cursor isn't on it.  *
* Positions x and y of the center of the button (a circle)  *
* The clip of both of the images, and an event variable     *
*********************** Output ******************************
* Returns true if the cursor is on the button               *
************************************************************/
bool dynamicButton(SDL_Surface *imgOver, SDL_Surface *imgDefault, SDL_Surface *screen,
                   int xButton, int yButton, int rButton,
                   int xOverDisplay, int yOverDisplay,
                   int xDefaultDisplay, int yDefaultDisplay,
                   SDL_Rect *overClip, SDL_Rect *defaultClip,
                   SDL_Event event){

    // If the cursor is on it ..
    if(overCircle(xButton,yButton,rButton)){
        // .. it applies an image
        applySurface(xOverDisplay,yOverDisplay,imgOver,screen,overClip);
        if(event.type==SDL_MOUSEBUTTONUP){
            // And if the user clicked, it returns true
            return true;
        }else{
            return false;
        }
    }else{
        applySurface(xDefaultDisplay,yDefaultDisplay,imgDefault,screen,defaultClip);
        return false;
    }
}
