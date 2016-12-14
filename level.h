#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "array"

const int NB_MAX_OBJECT = 45;

const int TAILLE_LINE = 9;
const int TAILLE_COLUMN = 5;

enum {STANDARD,SLEEPING,DEAD,WALL,ICE};

struct object{
    int type;
    int l;
    int c;
};


struct level{
    std::array<object,NB_MAX_OBJECT> tabMonster;
    int nbMonster;
    int nbMonsterSleeping;
    std::array<object,NB_MAX_OBJECT> tabArrow;
    int nbArrow;
    std::array<object,NB_MAX_OBJECT> tabWall;
    int nbWall;
    std::array<object,NB_MAX_OBJECT> tabIce;
    int nbIce;
};

void initLevel(int lvl, level & grid);

#endif