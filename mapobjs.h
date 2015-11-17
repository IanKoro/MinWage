#ifndef MAPOBJS_H
#define MAPOBJS_H

#include "gameobjs.h"


extern GameObject game_rock;
extern GameObject game_bigrock;
extern GameObject game_tree;
extern GameObject game_shrub;
extern GameObject game_bar;
extern GameObject game_apartment;

extern SDL_Surface* grassTiles;
extern SDL_Surface* fullGrass;
extern SDL_Surface* blackTile;
extern SDL_Surface* sepBar;
extern SDL_Surface* playerMask;


extern SDL_Surface* tempOVERHEAD;
extern SDL_Surface* indoorDesk;

extern SDL_Surface* indoorWayTop;
extern SDL_Surface* indoorWayBottom;
extern SDL_Surface* indoorWayLeft;
extern SDL_Surface* indoorWayRight;

extern SDL_Surface* dollarSprite;



extern SDL_Surface* deskMan;

void setupTiles();


extern int tiledMapBlank[300];
    
#endif
