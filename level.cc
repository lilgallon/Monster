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
          grille[ligne][colonne] = 0;
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
void initLevel(int lvl, grilleLevel & grille, int taille_colonne, int taille_ligne, int nbMonster)
{

   initTabLevel(grille,taille_colonne,taille_ligne);

   switch(lvl){
       case 1 :
       // grille[ligne][colonne]
           nbMonster = 1;
           grille[2][3]= Wall;
           grille[7][0]= Ice;
           grille[5][3]= Awake;
           grille[3][0]= Sleep;
           grille[6][4]= Sleep;
       break;
   }

}



