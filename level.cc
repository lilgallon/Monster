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
        grille.tabWall[0].x=2;
        grille.tabWall[0].y=3;
        grille.nbWall=1;
        // Ice
        grille.tabIce[0].x=7;
        grille.tabIce[0].y=0;
        grille.nbIce=1;
        // Awake monster
        grille.tabMonster[0].x=5;
        grille.tabMonster[0].y=3;
        grille.tabMonster[0].type=STANDARD;
        // Sleeping monster
        grille.tabMonster[1].x=3;
        grille.tabMonster[1].y=0;
        grille.tabMonster[1].type=SLEEPING;

        grille.tabMonster[2].x=6;
        grille.tabMonster[2].y=1;
        grille.tabMonster[2].type=SLEEPING;

        grille.nbMonster=3;

        break;
    }

}




