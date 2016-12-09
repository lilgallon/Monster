#include <SDL/SDL.h>
#include <iostream>
#include "deplacement.h"
#include "level.h"
#include "affichage.h"

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
int direction(SDL_Event &eventM, coordCartesiennes &mouseDown, coordCartesiennes mouseDownReleased, coordCartesiennes swipe)
{
    if (eventM.type == SDL_MOUSEBUTTONDOWN){
        if (eventM.button.button==SDL_BUTTON_LEFT)
        {
            mouseDown.x=eventM.button.x;
            mouseDown.y=eventM.button.y;
        }
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
* hitboxMonster                                             *
******************** Auteur , Dates *************************
* Tristan RENAUDON, 09/12/16                                *
********************* Description ***************************
* Deteecte si la souris clique sur un monstre               *
*********************** Entrées *****************************
* la grille, les coordonnées de la souris lors d'un clique  *
* la taille x/y d'une case, et l'offset de l'image          *
*********************** Sorties *****************************
* l'indice du monstre détécté -1 sinon                      *
************************************************************/
int hitboxMonster(level grille, coordCartesiennes mouseDown, int coefx, int coefy, int offsetX, int offsetY, int &k)
{
    int j=-1;
    bool onMonster=false;

    if( k<grille.nbMonster && !onMonster )
    {
        if (    grille.tabMonster[k].l*coefy+offsetY <= mouseDown.y
                && (grille.tabMonster[k].l+1)*coefy+offsetY >= mouseDown.y
                && grille.tabMonster[k].c*coefx+offsetX <= mouseDown.x
                && (grille.tabMonster[k].c+1)*coefx+offsetX >= mouseDown.x
                && grille.tabMonster[k].type==STANDARD)
        {
            onMonster=true;
            j=k;
            cout << "tru" << endl;
        }
        k++;
    }
    if(k>=grille.nbMonster)
    {
        k=0;
    }
    return j;
}

/****************** Nom de la fonction **********************
* coefDir                                                   *
******************** Auteur , Dates *************************
* Lilian GALLON , 09/12/16                                  *
********************* Description ***************************
* Calcule les coefficients en fonction de la direction du   *
* monstre                                                   *
*********************** Entrées *****************************
* La direction du monstre                                   *
*********************** Sorties *****************************
* Les coefficients de la direction du monstre               *
*************************************************************/

coordGrille coefDir(int dir){
    coordGrille coef;
    if(dir==Up){coef.l = -1; coef.c=0;}
    else if(dir==Down){coef.l = 1; coef.c=0;}
    else if(dir==Left){coef.l=0; coef.c=-1;}
    else if(dir==Right){coef.l=0; coef.c=1;}
    return coef;
}

/****************** Nom de la fonction **********************
* updateLevel                                               *
******************** Auteur , Dates *************************
* Lilian GALLON & Tristan Renaudon, 07/12/16                *
********************* Description ***************************
* Met à jour la grille et anime le déplacement d'un monstre *
************************ Entrées ****************************
* La structure level, la direction choisie,                 *
* d'id du monstre à déplacer, et une variable indiquant si  *
* le monstre est sorti de la grille                         *
*********************** Sorties *****************************
* -                                                          *
*************************************************************/


void updateLevel(level &grille,int monsterId, int dir, bool &outOfGrid,
                 SDL_Surface *screen, offset initialOff, SDL_Rect clipAwake, SDL_Surface *imgAwake,
                 int coefx, int coefy){

    coordGrille monstre;
    monstre.l=grille.tabMonster[monsterId].l;
    monstre.c=grille.tabMonster[monsterId].c;
    bool exit = false;
    int ligneCoef;
    int colonneCoef;

    // Faire des if pour trouver les coef selon dir
    colonneCoef=coefDir(dir).c;
    ligneCoef=coefDir(dir).l;

    while(!exit){

        for(int i=0;i<grille.nbArrow;i++){
            if(grille.tabArrow[i].l==monstre.l+ligneCoef && grille.tabArrow[i].c==monstre.c+colonneCoef){
                monstre.c=monstre.c+colonneCoef;
                monstre.l=monstre.l+ligneCoef;
                anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
                dir=grille.tabArrow[i].type;
                colonneCoef=coefDir(dir).c;
                ligneCoef=coefDir(dir).l;
                grille.tabMonster[monsterId].l=monstre.l;
                grille.tabMonster[monsterId].c=monstre.c;
                anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
            }
        }

        if(monstre.l+ligneCoef==TAILLE_LIGNE || monstre.l+ligneCoef==-1 || monstre.c+colonneCoef==TAILLE_COLONNE || monstre.c+colonneCoef==-1){
            anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
            outOfGrid=true;
            exit = true;
        }

        // On vérifie si il ya un monstre sur le passage
        for(int i=0;i<grille.nbMonster;i++){
            if(grille.tabMonster[i].type==STANDARD && monsterId!=i){
                if(grille.tabMonster[i].l==monstre.l+ligneCoef && grille.tabMonster[i].c==monstre.c+colonneCoef){
//                    monstre.c=monstre.c-colonneCoef;
//                    monstre.l=monstre.l-ligneCoef;
                    anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
                    exit = true;
                }
            }
            if(grille.tabMonster[i].type==SLEEPING && monsterId!=i){
                if(grille.tabMonster[i].l==monstre.l+ligneCoef && grille.tabMonster[i].c==monstre.c+colonneCoef){
                    grille.tabMonster[i].type=STANDARD;
                    grille.nbMonsterSleeping --;
//                    monstre.c=monstre.c-colonneCoef;
//                    monstre.l=monstre.l-ligneCoef;
                    anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
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
                anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
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
                anime(grille, monstre,initialOff,clipAwake,coefx,coefy,screen,imgAwake,dir, monsterId);
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