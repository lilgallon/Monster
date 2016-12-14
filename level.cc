using namespace std;
#include "level.h"
#include "movement.h"

// Structure level

/****************** Nom de la fonction **********************
* initTabLevel                                              *
******************** Auteur , Dates *************************
* Lilian GALLON, 09/11/16                                   *
********************* Description ***************************
* Initialise la "grid" selon le niveau                    *
*********************** Entrées *****************************
* La grid, et le niveau                                   *
*********************** Sorties *****************************
* -                                                         *
************************************************************/

void initLevel(int lvl, level & grid)
{

    // Initialise les positions des objets
    grid.nbArrow=0;
    grid.nbIce=0;
    grid.nbMonster=0;
    grid.nbMonsterSleeping=0;
    grid.nbWall=0;

    switch(lvl){
    case 1 :

        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=1;
        grid.tabMonster[1].c=4;
        grid.tabMonster[1].type=SLEEPING;
        // Nb objects
        grid.nbMonsterSleeping=1;
        grid.nbMonster=1;
        break;

    case 2 :
        // Awake monster
        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=1;
        grid.tabMonster[1].c=4;
        grid.tabMonster[1].type=SLEEPING;
        // Nb objects
        grid.nbMonsterSleeping=1;
        grid.nbMonster=1;
        break;

    case 3 :
        // Awake monster
        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=6;
        grid.tabMonster[1].c=3;
        grid.tabMonster[1].type=SLEEPING;
        // Wall
        grid.tabWall[0].l=1;
        grid.tabWall[0].c=4;
        // Nb objects
        grid.nbMonsterSleeping=1;
        grid.nbMonster=1;
        grid.nbWall=1;
        break;
    case 4 :
        // Awake monster
        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=6;
        grid.tabMonster[1].c=3;
        grid.tabMonster[1].type=SLEEPING;
        // Arrow
        grid.tabArrow[0].l=1;
        grid.tabArrow[0].c=3;
        grid.tabArrow[0].type=Down;
        // Nb objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=1;
        grid.nbArrow=1;
        break;
    case 5 :
        // Awake monster
        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=6;
        grid.tabMonster[1].c=3;
        grid.tabMonster[1].type=SLEEPING;
        // Arrow
        grid.tabArrow[0].l=1;
        grid.tabArrow[0].c=3;
        grid.tabArrow[0].type=Down;
        // Ice
        grid.tabIce[0].l=3;
        grid.tabIce[0].c=3;
        // Nb objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=1;
        grid.nbArrow=1;
        grid.nbIce=1;
        break;
    case 6 :
        // Awake monster
        grid.tabMonster[0].l=1;
        grid.tabMonster[0].c=1;
        grid.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grid.tabMonster[1].l=6;
        grid.tabMonster[1].c=3;
        grid.tabMonster[1].type=SLEEPING;
        // Arrow
        grid.tabArrow[0].l=1;
        grid.tabArrow[0].c=3;
        grid.tabArrow[0].type=Down;
        // Ice
        grid.tabIce[0].l=3;
        grid.tabIce[0].c=3;
        // Nb objects
        grid.nbMonster=1;
        grid.nbMonsterSleeping=1;
        grid.nbArrow=1;
        grid.nbIce=1;
        break;
    }
}

