#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <iostream>
#include "array"

const int NB_MAX_OBJECT = 45;

const int TAILLE_LIGNE = 9;
const int TAILLE_COLONNE = 5;

enum {STANDARD,SLEEPING,DEAD,WALL,ICE};

struct object{
    int type;
    int x;
    int y;
};


struct level{
    std::array<object,NB_MAX_OBJECT> tabMonster;
    int nbMonster;
    std::array<object,NB_MAX_OBJECT> tabWall;
    int nbWall;
    std::array<object,NB_MAX_OBJECT> tabIce;
    int nbIce;
};

void initLevel2(int lvl, level & grille);

#endif