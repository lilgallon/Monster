#include <iostream>
#include <sstream>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <array>

#include "level.h"

#include "deplacement.h"
#include "affichage.h"

using namespace std;

const int BOUTON_RAYON=50;
const int BOUTON_MIDDLE_X=92+BOUTON_RAYON ;
const int BOUTON_MIDDLE_Y=256+BOUTON_RAYON;

const int ECRAN_WIDTH = 320;
const int ECRAN_HEIGHT = 568;
const int ECRAN_BPP = 32;
const int NB_LEVEL = 6;

enum {Menu,Play,Lost};

int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    /****************************************
     * Initialisation pour les images
     * **************************************/
    SDL_Surface *fondAccueil1, *fondAccueil2;
    SDL_Surface *fondJeu;
    SDL_Surface *screen;
    SDL_Surface *imgWall, *imgIce, *imgAwake, *imgSleep;
    SDL_Surface *imgaLeft, *imgaRight, *imgaUp, *imgaDown;

    screen=SDL_SetVideoMode(ECRAN_WIDTH,ECRAN_HEIGHT,ECRAN_BPP,SDL_SWSURFACE);

    fondJeu=loadImage("background.bmp");
    fondAccueil1=loadImage("menu.bmp");
    fondAccueil2=loadImage("menu_play.bmp");
    imgWall = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgIce = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgAwake = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgSleep = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgaLeft = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgaRight = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgaUp = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgaDown = loadImageWithColorKey("sprite.bmp",255,255,255);



    /********************************************
     * Initialisation pour l'affichage
     * *******************************************/

    SDL_Rect clipWall;
    clipWall.x=70;
    clipWall.y=68;
    clipWall.w=55;
    clipWall.h=62;
    SDL_Rect clipIce;
    clipIce.x=9;
    clipIce.y=71;
    clipIce.w=55;
    clipIce.h=62;
    SDL_Rect clipAwake;
    clipAwake.x=16;
    clipAwake.y=147;
    clipAwake.w=43;
    clipAwake.h=45;
    SDL_Rect clipSleep;
    clipSleep.x=0;
    clipSleep.y=0;
    clipSleep.w=72;
    clipSleep.h=64;
    SDL_Rect clipArrowLeft;
    clipArrowLeft.x=159;
    clipArrowLeft.y=224;
    clipArrowLeft.w=43;
    clipArrowLeft.h=38;
    SDL_Rect clipArrowRight;
    clipArrowRight.x=107;
    clipArrowRight.y=224;
    clipArrowRight.w=43;
    clipArrowRight.h=38;
    SDL_Rect clipArrowUp;
    clipArrowUp.x=62;
    clipArrowUp.y=224;
    clipArrowUp.w=43;
    clipArrowUp.h=38;
    SDL_Rect clipArrowDown;
    clipArrowDown.x=15;
    clipArrowDown.y=224;
    clipArrowDown.w=43;
    clipArrowDown.h=38;


    offset initialOff;
    initialOff.xOffset = 16;
    initialOff.yOffset = 33;
    offset sleepOff;
    sleepOff.xOffset = 9;
    sleepOff.yOffset = 23;
    offset wallOff;
    wallOff.xOffset = 9;
    wallOff.yOffset = 25;
    offset iceOff;
    offset awakeOff;
    offset arrowOff;

    int coefy = 52;
    int coefx = 60;

    /**************************************
     * Initialisations liées à la grille et au lvl
     * ************************************/

    // Version 3
    int lvl = 1;
    level grille;
    initLevel(lvl,grille);

    /****************************************
     * Autres initialisations
     * **************************************/

    SDL_Event event, eventM;
    coordCartesiennes mouseDown, mouseDownReleased, swipe;
    int Etat_Jeu=Menu;
    bool quit = false;
    int dir = Null;
    bool outOfGrid=false;

    int j = 0;
    int k = 0;



    while (!quit){

        SDL_Flip(screen);

        switch(Etat_Jeu){
        case Menu:

            SDL_PollEvent(&event);

            if(event.type==SDL_QUIT){
                quit=true;
            }
            if(dynamicButton(fondAccueil2,fondAccueil1,screen,BOUTON_MIDDLE_X,BOUTON_MIDDLE_Y,BOUTON_RAYON,0,0,0,0,NULL,NULL,event)){
                Etat_Jeu=Play;
            }

            break;

        case Play:

            applySurface(0,0,fondJeu,screen,NULL);
            SDL_PollEvent(&eventM);

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            // Version 3

            showGrid(wallOff,iceOff,awakeOff,sleepOff,initialOff,arrowOff,
                     coefx, coefy,
                     imgWall,imgIce,imgSleep,imgAwake, screen,
                     imgaLeft,imgaRight,imgaUp,imgaDown,
                     clipWall,clipIce,clipSleep,clipAwake,
                     clipArrowRight,clipArrowLeft,clipArrowDown,clipArrowUp,
                     grille);




            dir=direction(eventM,mouseDown,mouseDownReleased,swipe);
            j=hitboxMonster(grille,mouseDown,coefx,coefy,initialOff.xOffset,initialOff.yOffset,k);

            if(dir != Null && j!= -1)
            {
                updateLevel(grille,j,dir,outOfGrid,screen,initialOff,clipAwake,imgAwake,coefx,coefy);
            }

            if(grille.nbMonsterSleeping==0){
               // cout << "Vous avez gagné" << endl;
               // cout << "Avec " << i << " coups." << endl;
                // Passe au niveau suivant
            }else if(outOfGrid){
                //cout << "Vous etes sorti!!" << endl;
                // Passe à l'état "perdu" avec l'écran de défaite
                // Etat_Jeu=Lost;
            }


        break;

        case Lost:

             // Affiche l'écran perdu
        break;
    }
}

SDL_FreeSurface(screen);
SDL_FreeSurface(imgWall);
SDL_FreeSurface(imgIce);
SDL_FreeSurface(imgAwake);
SDL_FreeSurface(imgSleep);
SDL_FreeSurface(fondAccueil1);
SDL_FreeSurface(fondAccueil2);
SDL_FreeSurface(fondJeu);

return 0;
}

