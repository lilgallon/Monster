using namespace std;
#include "level.h"
#include "deplacement.h"

// Structure level

/****************** Nom de la fonction **********************
* initTabLevel                                              *
******************** Auteur , Dates *************************
* Lilian GALLON, 09/11/16                                   *
********************* Description ***************************
* Initialise la "grille" selon le niveau                    *
*********************** Entrées *****************************
* La grille, et le niveau                                   *
*********************** Sorties *****************************
* -                                                         *
************************************************************/

void initLevel(int lvl, level & grille)
{

    // Initialise les positions des objets
    grille.nbArrow=0;
    grille.nbIce=0;
    grille.nbMonster=0;
    grille.nbMonsterSleeping=0;
    grille.nbWall=0;

    switch(lvl){
    case 1 :

        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=1;
        grille.tabMonster[1].c=4;
        grille.tabMonster[1].type=SLEEPING;
        // Nb objects
        grille.nbMonsterSleeping=1;
        grille.nbMonster=1;
        break;

    case 2 :
        // Awake monster
        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=1;
        grille.tabMonster[1].c=4;
        grille.tabMonster[1].type=SLEEPING;
        // Nb objects
        grille.nbMonsterSleeping=1;
        grille.nbMonster=1;
        break;

    case 3 :
        // Awake monster
        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=6;
        grille.tabMonster[1].c=3;
        grille.tabMonster[1].type=SLEEPING;
        // Wall
        grille.tabWall[0].l=1;
        grille.tabWall[0].c=4;
        // Nb objects
        grille.nbMonsterSleeping=1;
        grille.nbMonster=1;
        grille.nbWall=1;
        break;
    case 4 :
        // Awake monster
        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=6;
        grille.tabMonster[1].c=3;
        grille.tabMonster[1].type=SLEEPING;
        // Arrow
        grille.tabArrow[1].l=1;
        grille.tabArrow[1].c=3;
        grille.tabArrow[1].type=Down;
        // Nb objects
        grille.nbMonster=1;
        grille.nbMonsterSleeping=1;
        grille.nbArrow=1;
        break;
    case 5 :
        // Awake monster
        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=6;
        grille.tabMonster[1].c=3;
        grille.tabMonster[1].type=SLEEPING;
        // Arrow
        grille.tabArrow[1].l=1;
        grille.tabArrow[1].c=3;
        grille.tabArrow[1].type=Down;
        // Ice
        grille.tabIce[0].l=3;
        grille.tabIce[0].c=3;
        // Nb objects
        grille.nbMonster=1;
        grille.nbMonsterSleeping=1;
        grille.nbArrow=1;
        grille.nbIce=1;
        break;
    case 6 :
        // Awake monster
        grille.tabMonster[0].l=1;
        grille.tabMonster[0].c=1;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=6;
        grille.tabMonster[1].c=3;
        grille.tabMonster[1].type=SLEEPING;
        // Arrow
        grille.tabArrow[1].l=1;
        grille.tabArrow[1].c=3;
        grille.tabArrow[1].type=Down;
        // Ice
        grille.tabIce[0].l=3;
        grille.tabIce[0].c=3;
        // Nb objects
        grille.nbMonster=1;
        grille.nbMonsterSleeping=1;
        grille.nbArrow=1;
        grille.nbIce=1;
        break;
    }
}

