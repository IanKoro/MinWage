#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <cstdlib>
#include <algorithm>


#include "SDLGraphics.h"
#include "SDL_collide.h"
#include "Input.h"
#include "Timer.h"
#include "gameobjs.h"
#include "mapobjs.h"


//function prototypes
void handleKeyboardInput();
void gameloop(int randTiles[]);
void drawGrass(int randTiles[]);
void screenBlackAnim();
void drawOverlay();


//global vars
bool gameIsRunning = true;
SDLGraphics *game_graphics = NULL;
Input* game_input = NULL;
Timer* game_timer = NULL;

std::vector <Coords> rockLocations;

bool runOnce = false;

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


	
	setupTiles();

	gameloop(randTiles);

	screenBlackAnim();

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
		if (runOnce == true)
		{
			for (int rockCount = 0; rockCount < rockLocations.size(); rockCount++)
			{
				if(SDL_CollidePixel(playerMask, p1.getX(), p1.getY(), rockTile, rockLocations.at(rockCount).getX() * 32, rockLocations.at(rockCount).getY() * 32))
				{
						game_graphics->drawText("Collide!", 12, 250, 100, 200, 0, 0, 0, 0, 0);
				}
			}
		}


		drawOverlay();
		printf("x: %d y: %d\n", rockLocations.at(0).getX(), rockLocations.at(0).getY());
		game_graphics->drawSprite(p1.playerBMP, (int)frame * 32, dir, p1.getX(), p1.getY(), 32, 32);
		
	    
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
	
	//std::vector <Coords> screenTiles((SCREEN_WIDTH / 32) * (SCREEN_HEIGHT / 32));
	std::vector <Coords> screenTiles((SCREEN_WIDTH / 8) * (SCREEN_HEIGHT / 8));


	//for (int x = 0; x < SCREEN_WIDTH/SPRITE_WIDTH; x++)
	for (int x = 0; x < SCREEN_WIDTH/8; x++) 
	{
		//for (int y = 0; y < SCREEN_HEIGHT/SPRITE_HEIGHT; y++)
		for (int y = 0; y < SCREEN_HEIGHT/8; y++) 
		{
			screenTiles.at(tileCount).setX(x);
			screenTiles.at(tileCount).setY(y);
			tileCount++;
		}
	}

	std::random_shuffle(screenTiles.begin(), screenTiles.end());
	
	for (int count = 0; count < screenTiles.size(); count++)
	{
			//game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 32, screenTiles.at(count).getY() * 32, 32, 32);
			game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 8, screenTiles.at(count).getY() * 8, 8, 8);
			game_graphics->endScene();
			//SDL_Delay(2);
	}
	game_graphics->endScene();
	SDL_Delay(500);
	
}

void drawOverlay()
{
	
	int mapPlace = 0;

	Coords tempCoords;
	
	for (int y = 0; y < SCREEN_HEIGHT/SPRITE_HEIGHT; y++) 
	{
		for (int x = 0; x < SCREEN_WIDTH/SPRITE_WIDTH; x++) 
		{
			if (overlayMap01[mapPlace] == 1)
			{
				game_graphics->drawSprite(rockTile, 0, 0, x * 32, y * 32, 32, 32);
				if (runOnce == false)
				{
					
					printf("2. rock at x: %d y: %d\n", x, y);
					tempCoords.setX(x);
					tempCoords.setY(y);
					rockLocations.push_back(tempCoords);
				}
			}
			else if (overlayMap01 == 0)
			{}
			mapPlace++;
		}
	}	
	if (runOnce == false)
	{
		runOnce = true;
		printf("No. rocks: %d\n", rockLocations.size());
		for (int x = 0; x < rockLocations.size(); x++)
		{
			printf("Rock X: %d   Y: %d\n", rockLocations.at(x).getX(), rockLocations.at(x).getY());
		}
	}
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

