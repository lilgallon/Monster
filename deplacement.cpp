#include <SDL/SDL.h>
#include <iostream>
#include "deplacement.h"

using namespace std;

int valAbsolue(int val)
{
    if(val<=0)
    {
        val=-val;
    }
    return val;
}

int deplacement()
{
    SDL_Event eventM;

    coord mouseDown;
    coord mouseDownReleased;
    coord swipe;

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

