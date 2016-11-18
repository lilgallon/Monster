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

        if (eventM.type == SDL_MOUSEBUTTONUP)
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

    if(dir==Up && ligne-1>=0)
    {
       while(ligne-1>=0 && !exit)
       {
           if(grille[ligne-1][colonne]==0)
           {
               cout << "Test UP rien après" << endl;
               grille[ligne][colonne]=Void;
               ligne--;
               grille[ligne][colonne]=Awake;
           }
           else if(grille[ligne-1][colonne]==Ice)
           {
               grille[ligne+1][colonne] = Void;
               grille[ligne][colonne] =  Awake;
               grille[ligne-1][colonne] =  Void;
               exit=true;
           }else if(grille[ligne-1][colonne]==Wall)
           {
               cout << "Test UP wall après" << endl;
               grille[ligne+1][colonne] = Void;
               grille[ligne][colonne] =  Awake;
               exit=true;
           }
           else
           {
               exit=true;
           }
       }
       if(ligne-1<0)
       {
           alive=false;
       }
    }
    else if (dir==Down && ligne+1<TAILLE_LIGNE)
    {
        while(ligne+1<TAILLE_LIGNE && !exit)
        {
            if(grille[ligne+1][colonne]==0)
            {
                grille[ligne][colonne]=Void;
                ligne++;
                grille[ligne][colonne]=Awake;
            }
            else if(grille[ligne+1][colonne]==Ice)
            {
                grille[ligne-1][colonne] = Void;
                grille[ligne][colonne] =  Awake;
                grille[ligne+1][colonne] =  Void;
                exit=true;
            }
            else if(grille[ligne+1][colonne]==Wall)
            {
                grille[ligne-1][colonne] = Void;
                grille[ligne][colonne] =  Awake;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }
        if(ligne+1>=TAILLE_LIGNE)
        {
            alive=false;
        }

    }
    else if (dir==Left && colonne-1>=0)
    {
        while(colonne-1>=0 && !exit)
        {
            if(grille[ligne][colonne-1]==Void)
            {
                grille[ligne][colonne]=Void;
                colonne--;
                grille[ligne][colonne]=Awake;
            }
            else if(grille[ligne][colonne-1]==Ice)
            {
                grille[ligne][colonne+1]=Void;
                grille[ligne][colonne] =  Awake;
                grille[ligne][colonne-1] =  Void;
                exit=true;
            }
            else if(grille[ligne][colonne-1]==Wall)
            {
                grille[ligne][colonne+1]=Void;
                grille[ligne][colonne] =  Awake;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }
        if(colonne-1<0)
        {
            alive=false;
        }
    }
    else if (dir==Right && colonne+1<TAILLE_COLONNE)
    {
        while(ligne+1<TAILLE_COLONNE && !exit)
        {
            if(grille[ligne][colonne+1]==Void)
            {
                grille[ligne][colonne]=Void;
                colonne++;
                grille[ligne][colonne]=Awake;
            }
            else if(grille[ligne][colonne+1]==Ice)
            {
                grille[ligne][colonne-1]=Void;
                grille[ligne][colonne] =  Awake;
                grille[ligne][colonne+1] =  Void;
                exit=true;
            }
            else if(grille[ligne][colonne+1]==Wall)
            {
                grille[ligne][colonne-1]=Void;
                grille[ligne][colonne] =  Awake;
                exit=true;
            }
            else
            {
                exit=true;
            }
        }
        if(ligne+1>=TAILLE_COLONNE)
        {
            alive=false;
        }
    }
    return alive;
}
