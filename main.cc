// used for the "NULL" value
#include <cstdlib>

// The SDL library
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// For the arrays
#include <array>

// Local files
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
const int NB_LEVEL = 7;

enum {Menu,Play,GameOver};



int main()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    /****************************************
     * Images initializations
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
     * Initializations linked to the level
     * ************************************/
    int lvl = 1;
    level grid;
    initLevel(lvl,grid);

    /****************************************
     * Other initializations
     * **************************************/

    SDL_Event eventM;
    coordCartesian mouseDown, mouseDownReleased, swipe;
    int Game_State=Menu;
    bool quit = false;
    int dir = Null;
    bool outOfGrid=false;

    int monsterId = -1;
    // k is used for the loop inside the function "hitbox monster"
    int k = 0;



    while (!quit){

        switch(Game_State){
        case Menu:

            while(SDL_PollEvent(&eventM)){}

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            // If we click on the dynamic button, the game state changes to "play"
            if(dynamicButton(backgroundHomeAlternative,backgroundHomeDefault,screen,BOUTON_MIDDLE_X,BOUTON_MIDDLE_Y,BUTTON_RADIUS,0,0,0,0,NULL,NULL,eventM)){
                Game_State=Play;
            }

            break;

        case Play:

            applySurface(0,0,backgroundInGame,screen,NULL);

            while (SDL_PollEvent(&eventM)){}

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            showGrid(imgObject,screen,grid);

            dir=direction(eventM,mouseDown,mouseDownReleased,swipe);
            monsterId=hitboxMonster(grid,mouseDown,k);

            // If the user swiped the mouse over a monster
            if(dir != Null && monsterId!= -1)
            {
                // The grid updates itself with the information of the direction and the monster selected
                updateLevel(grid,monsterId,dir,outOfGrid,screen,imgObject,backgroundInGame);
                dir = Null;
            }
            // If the user click on the reset button, in-game, the level initializes itself
            if(overCircle(93,531,26) && eventM.type==SDL_MOUSEBUTTONDOWN){
                initLevel(lvl,grid);
            }

            // If the is no more monsters sleeping, the level changes after a little delay
            if(grid.nbMonsterSleeping==0){
                applySurface(0,0,backgroundInGame,screen,NULL);
                showGrid(imgObject,screen,grid);
                SDL_Flip(screen);
                SDL_Delay(200);
                lvl ++;
                // If it was the last level, the game state changes to "GameOver"
                if(lvl>NB_LEVEL){
                    Game_State=GameOver;
                }else{
                    // Otherwise, the level changes and the level initializes itself according to the level
                    applySurface(0,0,transition,screen,NULL);
                    SDL_Flip(screen);
                    dir = Null;
                    SDL_Delay(1000);
                    initLevel(lvl,grid);
                }

            // Otherwise, the level initialize itself (when the monster is out of the grid)
            }else if(outOfGrid){
                initLevel(lvl,grid);
                outOfGrid = false;
            }


            break;

        case GameOver:

            while (SDL_PollEvent(&eventM)){}

            applySurface(0,0,endgame,screen,NULL);

            if(eventM.type==SDL_QUIT){
                quit=true;
            }

            break;
        }
        SDL_Flip(screen);

    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(imgObject);
    SDL_FreeSurface(backgroundHomeDefault);
    SDL_FreeSurface(backgroundHomeAlternative);
    SDL_FreeSurface(backgroundInGame);
    SDL_FreeSurface(transition);
    SDL_FreeSurface(endgame);

    return 0;
}

