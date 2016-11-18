#include <iostream>
#include <sstream>

#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <array>

#include "level.h"
#include "monster.h"
#include "affichage.h"

using namespace std;

const int BOUTON_RAYON=50;
const int BOUTON_MIDDLE_X=92+BOUTON_RAYON ;
const int BOUTON_MIDDLE_Y=256+BOUTON_RAYON;

const int ECRAN_WIDTH = 320;
const int ECRAN_HEIGHT = 568;
const int ECRAN_BPP = 32;
const int NB_LEVEL = 6;

// Variables pour l'etat du jeu
//const int Menu = 1;
//const int Jeu = 2;
enum {Menu,Jeu};

int valAbsolue(int val)
{
    if(val<=0)
    {
        val=-val;
    }
    return val;
}

struct coord{
    int x=0;
    int y=0;
};

int swipe(){

    coord mouseDown;
    coord mouseDownReleased;
    coord swipe;
    SDL_Event eventM;

    if (eventM.type == SDL_MOUSEBUTTONDOWN)
    {
        mouseDown.x=eventM.button.x;
        mouseDown.y=eventM.button.y;
    }

    if (eventM.type == SDL_MOUSEBUTTONUP)
    {

        if (eventM.button.button==SDL_BUTTON_LEFT)
        {
            mouseDownReleased.x=eventM.button.x-mouseDown.x;
            mouseDownReleased.y=eventM.button.y-mouseDown.y;

            swipe.x=valAbsolue(mouseDownReleased.x);
            swipe.y=valAbsolue(mouseDownReleased.y);

            if (mouseDownReleased.x>0 && swipe.x>swipe.y)
            {
                cout << "Droite" << endl;
                cout << mouseDownReleased.x << " " << mouseDown.x << endl;
                mouseDownReleased.x=0;
                return 1;
            }
            else if (mouseDownReleased.x<0 && swipe.x>swipe.y)
            {
                cout << "Gauche" << endl;
                cout << mouseDownReleased.x << " " << mouseDown.x << endl;
                mouseDownReleased.x=0;
                return 2;
            }
            else if (mouseDownReleased.y>0 && swipe.y>swipe.x)
            {
                cout << "Bas" << endl;
                cout << mouseDownReleased.y << " " << mouseDown.y << endl;
                mouseDownReleased.y=0;
                return 3;
            }
            else if (mouseDownReleased.y<0 && swipe.y>swipe.x)
            {
                cout << "Haut" << endl;
                cout << mouseDownReleased.y << " " << mouseDown.y << endl;
                mouseDownReleased.y=0;
                return 4;
            }

        }

    }
    return 0;

}

int main()
{
    int Etat_Jeu=Menu;
    bool quit = false;
    bool surPlay = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface *fondAccueil1, *fondAccueil2;
    SDL_Surface *fondJeu;
    SDL_Surface *screen;

    SDL_Surface *imgMur;
    SDL_Surface *imgIce;
    SDL_Surface *imgAwake;
    SDL_Surface *imgSleep;

    SDL_Event event;

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
        int decaly = 0;//40;
        int decalx = 20;//20;
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
    int nbMonster;

    initLevel(lvl,grille,TAILLE_COLONNE,TAILLE_LIGNE,nbMonster);


//        fin test pour la grille


    while (!quit){
        switch(Etat_Jeu){
            case Menu:
            if(surPlay==true)
            {
                applySurface(0,0,fondAccueil2,screen,NULL);
            }
            else if(surPlay==false)
            {
                applySurface(0,0,fondAccueil1,screen,NULL);
            }

            SDL_Flip(screen);


            while(SDL_PollEvent(&event))
            {

                // Gestion des évènements liées aux clics de la souris
                if( event.type == SDL_MOUSEBUTTONDOWN )
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    int dist_x = BOUTON_MIDDLE_X - x;
                    int dist_y = BOUTON_MIDDLE_Y - y;

                    int dist_x_abs;
                    int dist_y_abs;

                    dist_x_abs=valAbsolue(dist_x);
                    dist_y_abs=valAbsolue(dist_y);

                    // Survol de play
                    if(dist_x_abs<=BOUTON_RAYON && dist_y_abs<=BOUTON_RAYON)
                    {
                        // Clic sur play
                        if(event.button.button==SDL_BUTTON_LEFT)
                        {
                            Etat_Jeu= Jeu;
                        }

                    }
                }

                if (event.type == SDL_MOUSEMOTION)
                {
                    int x = event.button.x;
                    int y = event.button.y;

                    int dist_x = BOUTON_MIDDLE_X - x;
                    int dist_y = BOUTON_MIDDLE_Y - y;

                    int dist_x_abs;
                    int dist_y_abs;

                    dist_x_abs=valAbsolue(dist_x);
                    dist_y_abs=valAbsolue(dist_y);

                    if(dist_x_abs<=BOUTON_RAYON && dist_y_abs<=BOUTON_RAYON)
                    {
                        surPlay=true;
                    }
                    else
                    {
                        surPlay=false;
                    }
                }
            }
            break;





             case Jeu:

            applySurface(0,0,fondJeu,screen,NULL);

            initLevel(lvl,grille,TAILLE_COLONNE,TAILLE_LIGNE);
            affichageTerminal(grille,TAILLE_LIGNE,TAILLE_COLONNE);


            while(SDL_PollEvent(&event)){
                if(event.type==SDL_QUIT){
                    quit=true;
                }

                for (int ligne =0; ligne < TAILLE_LIGNE; ligne ++) {
                    for (int colonne =0; colonne < TAILLE_COLONNE; colonne ++) {
                        if(grille[ligne][colonne]==Wall){
                            applySurface(colonne*coefy+decaly,ligne*coefx+decalx,imgMur,screen,&clipWall);
                        }else if(grille[ligne][colonne]==Ice){
                            applySurface(colonne*coefy+decaly,ligne*coefx+decalx,imgIce,screen,&clipIce);
                        }else if(grille[ligne][colonne]==Sleep){
                            applySurface(colonne*coefy+decaly,ligne*coefx+decalx,imgSleep,screen,&clipSleep);
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

