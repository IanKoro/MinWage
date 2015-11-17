#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_events.h>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>

#include "main.h"

/*
#include "SDLGraphics.h"
#include "SDL_collide.h"
#include "Input.h"
#include "Timer.h"
#include "gameobjs.h"
#include "mapobjs.h"

#include "menuclass.h"
#include "indoors.h"
#include "maps.h"
#include "inventory.h"

#include "makeMap.h"
*/

//#include "indoorMaps.h"

//const int FRAMES_PER_SECOND = 20;


//global vars
bool gameIsRunning = true;
SDLGraphics *game_graphics = NULL;
Input* game_input = NULL;
//Timer* game_timer = NULL;
Timer game_timer;

SDL_Event game_event;

menuClass *gameMenu = NULL;
IndoorHandler *gameIndoors = NULL;

bool inMenu = false;

std::map <int, GameObject> AllGameObjects;
std::vector <Coords> mapObjLocations;


bool runOnce = false;

Player p1;
AllMaps fullMaps;
IndoorPlayer playerAbove;
PlayerInventory playerStuff;

int main()
{
	
	srand ( time(NULL) );
	
	game_graphics = new SDLGraphics(SCREEN_WIDTH + 150, SCREEN_HEIGHT, "Min Wage", 0,0,0);
	//game_timer = new Timer();
	
	game_input = new Input();

	gameMenu = new menuClass();
	gameIndoors = new IndoorHandler();
	
	playerStuff.gameStart();
	
	//There's got to be a better way to do this (generating random tiles for the grass)...
	//This is probably a better idea: generate the entire backdrop as an SDL_Surface that can be drawn 
	//														each time it is needed?

	int randTiles[(SCREEN_HEIGHT / 32) * (SCREEN_WIDTH / 32)];
	int i = 0;
	for (i = 0; i < (SCREEN_HEIGHT / 32) * (SCREEN_WIDTH / 32); i++)
	{
		randTiles[i] = rand() % 4;
	}

	//makeMap();
	//loadMapFile("datfile.dat");
	setupTiles();

	showTitle();

	gameloop(randTiles);

	exitGame();

	return 0;
}

void gameloop(int randTiles[])
{
	float frame = 0.0;
	int dir = 0;
	
	//game_input->clearKeys();
	
	while (gameIsRunning)
	{
		
		game_timer.start();

		/**
		game_input->readInput();

		if (game_input->windowClosed())
		{
			gameIsRunning = false;
		}
		**/


		while( SDL_PollEvent( &game_event ) )
        {
            //Handle events for the dot
            handleKeyboardInput();

            //If the user has Xed out the window
            if( game_event.type == SDL_QUIT )
            {
                //Quit the program
                gameIsRunning = false;
            }
        }
        
        p1.moveChar();


		

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

		game_graphics->drawSprite(p1.playerBMP, (int)frame * 32, dir, p1.getX(), p1.getY(), 32, 32);

		//showXY();
		
		game_graphics->drawSprite(sepBar, 0, 0, 640, 0, 7, 480);
	    
	    drawStats();
	    
		game_graphics->endScene();

		if (inMenu)
		{
			gameMenu->displayMenu();
			
		}

		
		//Cap the frame rate
        if( game_timer.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - game_timer.get_ticks() );
        }
		
		
		
	}
}

void exitMessage(std::string exitMsg)
{
	std::cout << "Error: " << exitMsg << "\n";
	exitGame();
}


void exitGame()
{
	screenBlackAnim();

	//delete game_timer;
	delete game_input;
	delete game_graphics;	
}
	
void drawGrass(int randTiles[])
{

	game_graphics->drawSprite(fullGrass, 0, 0, 0,0, 640, 480);

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
	int spriteCount = 0;
	int typeHold = 0;
	
	//If we have just loaded this map, pull the sprites into memory
	//Once the sprites are no longer stored as a giant map, this will be simpler
	if (runOnce == false)
	{
		loadMapFile("datfile.dat", p1.getMapX(), p1.getMapY());
		runOnce = true;
	}
	
	for (spriteCount = 0; spriteCount < mapObjLocations.size(); spriteCount++)
	{
		typeHold = mapObjLocations.at(spriteCount).getObjType();
		holdDimensions = getObjDimensions(typeHold);
		
		if (typeHold < 90)
		{
			game_graphics->drawSprite(getObjSurface(typeHold), 0, 0, mapObjLocations.at(spriteCount).getX() * 32, mapObjLocations.at(spriteCount).getY() * 32, holdDimensions.getX(), holdDimensions.getY());
		}
	}
}

void handleKeyboardInput()
{
	
	    //If a key was pressed
    if( game_event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( game_event.key.keysym.sym )
        {
            case SDLK_UP: p1.throttleY(-MOVE_SIZE);  p1.setDir(PLAYER_UP); break;
            case SDLK_DOWN: p1.throttleY(MOVE_SIZE);  p1.setDir(PLAYER_DOWN); break;
            case SDLK_LEFT: p1.throttleX(-MOVE_SIZE);  p1.setDir(PLAYER_LEFT); break;
            case SDLK_RIGHT: p1.throttleX(MOVE_SIZE);  p1.setDir(PLAYER_RIGHT); break;
            case SDLK_ESCAPE: inMenu = true; break;
        }
    }
    //If a key was released
    else if( game_event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( game_event.key.keysym.sym )
        {
            case SDLK_UP: p1.throttleY(MOVE_SIZE); break;
            case SDLK_DOWN: p1.throttleY(-MOVE_SIZE); break;
            case SDLK_LEFT: p1.throttleX(MOVE_SIZE); break;
            case SDLK_RIGHT: p1.throttleX(-MOVE_SIZE); break;
        }
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
int collideMapObjTest(int chX, int chY)
{
		int retVal = 0;
		if (runOnce == true)
		{
			for (int mapObjCount = 0; mapObjCount < mapObjLocations.size(); mapObjCount++)
			{
				//if(SDL_CollidePixel(playerMask, p1.getX() + chX, p1.getY() + chY, getObjSurfaceMasks(mapObjLocations.at(mapObjCount).getObjType()), mapObjLocations.at(mapObjCount).getX() * 32, mapObjLocations.at(mapObjCount).getY() * 32))
				if(SDL_CollidePixel(playerMask, p1.getX() + chX, p1.getY() + chY, getObjSurface(mapObjLocations.at(mapObjCount).getObjType()), mapObjLocations.at(mapObjCount).getX() * 32, mapObjLocations.at(mapObjCount).getY() * 32))
				{
						
						retVal = mapObjLocations.at(mapObjCount).getObjType();
						
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
	mapObjLocations.clear();
}

void showTitle()
{
	SDL_Surface *titleImage = IMG_Load("images/title2.png");
	game_graphics->drawSprite(titleImage, 0, 0, 0,0, 790, 480);
	game_graphics->endScene();
	SDL_Delay(1000);
	game_input->clearKeys();
	
}

int collidedWith(int collideItem)
{
		printf("You collided with: %d\n", collideItem);
		if (collideItem == 91)
			{	
				drawSpiral(75, 5);
				gameIndoors->goInside(0);
			}
		else if (collideItem == 92)
			{
				drawSpiral(75, 5);
				gameIndoors->goInside(1);				
			}
		return 0;
}

void drawStats()
{
	char stringtoPrint[10];
	sprintf(stringtoPrint, "Money: $%d", playerStuff.getMoney());
	game_graphics->drawText(stringtoPrint, 25, 655, 10, 200, 0, 0, 0, 0, 0);

	sprintf(stringtoPrint, "Map X: %d", p1.getMapX());
	game_graphics->drawText(stringtoPrint, 25, 655, 40, 200, 0, 0, 0, 0, 0);

	sprintf(stringtoPrint, "Map Y: %d", p1.getMapY());
	game_graphics->drawText(stringtoPrint, 25, 655, 70, 200, 0, 0, 0, 0, 0);
		
}


