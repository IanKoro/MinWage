#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <cstdlib>
#include <algorithm>


#include "SDLGraphics.h"
#include "Input.h"
#include "Timer.h"
#include "gameobjs.h"
#include "mapobjs.h"




#define SPRITE_WIDTH   32
#define SPRITE_HEIGHT  32
//34x52

#define SCREEN_WIDTH  640 // 20 * 32
#define SCREEN_HEIGHT 480 // 15 * 32


//function prototypes
void handleKeyboardInput();
void gameloop(int randTiles[]);
void drawGrass(int randTiles[]);
void screenBlackAnim();

//global vars
bool gameIsRunning = true;
SDLGraphics *game_graphics = NULL;
Input* game_input = NULL;
Timer* game_timer = NULL;


Player p1;

int main()
{
	
	srand ( time(NULL) );
	
	game_graphics = new SDLGraphics(SCREEN_WIDTH, SCREEN_HEIGHT, "Min Wage", 0,90,0);
	game_timer = new Timer();
	game_input = new Input();


	
	//There's got to be a better way to do this (generating random tiles for the grass)...
	//This is probably a better idea: generate the entire backdrop as an SDL_Surface that can be drawn 
	//														each time it is needed?
	int randTiles[(SCREEN_HEIGHT / 32) * (SCREEN_WIDTH / 32)];
	int i = 0;
	for (i = 0; i < (SCREEN_HEIGHT / 32) * (SCREEN_WIDTH / 32); i++)
	{
		randTiles[i] = rand() % 4;
	}

	gameloop(randTiles);


	delete game_timer;
	delete game_input;
	delete game_graphics;

	return 0;
}

void gameloop(int randTiles[])
{
	float frame = 0.0;
	int dir = 0;
	
	while (gameIsRunning)
	{
		
		float deltaTime = game_timer->timeSinceLastFrame();

		game_input->readInput();

		if (game_input->windowClosed())
		{
			gameIsRunning = false;
		}

		handleKeyboardInput();

		dir = p1.getDir() * 32;

		if (p1.isWalk())
		{
			frame += 0.05;
			if (frame > 3.0)
			{
				frame = 0.0;
			}
		}
		else 
		{
			frame = 0.0;
		}

		game_graphics->beginScene();
		drawGrass(randTiles);
		game_graphics->drawSprite(p1.playerBMP, (int)frame * 32, dir, p1.getX(), p1.getY(), 32, 32);
		
	    //game_graphics->drawText("This tutorial rules!", 12, 250, 100, 200, 0, 0, 0, 0, 0);
		game_graphics->endScene();

		// Give the computer a break (optional)
		SDL_Delay(10);
		
	}
}

void drawGrass(int randTiles[])
{

	for (int x = 0; x < SCREEN_WIDTH/SPRITE_WIDTH; x++) 
	{
		for (int y = 0; y < SCREEN_HEIGHT/SPRITE_HEIGHT; y++) 
		{
			//randTile = rand() * 4;

			game_graphics->drawSprite(grassTiles, randTiles[x*y] * 32, 0, x*32, y*32, 32, 32);

			//game_graphics->drawSprite(grassTiles, 2 * 32, 0, x*32, y*32, 32, 32);	
				//SDL_BlitSurface(grass, NULL, screen, &rcGrass);
		}
	}	
}

void screenBlackAnim()
{

	int tileX, tileY;
	
	int tileCount = 0;
	
	std::vector <Coords> screenTiles((SCREEN_WIDTH / 32) * (SCREEN_HEIGHT / 32));

	for (int x = 0; x < SCREEN_WIDTH/SPRITE_WIDTH; x++) 
	{
		for (int y = 0; y < SCREEN_HEIGHT/SPRITE_HEIGHT; y++) 
		{
			screenTiles.at(tileCount).setX(x);
			screenTiles.at(tileCount).setY(y);
			tileCount++;
		}
	}


	
	//for (int count = 0; count < screenTiles.size(); count++)
	//{
	//	printf("X: %d    Y: %d\n", screenTiles.at(count).getX(), screenTiles.at(count).getY());
	//}
	std::random_shuffle(screenTiles.begin(), screenTiles.end());

	
	for (int count = 0; count < screenTiles.size(); count++)
	{
			game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 32, screenTiles.at(count).getY() * 32, 32, 32);
			game_graphics->endScene();
			SDL_Delay(2);
	}
	game_graphics->endScene();
	SDL_Delay(1000);
	
}

void handleKeyboardInput()
{
   bool* keysHeld = game_input->getInput();

   if (keysHeld[SDLK_ESCAPE])
   {
      gameIsRunning = false;
   }

   if (keysHeld[SDLK_LEFT])
   {
      p1.changeX(-1);
      p1.startWalk(); 
      p1.setDir(PLAYER_LEFT);
    }
	else if (keysHeld[SDLK_RIGHT])
	{
      p1.changeX(1);
      p1.startWalk(); 
      p1.setDir(PLAYER_RIGHT);
	}
	
	if (keysHeld[SDLK_UP])
	{
      p1.changeY(-1);
      p1.startWalk(); 
      p1.setDir(PLAYER_UP);
	}
	else if (keysHeld[SDLK_DOWN])
	{
      p1.changeY(1);
      p1.startWalk();
      p1.setDir(PLAYER_DOWN); 
	}

	if (!keysHeld[SDLK_DOWN] && !keysHeld[SDLK_UP] && !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT])
	{
		p1.stopWalk();
	}
	
	if (keysHeld[SDLK_b])
	{
		screenBlackAnim();
	}
}

