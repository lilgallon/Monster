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


void initObjet(){

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
void initLevel(int lvl, grilleLevel & grille, int taille_colonne, int taille_ligne, objectTab &wall, objectTab &ice, objectTab &awake, objectTab &sleep)
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
        wall[0].ligne=2; wall[0].colonne = 3; wall[0].nb=1;
        // Ice
        ice[0].ligne = 7; ice[0].colonne = 0; ice[0].nb=1;
        // Awake monster
        awake[0].ligne = 5; awake[0].colonne =3; awake[0].nb=1;
        // Sleeping monster
        sleep[0].ligne=3; sleep[0].colonne=0; sleep[0].nb=2;
        sleep[1].ligne=6; sleep[1].colonne=4;

        break;
    }

    // Met les objets dans la grille
    for (int i =0; i < wall[0].nb ; i++){
        grille[wall[i].ligne][wall[i].colonne]=Wall;
    }
    for (int i =0; i < ice[0].nb ; i++){
        grille[ice[i].ligne][ice[i].colonne]=Ice;
    }
    for (int i =0; i < awake[0].nb ; i++){
        grille[awake[i].ligne][awake[i].colonne]=Awake;
    }
    for (int i =0; i < sleep[0].nb ; i++){
        grille[sleep[i].ligne][sleep[i].colonne]=Sleep;
    }

}



