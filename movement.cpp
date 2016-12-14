#include <SDL/SDL.h>
#include "movement.h"
#include "level.h"
#include "display.h"

using namespace std;

/****************** Nom de la fonction **********************
* suppOccurenceIce                                          *
******************** Auteur , Dates *************************
* Lilian GALLON, 12/12/16                                   *
********************* Description ***************************
* Supprime une occurence d'un tableau                       *
*********************** Entrées *****************************
* LA grid, et l'indice de la glace à effacer              *
*********************** Sorties *****************************
* -                                                         *
************************************************************/

void suppOccIce(level &grid,int idIce){
    for(int i=0; i<grid.nbIce ; i++){
        grid.tabIce[idIce+i]=grid.tabIce[idIce+1+i];
    }
}



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
int direction(SDL_Event &eventM, coordCartesian &mouseDown, coordCartesian mouseDownReleased, coordCartesian swipe)
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
* Deteecte si la souris clique sur un monster               *
*********************** Entrées *****************************
* la grid, les coordonnées de la souris lors d'un clique  *
* la taille x/y d'une case, et l'offset de l'image          *
*********************** Sorties *****************************
* l'indice du monster détécté -1 sinon                      *
************************************************************/
int hitboxMonster(level grid, coordCartesian mouseDown, int &k)
{
    int j=-1;
    bool onMonster=false;

    if( k<grid.nbMonster && !onMonster )
    {
        if (    grid.tabMonster[k].l*coefy+initialOff.yOffset <= mouseDown.y
                && (grid.tabMonster[k].l+1)*coefy+initialOff.yOffset >= mouseDown.y
                && grid.tabMonster[k].c*coefx+initialOff.xOffset <= mouseDown.x
                && (grid.tabMonster[k].c+1)*coefx+initialOff.xOffset >= mouseDown.x
                && grid.tabMonster[k].type==STANDARD)
        {
            onMonster=true;
            j=k;
        }
        k++;
    }
    if(k>=grid.nbMonster)
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
* monster                                                   *
*********************** Entrées *****************************
* La direction du monster                                   *
*********************** Sorties *****************************
* Les coefficients de la direction du monster               *
*************************************************************/

coordgrid coefDir(int dir){
    coordgrid coef;
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
* Met à jour la grid et anime le déplacement d'un monster *
************************ Entrées ****************************
* La structure level, la direction choisie,                 *
* d'id du monster à déplacer, et une variable indiquant si  *
* le monster est sorti de la grid                         *
*********************** Sorties *****************************
* -                                                          *
*************************************************************/


void updateLevel(level &grid,int monsterId, int dir, bool &outOfGrid, SDL_Surface *screen, SDL_Surface *imgObject, SDL_Surface *fondJeu){

    coordgrid monster;
    monster.l=grid.tabMonster[monsterId].l;
    monster.c=grid.tabMonster[monsterId].c;
    bool exit = false;
    int lineCoef;
    int columnCoef;

    // Faire des if pour trouver les coef selon dir
    columnCoef=coefDir(dir).c;
    lineCoef=coefDir(dir).l;

    while(!exit){

        for(int i=0;i<grid.nbArrow;i++){
            if(grid.tabArrow[i].l==monster.l+lineCoef && grid.tabArrow[i].c==monster.c+columnCoef){
                monster.c=monster.c+columnCoef;
                monster.l=monster.l+lineCoef;
                anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                dir=grid.tabArrow[i].type;
                columnCoef=coefDir(dir).c;
                lineCoef=coefDir(dir).l;
                grid.tabMonster[monsterId].l=monster.l;
                grid.tabMonster[monsterId].c=monster.c;
                anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
            }
        }

        if(monster.l+lineCoef==TAILLE_LINE || monster.l+lineCoef==-1 || monster.c+columnCoef==TAILLE_COLUMN || monster.c+columnCoef==-1){
            anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
            outOfGrid=true;
            exit = true;
        }

        // On vérifie si il ya un monster sur le passage
        for(int i=0;i<grid.nbMonster+grid.nbMonsterSleeping;i++){
            if(grid.tabMonster[i].type==STANDARD && monsterId!=i){
                if(grid.tabMonster[i].l==monster.l+lineCoef && grid.tabMonster[i].c==monster.c+columnCoef){
                anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                exit = true;
                }
            }
            if(grid.tabMonster[i].type==SLEEPING && monsterId!=i){
                if(grid.tabMonster[i].l==monster.l+lineCoef && grid.tabMonster[i].c==monster.c+columnCoef){
                    anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                    grid.tabMonster[i].type=STANDARD;
                    grid.nbMonsterSleeping --;
                    grid.nbMonster ++;
                    exit = true;
                }
            }
        }

        // On vérifie si il y a un mur sur le passage
        for(int i=0;i<grid.nbWall;i++){
            if(grid.tabWall[i].l==monster.l+lineCoef && grid.tabWall[i].c==monster.c+columnCoef){
                anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                exit = true;
            }
        }

        for(int i=0;i<grid.nbIce;i++){
            if(grid.tabIce[i].l==monster.l+lineCoef && grid.tabIce[i].
                    c==monster.c+columnCoef
                    && monster.l==grid.tabMonster[monsterId].l
                    && monster.c==grid.tabMonster[monsterId].c){
                exit = true;
            }else if(grid.tabIce[i].l==monster.l+lineCoef && grid.tabIce[i].c==monster.c+columnCoef){
                anime(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                suppOccIce(grid,i);
                grid.nbIce = grid.nbIce - 1;
                exit = true;
            }
        }
        if(!exit){
            monster.c=monster.c+columnCoef;
            monster.l=monster.l+lineCoef;
        }
    }

    grid.tabMonster[monsterId].l=monster.l;
    grid.tabMonster[monsterId].c=monster.c;


}