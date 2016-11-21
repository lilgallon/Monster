using namespace std;
#include "level.h"

// Structure level

/****************** Nom de la fonction **********************
* initTabLevel                                              *
******************** Auteur , Dates *************************
* Lilian GALLON, 09/11/16                                   *
********************* Description ***************************
* Initialise la grille en mettant des 0 partout             *
*********************** Entrées *****************************
* La grille, la taille en colonne et la taille en ligne     *
*********************** Sorties *****************************
* -                                                         *
************************************************************/
void initTabLevel(grilleLevel & grille, int taille_colonne, int taille_ligne){

    for (int ligne =0; ligne < taille_ligne; ligne++) {
       for (int colonne =0; colonne < taille_colonne; colonne++) {
          grille[ligne][colonne] = Void;
       }
    }
}



/****************** Nom de la fonction **********************
* initTabLevel                                              *
******************** Auteur , Dates *************************
* Lilian GALLON, 09/11/16                                   *
********************* Description ***************************
* Initialise la grille selon le niveau                      *
*********************** Entrées *****************************
* La grille, la taille en colonne et en ligne, et le niveau *
*********************** Sorties *****************************
* -                                                         *
************************************************************/
//// Fonctions
void initLevel(int lvl, grilleLevel & grille, int taille_colonne, int taille_ligne, objectTab &wallTab, objectTab &iceTab, objectTab &awakeTab, objectTab &sleepTab)
{

    initTabLevel(grille,taille_colonne,taille_ligne);

//    objectTab wall;
//    objectTab ice;
//    objectTab awake;
//    objectTab sleep;

    // Initialise les positions des objets
    switch(lvl){
    case 1 :
        // grille[ligne][colonne]
        // Wall
        wallTab[0].ligne=2; wallTab[0].colonne = 3; wallTab[0].nb=1;
        // Ice
        iceTab[0].ligne = 7; iceTab[0].colonne = 0; iceTab[0].nb=1;
        // Awake monster
        awakeTab[0].ligne = 5; awakeTab[0].colonne =3; awakeTab[0].nb=1;
        // Sleeping monster
        sleepTab[0].ligne=3; sleepTab[0].colonne=0; sleepTab[0].nb=2;
        sleepTab[1].ligne=6; sleepTab[1].colonne=4;

        break;
    }

    // Met les objets dans la grille
    for (int i =0; i < wallTab[0].nb ; i++){
        grille[wallTab[i].ligne][wallTab[i].colonne]=Wall;
    }
    for (int i =0; i < iceTab[0].nb ; i++){
        grille[iceTab[i].ligne][iceTab[i].colonne]=Ice;
    }
    for (int i =0; i < awakeTab[0].nb ; i++){
        grille[awakeTab[i].ligne][awakeTab[i].colonne]=Awake;
    }
    for (int i =0; i < sleepTab[0].nb ; i++){
        grille[sleepTab[i].ligne][sleepTab[i].colonne]=Sleep;
    }

}



