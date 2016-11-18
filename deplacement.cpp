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

int deplacement(SDL_Event &eventM, coord &mouseDown, coord mouseDownReleased, coord swipe)
{
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

                // Droite
                if (mouseDownReleased.x>0 && swipe.x>swipe.y)
                {
                    mouseDownReleased.x=0;
                    return Right;
                }

                // Gauche
                else if (mouseDownReleased.x<0 && swipe.x>swipe.y)
                {
                    mouseDownReleased.x=0;
                    return Left;
                }

                // Bas
                else if (mouseDownReleased.y>0 && swipe.y>swipe.x)
                {
                    mouseDownReleased.y=0;
                    return Down;
                }

                // Haut
                else if (mouseDownReleased.y<0 && swipe.y>swipe.x)
                {
                    mouseDownReleased.y=0;
                    return Up;
                }

            }

        }
        return Null;
}

