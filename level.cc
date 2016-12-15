using namespace std;
#include "level.h"
#include "movement.h"

// Structure level

/****************** Function's name *************************
* initaryLevel                                              *
******************** Auteur , Dates *************************
* Lilian GALLON, 09/11/16                                   *
********************* Description ***************************
* Initializes the grid according to the level               *
*********************** Entries *****************************
* The grid and the level                                    *
*********************** Output ******************************
* -                                                         *
************************************************************/

void initLevel(int lvl, level & grid)
{

    // Initializes the number of the objects
    grid.nbArrow=0;
    grid.nbIce=0;
    grid.nbMonster=0;
    grid.nbMonsterSleeping=0;
    grid.nbWall=0;

    switch(lvl){
    case 1 :

        grid.aryMonster[0].l=1;
        grid.aryMonster[0].c=1;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster
        grid.aryMonster[1].l=1;
        grid.aryMonster[1].c=4;
        grid.aryMonster[1].type=SLEEPING;
        // Nb of the objects
        grid.nbMonsterSleeping=1;
        grid.nbMonster=1;
        break;

    case 2 :
        // Awake monster
        grid.aryMonster[0].l=1;
        grid.aryMonster[0].c=1;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster
        grid.aryMonster[1].l=6;
        grid.aryMonster[1].c=3;
        grid.aryMonster[1].type=SLEEPING;
        // Wall
        grid.aryWall[0].l=1;
        grid.aryWall[0].c=4;
        // Nb of the objects
        grid.nbMonsterSleeping=1;
        grid.nbMonster=1;
        grid.nbWall=1;
        break;
    case 3 :
        // Awake monster
        grid.aryMonster[0].l=1;
        grid.aryMonster[0].c=1;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster
        grid.aryMonster[1].l=6;
        grid.aryMonster[1].c=3;
        grid.aryMonster[1].type=SLEEPING;
        // Arrow
        grid.aryArrow[0].l=1;
        grid.aryArrow[0].c=3;
        grid.aryArrow[0].type=Down;
        // Nb of the objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=1;
        grid.nbArrow=1;
        break;
    case 4 :
        // Awake monster
        grid.aryMonster[0].l=1;
        grid.aryMonster[0].c=1;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster
        grid.aryMonster[1].l=6;
        grid.aryMonster[1].c=3;
        grid.aryMonster[1].type=SLEEPING;
        // Arrow
        grid.aryArrow[0].l=1;
        grid.aryArrow[0].c=3;
        grid.aryArrow[0].type=Down;
        // Ice
        grid.aryIce[0].l=3;
        grid.aryIce[0].c=3;
        // Nb of the objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=1;
        grid.nbArrow=1;
        grid.nbIce=1;
        break;
    case 5 :
        // Awake monster
        grid.aryMonster[0].l=6;
        grid.aryMonster[0].c=2;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster
        grid.aryMonster[1].l=0;
        grid.aryMonster[1].c=2;
        grid.aryMonster[1].type=SLEEPING;

        grid.aryMonster[2].l=1;
        grid.aryMonster[2].c=3;
        grid.aryMonster[2].type=SLEEPING;

        grid.aryMonster[3].l=1;
        grid.aryMonster[3].c=1;
        grid.aryMonster[3].type=SLEEPING;

        // Nb of the objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=3;

        break;

    case 6 :
        // Awake monster
        grid.aryMonster[0].l=6;
        grid.aryMonster[0].c=2;
        grid.aryMonster[0].type=STANDARD;
        // Sleeping monster

        grid.aryMonster[1].l=1;
        grid.aryMonster[1].c=3;
        grid.aryMonster[1].type=SLEEPING;

        grid.aryMonster[2].l=1;
        grid.aryMonster[2].c=1;
        grid.aryMonster[2].type=SLEEPING;

        grid.aryMonster[3].l=8;
        grid.aryMonster[3].c=1;
        grid.aryMonster[3].type=SLEEPING;

        // Wall
        grid.aryWall[0].l=0;
        grid.aryWall[0].c=2;

        // Nb of the objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=3;
        grid.nbWall=1;

        break;

    }

}

