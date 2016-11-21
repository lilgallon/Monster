#include <SDL/SDL.h>
#include <iostream>
#include "deplacement.h"
#include "level.h"

using namespace std;


/****************** Nom de la fonction **********************
* absoluteValue                                             *
******************** Auteur , Dates *************************
* Tristan RENAUDON, 09/11/16                                *
********************* Description ***************************
* Convertie une valeur en valeur absolue                    *
*********************** Entrées *****************************
* Une valeur entière                                        *
*********************** Sorties *****************************
* La valeur absolue                                         *
************************************************************/
int absoluteValue(int val)
{
    if(val<=0)
    {
        val=-val;
    }
    return val;
}


/****************** Nom de la fonction **********************
* direction                                                 *
******************** Auteur , Dates *************************
* Tristan RENAUDON, 09/11/16                                *
********************* Description ***************************
* Donne la direction choisie en fonction du mouvement de la *
* souris                                                    *
*********************** Entrées *****************************
* Une gestion d'évènement, les coordonnées de la souris     *
* clic enfoncé + clic relaché, valeur absolue de la distance*
*********************** Sorties *****************************
* Direction choisie                                         *
************************************************************/
int direction(SDL_Event &eventM, coord &mouseDown, coord mouseDownReleased, coord swipe)
{
        if (eventM.type == SDL_MOUSEBUTTONDOWN)
        {
            mouseDown.x=eventM.button.x;
            mouseDown.y=eventM.button.y;
        }
        else if (eventM.type == SDL_MOUSEBUTTONUP)
        {
            if (eventM.button.button==SDL_BUTTON_LEFT)
            {
                mouseDownReleased.x=eventM.button.x-mouseDown.x;
                mouseDownReleased.y=eventM.button.y-mouseDown.y;

                swipe.x=absoluteValue(mouseDownReleased.x);
                swipe.y=absoluteValue(mouseDownReleased.y);

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


/****************** Nom de la fonction **********************
* monsterMovement                                           *
******************** Auteur , Dates *************************
* Tristan RENAUDON, 09/11/16                                *
********************* Description ***************************
* Déplace le monstre en fonction des evènements du jeux     *
*********************** Entrées *****************************
* La matrice, la direction choisie, la ligne et la colonne  *
* du monstre                                                *
*********************** Sorties *****************************
* Le tableau modifié, si le joueur est en vie               *
************************************************************/
bool monsterMovement(grilleLevel &grille, int dir, int &ligne, int &colonne)
{
    bool exit=false;
    bool alive=true;
    int i=0,j=0;

    if(dir==Up)
    {
        j=-1;
        i=0;
    }
    else if(dir==Down)
    {
        j=1;
        i=0;
    }
    else if(dir==Left)
    {
        i=-1;
        j=0;
    }
    else if(dir==Right)
    {
        i=1;
        j=0;
    }

    if(dir!=Null && ligne+j>=0 && ligne+j<=TAILLE_LIGNE && colonne+i>=0 && colonne+i<=TAILLE_COLONNE)
    {
       while(ligne+j>=0 && ligne+j<=TAILLE_LIGNE && colonne+i>=0 && colonne+i<TAILLE_COLONNE && !exit)
       {
           if(grille[ligne+j][colonne+i]==Void)
           {
               cout << "void" << endl;

               grille[ligne][colonne]=Void;
               ligne=ligne+j;
               colonne=colonne+i;
               grille[ligne][colonne]=Awake;
           }
           else if(grille[ligne+j][colonne+i]==Ice)
           {
               cout << "ice" << endl;

               grille[ligne+j][colonne+i] =  Void;
               exit=true;
           }
           else if(grille[ligne+j][colonne+i]==Sleep)
           {
               cout << "sleep" << endl;
               exit=true;
           }
           else if(grille[ligne+j][colonne+i]==Wall)
           {
               cout << "mur" << endl;
               exit=true;
           }
           else
           {
               exit=true;
           }
       }
       if(ligne+j<0 && ligne+j>=TAILLE_LIGNE && colonne+i<0 && colonne+i>=TAILLE_COLONNE)
       {
           alive=false;
       }
    }
    return alive;
}
