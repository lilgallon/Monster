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

enum {Menu,Play,GameOver};



int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    /****************************************
     * Initialisation pour les images
     * **************************************/
    SDL_Surface *fondAccueil1, *fondAccueil2;
    SDL_Surface *fondJeu;
    SDL_Surface *screen;
    SDL_Surface *imgObject;
    SDL_Surface *transition, *endgame;

    screen=SDL_SetVideoMode(ECRAN_WIDTH,ECRAN_HEIGHT,ECRAN_BPP,SDL_SWSURFACE);

    fondJeu=loadImage("background.bmp");
    fondAccueil1=loadImage("menu.bmp");
    fondAccueil2=loadImage("menu_play.bmp");
    imgObject = loadImageWithColorKey("sprite.bmp",255,255,255);
    transition = loadImage("winSprite.bmp");
    endgame = loadImage("winEndSprite.bmp");


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

            while(SDL_PollEvent(&event)){
            }


            if(event.type==SDL_QUIT){
                quit=true;
            }
            if(dynamicButton(fondAccueil2,fondAccueil1,screen,BOUTON_MIDDLE_X,BOUTON_MIDDLE_Y,BOUTON_RAYON,0,0,0,0,NULL,NULL,event)){
                Etat_Jeu=Play;
            }

            break;

        case Play:

            applySurface(0,0,fondJeu,screen,NULL);

            while (SDL_PollEvent(&eventM)){

            }

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            // Version 3

            showGrid(imgObject,screen,grille);

            dir=direction(eventM,mouseDown,mouseDownReleased,swipe);
            j=hitboxMonster(grille,mouseDown,k);

            if(dir != Null && j!= -1)
            {
                updateLevel(grille,j,dir,outOfGrid,screen,imgObject,fondJeu);
                dir = Null;
            }
            if(overCircle(93,531,26)){
                initLevel(lvl,grille);
            }

            if(grille.nbMonsterSleeping==0){

                lvl ++;
                if(lvl>NB_LEVEL){
                    Etat_Jeu=GameOver;
                }else{
                    applySurface(0,0,transition,screen,NULL);
                    SDL_Flip(screen);
                    dir = Null;
                    SDL_Delay(1000);
                    initLevel(lvl,grille);
                }

            }else if(outOfGrid){
                cout << "out" << endl;
                initLevel(lvl,grille);
            }


            break;

        case GameOver:

            while (SDL_PollEvent(&eventM)){

            }

        applySurface(0,0,endgame,screen,NULL);
        SDL_Flip(screen);

        if(eventM.type==SDL_QUIT){
            quit=true;
        }

            break;
        }

    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(imgObject);
    SDL_FreeSurface(fondAccueil1);
    SDL_FreeSurface(fondAccueil2);
    SDL_FreeSurface(fondJeu);

    return 0;
}

