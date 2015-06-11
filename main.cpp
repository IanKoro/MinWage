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
#include "main.h"
#include "menuclass.h"
#include "indoors.h"
#include "maps.h"

//global vars
bool gameIsRunning = true;
SDLGraphics *game_graphics = NULL;
Input* game_input = NULL;
Timer* game_timer = NULL;

menuClass *gameMenu = NULL;
IndoorHandler *gameIndoors = NULL;

bool inMenu = false;


std::vector <Coords> rockLocations;


bool runOnce = false;

Player p1;

int main()
{
	
	srand ( time(NULL) );
	
	game_graphics = new SDLGraphics(SCREEN_WIDTH, SCREEN_HEIGHT, "Min Wage", 0,90,0);
	game_timer = new Timer();
	game_input = new Input();

	gameMenu = new menuClass();
	gameIndoors = new IndoorHandler();
	
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

	exitGame();

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

		drawOverlay();
		//printf("x: %d y: %d\n", rockLocations.at(0).getX(), rockLocations.at(0).getY());
		game_graphics->drawSprite(p1.playerBMP, (int)frame * 32, dir, p1.getX(), p1.getY(), 32, 32);

		showXY();
	    
		game_graphics->endScene();

		if (inMenu)
		{
			gameMenu->displayMenu();
		}

		// Give the computer a break (optional)
		//SDL_Delay(10);
		
	}
}

void exitGame()
{
	screenBlackAnim();

	delete game_timer;
	delete game_input;
	delete game_graphics;	
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
			game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 8, screenTiles.at(count).getY() * 8, 8, 8);
			count++;
			game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 8, screenTiles.at(count).getY() * 8, 8, 8);
			count++;
			game_graphics->drawSprite(blackTile, 0, 0, screenTiles.at(count).getX() * 8, screenTiles.at(count).getY() * 8, 8, 8);			
			game_graphics->endScene();
			//SDL_Delay(2);
	}
	game_graphics->endScene();
	//SDL_Delay(500);
	
}

void drawOverlay()
{
	
	int mapPlace = 0;

	Coords tempCoords, holdDimensions;

	
	for (int y = 0; y < SCREEN_HEIGHT/SPRITE_HEIGHT; y++) 
	{
		for (int x = 0; x < SCREEN_WIDTH/SPRITE_WIDTH; x++) 
		{
			if (gameMaps[p1.getMapX()][p1.getMapY()][mapPlace] != 0)
			{
				//game_graphics->drawSprite(getObjSurface(gameMaps[p1.getMapX()][p1.getMapY()][mapPlace]), 0, 0, x * 32, y * 32, 32, 32);
				holdDimensions = getObjDimensions(gameMaps[p1.getMapX()][p1.getMapY()][mapPlace]);
				game_graphics->drawSprite(getObjSurface(gameMaps[p1.getMapX()][p1.getMapY()][mapPlace]), 0, 0, x * 32, y * 32, holdDimensions.getX(), holdDimensions.getY());
				if (runOnce == false)
				{
					
					printf("2. rock at x: %d y: %d\n", x, y);
					tempCoords.setX(x);
					tempCoords.setY(y);
					tempCoords.setObjType(gameMaps[p1.getMapX()][p1.getMapY()][mapPlace]);
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
   bool* keysHit = game_input->getSlowInput();
   

   if (keysHeld[SDLK_ESCAPE])
   {
      gameIsRunning = false;
   }

   if (keysHeld[SDLK_LEFT])
   {
	  if (!collideRockTest(-1, 0))
      {
		if (  (p1.getX() - 1) < 0)
		{
			if ((p1.getMapX() > 0))
			{
				mapChange(-1, 0);
			}
		}
		else
		{
			p1.changeX(-1);
			p1.startWalk();
		} 
	  }
      p1.setDir(PLAYER_LEFT);
    }
	else if (keysHeld[SDLK_RIGHT])
	{
      if (!collideRockTest(1, 0))
      {
		if ((p1.getX() + 1) > (SCREEN_WIDTH - SPRITE_WIDTH)) //1 is the max map num
		{
			if ((p1.getMapX() < 1))
			{
				mapChange(1, 0);
			}
		}
		else
		{

			p1.changeX(1);
			p1.startWalk(); 
		}
      }
      p1.setDir(PLAYER_RIGHT);
	}
	
	if (keysHeld[SDLK_UP])
	{

      if (!collideRockTest(0, -1))
      {
		  
		if ((p1.getY() - 1) < 0)
		{
			if (p1.getMapY() > 0)
			{
				mapChange(0, -1);
			}
			
		}
		else
		{

			p1.changeY(-1);
			p1.startWalk(); 
		}
	  }
      p1.setDir(PLAYER_UP);
	}
	else if (keysHeld[SDLK_DOWN])
	{
	  if (!collideRockTest(0, 1))
      {
		if ((p1.getY() + 1) > (SCREEN_HEIGHT - SPRITE_HEIGHT)) 
		{
			if ((p1.getMapY() < 1))
			{
				mapChange(0,1);
			}

		}
		else
		{

			p1.changeY(1);
			p1.startWalk();
		}
	  }
      p1.setDir(PLAYER_DOWN); 
	}

	if (!keysHeld[SDLK_DOWN] && !keysHeld[SDLK_UP] && !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT])
	{
		p1.stopWalk();
	}
	
	if (keysHit[SDLK_b])  //'b' tests fade to black
	{
		screenBlackAnim();
		keysHit[SDLK_b] = false;
	}
	if (keysHit[SDLK_v])	//'v' is menu test
	{
		inMenu = true;
		keysHit[SDLK_v] = false;
	}
	if (keysHit[SDLK_n])	//'n' is indoors test
	{
		gameIndoors->drawRoomView();
		keysHit[SDLK_n] = false;
	}
	


}

void showXY()
{
		char xcor[10];
		char ycor[10];
		//printf("t1\n");
		sprintf(xcor, "x: %d", p1.getX());
		sprintf(ycor, "y: %d", p1.getY());
		//printf("t2\n");
		game_graphics->drawText(xcor, 12, 500, 300, 200, 0, 0, 0, 0, 0);
		game_graphics->drawText(ycor, 12, 500, 320, 200, 0, 0, 0, 0, 0);
}

//goes through each rock on the screen, checking for player collisions
int collideRockTest(int chX, int chY)
{
		int retVal = 0;
		if (runOnce == true)
		{
			for (int rockCount = 0; rockCount < rockLocations.size(); rockCount++)
			{
				//if(SDL_CollidePixel(playerMask, p1.getX() + chX, p1.getY() + chY, getObjSurfaceMasks(rockLocations.at(rockCount).getObjType()), rockLocations.at(rockCount).getX() * 32, rockLocations.at(rockCount).getY() * 32))
				if(SDL_CollidePixel(playerMask, p1.getX() + chX, p1.getY() + chY, getObjSurface(rockLocations.at(rockCount).getObjType()), rockLocations.at(rockCount).getX() * 32, rockLocations.at(rockCount).getY() * 32))
				{
						retVal = 1;
				}
			}
		}
	
		return retVal;
}


//resets things for map change, one map at a time
//ie mapChange(0,1) -> adds 1 to y OR mapChange(-1,0) -> adds 1 to y
//the change can be done in leaps greater than one map screen
//...but probably not needed
void mapChange(int chx, int chy)
{
	if (chx == 0)
	{
		if (chy > 0)
			{
				p1.setY(0);
				
			}
		else if (chy < 0)
			{
				p1.setY(SCREEN_HEIGHT - SPRITE_HEIGHT);
			}
		p1.changeMapY(chy);
	}
	else if (chy == 0)
	{
		if (chx > 0)
			{
				p1.setX(0);
			}
		else if (chx < 0)
			{
				p1.setX(SCREEN_WIDTH - SPRITE_WIDTH);
			}
		p1.changeMapX(chx);		
	}
	runOnce = false;
	rockLocations.clear();
}


