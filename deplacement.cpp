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
* columnMvt                                                 *
******************** Auteur , Dates *************************
* Lilian GALLON & Tristan Renaudon, 07/12/16                *
********************* Description ***************************
* Calcule les coordonnées d'arrivée du déplacement du       *
*  monstre                                                  *
*********************** Entrées *****************************
* La structure level, la direction choisie,                 *
* d'id du monstre à déplacer                                *
*********************** Sorties *****************************
* Les coordonnées d'arrivée du monstre                      *
*************************************************************/

void updateLevel(level &grille,int monsterId, int dir){

    coord2 monstre;
    monstre.l=grille.tabMonster[monsterId].l;
    monstre.c=grille.tabMonster[monsterId].c;
    bool exit = false;
    int ligneCoef;
    int colonneCoef;

    // Faire des if pour trouver les coef selon dir
    if(dir==Up){ligneCoef = -1; colonneCoef=0;}
    else if(dir==Down){ligneCoef = 1; colonneCoef=0;}
    else if(dir==Left){ligneCoef=0; colonneCoef=-1;}
    else if(dir==Right){ligneCoef=0; colonneCoef=1;}


    while(monstre.l+ligneCoef<TAILLE_LIGNE && monstre.l+ligneCoef>=0
          && monstre.c+colonneCoef<TAILLE_COLONNE && monstre.c+colonneCoef>=0
          && !exit){

        //pb colonne

        // On vérifie si il ya un monstre sur le passage
        for(int i=0;i<grille.nbMonster;i++){
            if(grille.tabMonster[i].type==STANDARD && monsterId!=i){
                if(grille.tabMonster[i].l==monstre.l+ligneCoef && grille.tabMonster[i].c==monstre.c+colonneCoef){
//                    monstre.c=monstre.c-colonneCoef;
//                    monstre.l=monstre.l-ligneCoef;
                    exit = true;
                }
            }
            if(grille.tabMonster[i].type==SLEEPING && monsterId!=i){
                if(grille.tabMonster[i].l==monstre.l+ligneCoef && grille.tabMonster[i].c==monstre.c+colonneCoef){
                    grille.tabMonster[i].type=STANDARD;
                    grille.nbMonsterSleeping --;
//                    monstre.c=monstre.c-colonneCoef;
//                    monstre.l=monstre.l-ligneCoef;
                    exit= true;
                }
            }
        }

        // On vérifie si il y a un mur sur le passage
        for(int i=0;i<grille.nbWall;i++){
            if(grille.tabWall[i].l==monstre.l+ligneCoef && grille.tabWall[i].c==monstre.c+colonneCoef){
                // On détecte qu'il y a un monstre juste à côté en x (colonne)
//                monstre.c=monstre.c-colonneCoef;
//                monstre.l=monstre.l-ligneCoef;
                exit = true;
            }
        }

        for(int i=0;i<grille.nbIce;i++){
            if(grille.tabIce[i].l==monstre.l+ligneCoef && grille.tabIce[i].
                    c==monstre.c+colonneCoef){
                // pour faire zizi dur profs go faire décalage gauche
                grille.tabIce[i].l=-1;
                grille.tabIce[i].c=-1;
                grille.nbIce --;
//                monstre.c=monstre.c-colonneCoef;
//                monstre.l=monstre.l-ligneCoef;
               exit = true;
            }
        }
        if(!exit){
            monstre.c=monstre.c+colonneCoef;
            monstre.l=monstre.l+ligneCoef;
        }
    }

    grille.tabMonster[monsterId].l=monstre.l;
    grille.tabMonster[monsterId].c=monstre.c;

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
*************************************************************/
/*
bool monsterMovement(grilleLevel &grille, int &dir, int &ligne, int &colonne)
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

    if(dir!=Null && ligne+j>=0 && ligne+j<=TAILLE_LIGNE && colonne+i>=0 && colonne+i<=TAILLE_COLONNE && !exit)
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
               grille[ligne+j][colonne+i]=Void;
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
       dir = Null;
    }
    return alive;
}
*/