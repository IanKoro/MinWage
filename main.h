#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include "SDLGraphics.h"
#include "Input.h"
#include "Timer.h"
#include "menuclass.h"
#include "indoors.h"
//function prototypes

void handleKeyboardInput();
void gameloop(int randTiles[]);

void exitGame();

void drawGrass(int randTiles[]);
void screenBlackAnim();
void drawOverlay();
void showXY();
void mapChange(int chx, int chy);

void pauseState();

int collideRockTest(int chX, int chY);

void displayMenu();
void initMenu();

//global vars
extern bool gameIsRunning;
extern SDLGraphics *game_graphics;
extern Input* game_input;
extern Timer* game_timer;
extern menuClass *gameMenu;
extern IndoorHandler *gameIndoors;

extern 	bool inMenu;

#endif
