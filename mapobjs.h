#ifndef MAPOBJS_H
#define MAPOBJS_H

//extern SDL_Surface* grassTiles[4];

extern SDL_Surface* grassTiles;
extern SDL_Surface* blackTile;
extern SDL_Surface* rockTile;
extern SDL_Surface* bigRockTile;
extern SDL_Surface* playerMask;

extern SDL_Surface* barBldg;

extern SDL_Surface* apartBldg;
extern SDL_Surface* apartBldgMask;

extern SDL_Surface* tempOVERHEAD;

void setupTiles();


extern int tiledMapBlank[300];
    
#endif
