#include <SDL/SDL.h>
#include <iostream>
#include "deplacement.h"
#include "level.h"

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

void deplacementMonstre(grilleLevel &grille, int dir, int ligne, int colonne)
{
    bool exit=false;

    if(dir==Up && ligne-1>=0)
    {
       while(ligne-1>=0 && !exit)
       {
           if(grille[ligne-1][colonne]==0)
           {
               ligne--;
           }
           else if(grille[ligne-1][colonne]==2)
           {
               ligne--;
               exit=true;
           }
           else
           {
               exit=true;
           }
       }
    }
    else if (dir==Down && ligne+1<TAILLE_LIGNE)
    {
        while(ligne+1<TAILLE_LIGNE && !exit)
        {
            if(grille[ligne+1][colonne]==0)
            {
                ligne++;
            }
            else if(grille[ligne+1][colonne]==2)
            {
                ligne++;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }

    }
    else if (dir==Left && colonne-1>=0)
    {
        while(colonne-1>=0 && !exit)
        {
            if(grille[ligne][colonne-1]==0)
            {
                colonne--;
            }
            else if(grille[ligne][colonne-1]==2)
            {
                colonne--;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }
    }
    else if (dir==Right && colonne+1<TAILLE_COLONNE)
    {
        while(ligne+1<TAILLE_COLONNE && !exit)
        {
            if(grille[ligne][colonne+1]==0)
            {
                colonne++;
            }
            else if(grille[ligne][colonne+1]==2)
            {
                colonne++;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }
    }
}
