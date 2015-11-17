#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <map>
#include <SDL/SDL.h>
#include "SDLGraphics.h"
#include "Input.h"


#include "Timer.h"
#include "menuclass.h"
#include "indoors.h"
#include "indoorPlayer.h"

#include "SDLGraphics.h"
#include "SDL_collide.h"

#include "gameobjs.h"
#include "mapobjs.h"



#include "maps.h"
#include "inventory.h"

#include "makeMap.h"

#define FRAMES_PER_SECOND	60
#define MOVE_SIZE			3

//function prototypes

void handleKeyboardInput();
void gameloop(int randTiles[]);
void exitMessage(std::string exitMsg);
void exitGame();

void drawGrass(int randTiles[]);
void screenBlackAnim();
void drawOverlay();
void showXY();
void mapChange(int chx, int chy);

void showTitle();

void pauseState();

int collideMapObjTest(int chX, int chY);



void displayMenu();
void initMenu();

int collidedWith(int collideItem);

void drawStats();

//global vars
extern std::map <int, GameObject> AllGameObjects;
extern std::vector <Coords> mapObjLocations;
extern bool gameIsRunning;
extern SDLGraphics *game_graphics;
extern Input* game_input;
extern Timer game_timer;
extern menuClass *gameMenu;
extern IndoorHandler *gameIndoors;

extern IndoorPlayer playerAbove;

extern SDL_Event game_event;


extern 	bool inMenu;

extern Player p1;
extern AllMaps fullMaps;
extern IndoorPlayer playerAbove;
extern PlayerInventory playerStuff;

#endif
