#include <cstdlib>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <array>

#include "level.h"
#include "display.h"
#include "movement.h"


using namespace std;

const int BUTTON_RADIUS=50;
const int BOUTON_MIDDLE_X=92+BUTTON_RADIUS ;
const int BOUTON_MIDDLE_Y=256+BUTTON_RADIUS;

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 568;
const int SCREEN_BPP = 32;
const int NB_LEVEL = 6;

enum {Menu,Play,GameOver};



int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    /****************************************
     * Initialisation pour les images
     * **************************************/
    SDL_Surface *backgroundHomeDefault, *backgroundHomeAlternative;
    SDL_Surface *backgroundInGame;
    SDL_Surface *screen;
    SDL_Surface *imgObject;
    SDL_Surface *transition, *endgame;

    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

    backgroundInGame=loadImage("background.bmp");
    backgroundHomeDefault=loadImage("menu.bmp");
    backgroundHomeAlternative=loadImage("menu_play.bmp");
    imgObject = loadImageWithColorKey("sprite.bmp",255,255,255);
    transition = loadImage("winSprite.bmp");
    endgame = loadImage("winEndSprite.bmp");


    /**************************************
     * Initialisations liées à la grid et au lvl
     * ************************************/

    // Version 3
    int lvl = 1;
    level grid;
    initLevel(lvl,grid);

    /****************************************
     * Autres initialisations
     * **************************************/

    SDL_Event event, eventM;
    coordCartesian mouseDown, mouseDownReleased, swipe;
    int Game_State=Menu;
    bool quit = false;
    int dir = Null;
    bool outOfGrid=false;

    int monsterId = -1;
    // k est un incrément comme i pourrait l'etre
    int k = 0;



    while (!quit){
        SDL_Flip(screen);

        switch(Game_State){
        case Menu:

            while(SDL_PollEvent(&event)){
            }


            if(event.type==SDL_QUIT){
                quit=true;
            }
            if(dynamicButton(backgroundHomeAlternative,backgroundHomeDefault,screen,BOUTON_MIDDLE_X,BOUTON_MIDDLE_Y,BUTTON_RADIUS,0,0,0,0,NULL,NULL,event)){
                Game_State=Play;
            }

            break;

        case Play:

            applySurface(0,0,backgroundInGame,screen,NULL);

            while (SDL_PollEvent(&eventM)){

            }

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            // Version 3

            showGrid(imgObject,screen,grid);

            dir=direction(eventM,mouseDown,mouseDownReleased,swipe);
            monsterId=hitboxMonster(grid,mouseDown,k);

            if(dir != Null && monsterId!= -1)
            {
                updateLevel(grid,monsterId,dir,outOfGrid,screen,imgObject,backgroundInGame);
                dir = Null;
            }
            if(overCircle(93,531,26)){
                initLevel(lvl,grid);
            }


            if(grid.nbMonsterSleeping==0){
                applySurface(0,0,backgroundInGame,screen,NULL);
                showGrid(imgObject,screen,grid);
                SDL_Flip(screen);
                SDL_Delay(200);
                lvl ++;
                if(lvl>NB_LEVEL){
                    Game_State=GameOver;
                }else{
                    applySurface(0,0,transition,screen,NULL);
                    SDL_Flip(screen);
                    dir = Null;
                    SDL_Delay(1000);
                    initLevel(lvl,grid);
                }

            }else if(outOfGrid){
                initLevel(lvl,grid);
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
    SDL_FreeSurface(backgroundHomeDefault);
    SDL_FreeSurface(backgroundHomeAlternative);
    SDL_FreeSurface(backgroundInGame);

    return 0;
}

