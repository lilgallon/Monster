#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <array>

const int NB_MAX_OBJECTS = 45;
const int LINE_SIZE = 9;
const int COLUMN_SIZE = 5;

// Differents states of an object
enum {STANDARD,SLEEPING,DEAD,WALL,ICE};

struct object{
    int type;
    // l corresponds to "line"
    int l;
    // c corresponds to "column"
    int c;
};


struct level{
    std::array<object,NB_MAX_OBJECTS> aryMonster;
    int nbMonster;
    int nbMonsterSleeping;

    std::array<object,NB_MAX_OBJECTS> aryArrow;
    int nbArrow;

    std::array<object,NB_MAX_OBJECTS> aryWall;
    int nbWall;

    std::array<object,NB_MAX_OBJECTS> aryIce;
    int nbIce;
};

void initLevel(int lvl, level & grid);

#endif