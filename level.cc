using namespace std;
#include "level.h"

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

void initLevel2(int lvl, level & grille)
{

    //initTabLevel1(grille,taille_colonne,taille_ligne);

    // Initialise les positions des objets
    switch(lvl){
    case 1 :
        // grille[ligne][colonne]
        // Wall
        grille.tabWall[0].l=5;
        grille.tabWall[0].c=4;

        grille.tabWall[1].l=0;
        grille.tabWall[1].c=2;

        grille.tabWall[2].l=5;
        grille.tabWall[2].c=0;

        grille.tabWall[3].l=8;
        grille.tabWall[3].c=2;
        grille.nbWall=4;
        // Ice
        grille.tabIce[0].l=7;
        grille.tabIce[0].c=0;
        grille.nbIce=1;
        // Awake monster
        grille.tabMonster[0].l=5;
        grille.tabMonster[0].c=2;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].l=3;
        grille.tabMonster[1].c=0;
        grille.tabMonster[1].type=SLEEPING;

        grille.tabMonster[2].l=6;
        grille.tabMonster[2].c=1;
        grille.tabMonster[2].type=SLEEPING;


        grille.nbMonsterSleeping=2;
        grille.nbMonster=3;

        break;
    }

}




