#include <iostream>
#include <sstream>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <array>

#include "level.h"
#include "monster.h"
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

enum {Menu,Jeu};

int main()
{
    int Etat_Jeu=Menu;
    bool quit = false;
    int dir;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface *fondAccueil1, *fondAccueil2;
    SDL_Surface *fondJeu;
    SDL_Surface *screen;

    SDL_Surface *imgMur;
    SDL_Surface *imgIce;
    SDL_Surface *imgAwake;
    SDL_Surface *imgSleep;

    SDL_Event event, eventM;

    coord mouseDown;
    coord mouseDownReleased;
    coord swipe;

    screen=SDL_SetVideoMode(ECRAN_WIDTH,ECRAN_HEIGHT,ECRAN_BPP,SDL_SWSURFACE);
    fondAccueil1=loadImage("menu.bmp");
    fondAccueil2=loadImage("menu_play.bmp");

    fondJeu=loadImage("background.bmp");

    imgMur = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgIce = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgAwake = loadImageWithColorKey("sprite.bmp",255,255,255);
    imgSleep = loadImageWithColorKey("sprite.bmp",255,255,255);

    // Décalage initial x: 20
    // Décalage initial y: -40
    // Dimensions d'une case: x:60 , y: 50
    // Décalage entre chaque ligne : y: 3
        int decaly = 16;
        int decalx = 33;

        int decalySleep = 8;
        int decalxSleep = 23;

        int decalyWall = 9;
        int decalxWall = 25;

        int coefy = 60;
        int coefx = 52;

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


    // TEst pour la grille
    grilleLevel grille;
    int lvl = 1;


    while (!quit){
        switch(Etat_Jeu){
            case Menu:


            SDL_Flip(screen);


            while(SDL_PollEvent(&event))
            {

                if(event.type==SDL_QUIT){
                    quit=true;
                }

                if(overCircle(BOUTON_MIDDLE_X,BOUTON_MIDDLE_Y,BOUTON_RAYON)){
                    applySurface(0,0,fondAccueil2,screen,NULL);
                    if(event.type==SDL_MOUSEBUTTONDOWN){
                        Etat_Jeu=Jeu;
                    }
                }else{
                    applySurface(0,0,fondAccueil1,screen,NULL);
                }

            }

            break;





             case Jeu:

            applySurface(0,0,fondJeu,screen,NULL);

            initLevel(lvl,grille,TAILLE_COLONNE,TAILLE_LIGNE);
            //affichageTerminal(grille,TAILLE_LIGNE,TAILLE_COLONNE);


            while(SDL_PollEvent(&eventM)){
                if(eventM.type==SDL_QUIT){
                    quit=true;
                }


                dir = direction(eventM,mouseDown,mouseDownReleased,swipe);
                if (dir != Null)
                {
                    cout << dir << endl;
                }


                for (int ligne =0; ligne < TAILLE_LIGNE; ligne ++) {
                    for (int colonne =0; colonne < TAILLE_COLONNE; colonne ++) {
                        if(grille[ligne][colonne]==Wall){
                            applySurface(colonne*coefy+decalyWall,ligne*coefx+decalxWall,imgMur,screen,&clipWall);
                        }else if(grille[ligne][colonne]==Ice){
                            applySurface(colonne*coefy+decaly,ligne*coefx+decalx,imgIce,screen,&clipIce);
                        }else if(grille[ligne][colonne]==Sleep){
                            applySurface(colonne*coefy+decalySleep,ligne*coefx+decalxSleep,imgSleep,screen,&clipSleep);
                        }else if(grille[ligne][colonne]==Awake){
                            applySurface(colonne*coefy+decaly,ligne*coefx+decalx,imgAwake,screen,&clipAwake);
                        }

                    }
                }




              SDL_Flip(screen);
            }


            break;
        }
    }

    return 0;
}

