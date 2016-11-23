#include <iostream>
#include <sstream>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <array>

#include "level.h"
#include "affichage.h"
#include "deplacement.h"

using namespace std;

const int BOUTON_RAYON=50;
const int BOUTON_MIDDLE_X=92+BOUTON_RAYON ;
const int BOUTON_MIDDLE_Y=256+BOUTON_RAYON;

const int ECRAN_WIDTH = 320;
const int ECRAN_HEIGHT = 568;
const int ECRAN_BPP = 32;
const int NB_LEVEL = 6;

enum {Menu,Play};

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

    screen=SDL_SetVideoMode(ECRAN_WIDTH,ECRAN_HEIGHT,ECRAN_BPP,SDL_SWSURFACE);

    fondJeu=loadImage("background.bmp");
    fondAccueil1=loadImage("menu.bmp");
    fondAccueil2=loadImage("menu_play.bmp");
    imgWall = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgIce = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgAwake = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgSleep = loadImageWithColorKey("sprite.bmp",255,255,255);



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

    offset initialOff;
    initialOff.xOffset = 33;
    initialOff.yOffset = 16;
    offset sleepOff;
    sleepOff.xOffset = 23;
    sleepOff.yOffset = 8;
    offset wallOff;
    wallOff.xOffset = 25;
    wallOff.yOffset = 9;
    offset iceOff;
    offset awakeOff;

    int coefy = 60;
    int coefx = 52;

    /**************************************
     * Initialisations liées à la grille et au lvl
     * ************************************/

    int lvl = 1; // Démarre su le niveau 1 au début
    objectTab sleepTab, awakeTab, wallTab, iceTab;
    grilleLevel grille;
    initLevel(lvl,grille,TAILLE_COLONNE,TAILLE_LIGNE,wallTab,iceTab,awakeTab,sleepTab);


    /****************************************
     * Autres initialisations
     * **************************************/

    SDL_Event event, eventM;
    coord mouseDown, mouseDownReleased, swipe;
    int Etat_Jeu=Menu;
    bool quit = false;
    int dir = Null;



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

            showGrid(wallOff,iceOff,awakeOff,sleepOff,initialOff,coefx, coefy,imgWall,imgIce,imgSleep,imgAwake,screen,clipWall,clipIce,clipSleep,clipAwake,grille);
            dir = direction(eventM,mouseDown,mouseDownReleased,swipe);
            if (dir != Null){
                if(!monsterMovement(grille,dir,awakeTab[0].ligne,awakeTab[0].colonne)){
                    cout << "Lose" << endl;
                    quit = true;
                }else if(sleepTab[0].nb==0){
                    cout << "Win" << endl;
                    quit = true;
                }
            }

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

