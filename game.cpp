#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "game.h"
#include "SDLGraphics.h"
#include "Input.h"
#include "Timer.h"
#include "gameobjs.h"

//global vars
bool gameIsRunning = true;
SDLGraphics *game_graphics = NULL;
Input* game_input = NULL;
Timer* game_timer = NULL;
