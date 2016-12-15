// SDL Library
#include <SDL/SDL.h>

#include "movement.h"
#include "level.h"
#include "display.h"

using namespace std;

/****************** Function's name *************************
* suppOccIce                                                *
******************** Authors , Dates ************************
* Lilian GALLON, 12/12/16                                   *
********************* Description ***************************
* Deletes an occurence of an array                          *
*********************** Entries *****************************
* The grid and the index of the ice to delete               *
*********************** Output ******************************
* -                                                         *
************************************************************/

void suppOccIce(level &grid,int idIce){
    // Browses the grid by shifting every occurence to the left
    for(int i=0; i<grid.nbIce ; i++){
        grid.aryIce[idIce+i]=grid.aryIce[idIce+1+i];
    }
}

/****************** Function's name *************************
* absoluteValue                                             *
******************** Authors , Dates ************************
* Tristan RENAUDON, 09/11/16                                *
********************* Description ***************************
* Converts a value to an absolute one                       *
*********************** Entries *****************************
* An integer value                                          *
*********************** Output ******************************
* An absolute value                                         *
************************************************************/
int absoluteValue(int val)
{
    if(val<=0)
    {
        val=-val;
    }
    return val;
}

/****************** Function's name *************************
* direction                                                 *
******************** Authors , Dates ************************
* Tristan RENAUDON, 09/11/16                                *
********************* Description ***************************
* Gives the direction chosen according to the mouse movement*
*********************** Entries *****************************
* An event variable, the mouse position when clicked, and   *
* released, the absolute value of the distance              *
*********************** Output ******************************
* Chosen direction                                          *
************************************************************/
int direction(SDL_Event &eventM, coordCartesian &mouseDown, coordCartesian mouseDownReleased, coordCartesian swipe)
{
    // Gets the positions of the mouse when pushed
    if (eventM.type == SDL_MOUSEBUTTONDOWN){
        if (eventM.button.button==SDL_BUTTON_LEFT)
        {
            mouseDown.x=eventM.button.x;
            mouseDown.y=eventM.button.y;
        }
    }
    // gets the positions of the mouse when released
    else if (eventM.type == SDL_MOUSEBUTTONUP)
    {
        // It works only if the click was made on the left button
        if (eventM.button.button==SDL_BUTTON_LEFT)
        {
            // Gets the difference between those values
            mouseDownReleased.x=eventM.button.x-mouseDown.x;
            mouseDownReleased.y=eventM.button.y-mouseDown.y;

            // Gets a swipe value from the precendent ones
            swipe.x=absoluteValue(mouseDownReleased.x);
            swipe.y=absoluteValue(mouseDownReleased.y);

            // Right
            if (mouseDownReleased.x>0 && swipe.x>swipe.y)
            {
                mouseDownReleased.x=0;
                return Right;
            }

            // Left
            else if (mouseDownReleased.x<0 && swipe.x>swipe.y)
            {
                mouseDownReleased.x=0;
                return Left;
            }

            // Down
            else if (mouseDownReleased.y>0 && swipe.y>swipe.x)
            {
                mouseDownReleased.y=0;
                return Down;
            }

            // Up
            else if (mouseDownReleased.y<0 && swipe.y>swipe.x)
            {
                mouseDownReleased.y=0;
                return Up;
            }

        }

    }
    return Null;
}


/****************** Function's name *************************
* hitboxMonster                                             *
******************** Authors , Dates ************************
* Tristan RENAUDON, 09/12/16                                *
********************* Description ***************************
* Detects if the mouse click was made on a monster, and     *
* which one                                                 *
*********************** Entries *****************************
* The level, the mouse positions when a click was made, and *
* the offset of the background (origin positions)           *
*********************** Output ******************************
* The index of the monster detected, -1 otherwise           *
************************************************************/
int hitboxMonster(level grid, coordCartesian mouseDown, int &k)
{
    int j=-1;
    bool onMonster=false;

    // Loops the monster's array
    if( k<grid.nbMonster && !onMonster )
    {
        // If the index "k" corresponds to a standard monster
        if (    grid.aryMonster[k].l*coefy+initialOff.yOffset <= mouseDown.y
                && (grid.aryMonster[k].l+1)*coefy+initialOff.yOffset >= mouseDown.y
                && grid.aryMonster[k].c*coefx+initialOff.xOffset <= mouseDown.x
                && (grid.aryMonster[k].c+1)*coefx+initialOff.xOffset >= mouseDown.x
                && grid.aryMonster[k].type==STANDARD)
        {
            // We conclude that we are on a monster
            // and its index is "k"
            onMonster=true;
            j=k;
        }
        // If the k index did not correspond to the monster when the user clicked
        // we increment k to check for the next index
        k++;
    }
    // If we are at the end of the monster's array, we reset k to 0 to continue checking
    if(k>=grid.nbMonster)
    {
        k=0;
    }
    // Returns j which is -1 if we did not find a monster on the mouse cursor
    // Otherwise it returns the index of the monster
    return j;
}

/****************** Function's name *************************
* coefDir                                                   *
******************** Authors , Dates ************************
* Lilian GALLON , 09/12/16                                  *
********************* Description ***************************
* Calculates the coefficients according to the direction of *
* the monster which will be used after                      *
*********************** Entries *****************************
* The direction of the monster                              *
*********************** Output ******************************
* The coefficients of the direction of the monster          *
*************************************************************/
coordgrid coefDir(int dir){
    coordgrid coef;
    if(dir==Up){coef.l = -1; coef.c=0;}
    else if(dir==Down){coef.l = 1; coef.c=0;}
    else if(dir==Left){coef.l=0; coef.c=-1;}
    else if(dir==Right){coef.l=0; coef.c=1;}
    return coef;
}

/****************** Function's name *************************
* updateLevel                                               *
******************** Authors , Dates ************************
* Lilian GALLON & Tristan Renaudon, 07/12/16                *
********************* Description ***************************
* Updates the grid according to the direction of the monster*
* and animates the movement the monster to move             *
* Met à jour la grid et animate le déplacement d'un monster   *
************************ Entries ****************************
* The level, the index of the monster to moven the direction*
* a variable which returns true if the monster is out of the*
* grid, the surface where the level will be displayed, the  *
* sprite, and the background of the game                    *
*********************** Output *****************************
* -                                                          *
*************************************************************/


void updateLevel(level &grid,int monsterId, int dir, bool &outOfGrid, SDL_Surface *screen, SDL_Surface *imgObject, SDL_Surface *fondJeu){


    bool exit = false;

    // We get the different steps (1,-1,0)
    int columnCoef=coefDir(dir).c;
    int lineCoef=coefDir(dir).l;

    // The initial position of the monster to move is temporarily stored
    coordgrid monster;
    monster.l=grid.aryMonster[monsterId].l;
    monster.c=grid.aryMonster[monsterId].c;

    while(!exit){


        // Browses the arrows' array
        for(int i=0;i<grid.nbArrow;i++){
            // If we find an arrow in the next cell
            if(grid.aryArrow[i].l==monster.l+lineCoef && grid.aryArrow[i].c==monster.c+columnCoef){
                // We move forward to the arrow
                monster.c=monster.c+columnCoef;
                monster.l=monster.l+lineCoef;
                // Then, we animate the movement according to :
                // The initial position: grid.aryMonster[monsterId].l/c:
                // The final position: monster.l/c
                animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                // Then we change the direction
                dir=grid.aryArrow[i].type;
                // By changing the steps
                columnCoef=coefDir(dir).c;
                lineCoef=coefDir(dir).l;
                // Then we update the grid with the current position
                grid.aryMonster[monsterId].l=monster.l;
                grid.aryMonster[monsterId].c=monster.c;
            }
        }

        // Browses the monsters's array
        for(int i=0;i<grid.nbMonster+grid.nbMonsterSleeping;i++){
            // If we find a monster in the NEXT cell
            // so the case with the same monster, when i=idMonster isn't a problem
            if(grid.aryMonster[i].type==STANDARD){
                // If it is a standard monster, we just stop the movement, and we animate the monster
                if(grid.aryMonster[i].l==monster.l+lineCoef && grid.aryMonster[i].c==monster.c+columnCoef){
                    animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                    exit = true;
                }
            }
            if(grid.aryMonster[i].type==SLEEPING){
                // If it is a sleepong monster, we update the type of the monster to a "standard" one
                if(grid.aryMonster[i].l==monster.l+lineCoef && grid.aryMonster[i].c==monster.c+columnCoef){
                    // We animate before updating the level
                    animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                    // We set the monster to a standard one
                    grid.aryMonster[i].type=STANDARD;
                    // We remove one monster sleeping
                    grid.nbMonsterSleeping --;
                    // And we add one more normal
                    grid.nbMonster ++;
                    exit = true;
                }
            }
        }

        // If the next cell of the monster is out of the grid
        if(monster.l+lineCoef==LINE_SIZE || monster.l+lineCoef==-1 || monster.c+columnCoef==COLUMN_SIZE || monster.c+columnCoef==-1){
            // We animate the movement
            animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
            // We set that the monster is out of the grid
            outOfGrid=true;
            // We go out of the while loop
            exit = true;
        }

        // If there is a wall, we stop it
        for(int i=0;i<grid.nbWall;i++){
            if(grid.aryWall[i].l==monster.l+lineCoef && grid.aryWall[i].c==monster.c+columnCoef){
                animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                exit = true;
            }
        }

        for(int i=0;i<grid.nbIce;i++){
            // If the monster find an ice block just next to him before moving
            // it does nothing
            // the difference is made by :
            // monster.l==grid.aryMonster[monsterId].l &&
            // monster.c==grid.aryMonster[monsterId].c
            if(grid.aryIce[i].l==monster.l+lineCoef && grid.aryIce[i].
                    c==monster.c+columnCoef
                    && monster.l==grid.aryMonster[monsterId].l
                    && monster.c==grid.aryMonster[monsterId].c){
                exit = true;
                // otherwise, if the monster already moved and we find an ice block
            }else if(grid.aryIce[i].l==monster.l+lineCoef && grid.aryIce[i].c==monster.c+columnCoef){
                // We animate the movement
                animate(grid, monster,screen,imgObject,dir, monsterId,fondJeu);
                // We delete an ice from its array
                suppOccIce(grid,i);
                // We remove one ice from the total number of ice
                grid.nbIce = grid.nbIce - 1;
                exit = true;
            }
        }
        // If we did not exit, we increment the positions of the monster
        if(!exit){
            monster.c=monster.c+columnCoef;
            monster.l=monster.l+lineCoef;
        }
    }

    // If the monster moved, it will check if there are monsters sleeping next to him
    // if so, it will update those to the state of "STANDARD" instead of "SLEEPING"
    if (grid.aryMonster[monsterId].l!=monster.l || grid.aryMonster[monsterId].c!=monster.c){
        coordgrid step;
        // Browses enum : Left, Right, Up, Down
        for(int i = Left; i != Down; i++ ){
            // Get differents steps according to the direction
            step.c=coefDir(i).c;
            step.l=coefDir(i).l;
            // Browses the array of the monsters
            for(int j=0; j<grid.nbMonster+grid.nbMonsterSleeping;j++){
                // It checks if there is a monster sleeping next to him
                if (grid.aryMonster[j].l==monster.l+step.l && grid.aryMonster[j].c==monster.c+step.c
                        && grid.aryMonster[j].type==SLEEPING){
                    // We set the monster to a standard one
                    grid.aryMonster[j].type=STANDARD;
                    // We remove one monster sleeping
                    grid.nbMonsterSleeping --;
                    // And we add one more normal
                    grid.nbMonster ++;
                }
            }
        }
    }

    // When everything is okay, we update the grid with the new monster position
    grid.aryMonster[monsterId].l=monster.l;
    grid.aryMonster[monsterId].c=monster.c;


}