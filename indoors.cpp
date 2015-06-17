#include "main.h"
#include "mapobjs.h"
#include "gameobjs.h"
#include "indoors.h"
#include "indoorPlayer.h"
#include "indoorMaps.h"


IndoorHandler::IndoorHandler()
{
	isIndoors = false;
}

IndoorHandler::~IndoorHandler()
{}

void IndoorHandler::drawRoomView(int roomNumber)
{


	float walkFramePos = 2;
	playerAbove.setX(275);
	playerAbove.setY(175);
	float pX, pY, frameP;

	
	while (isIndoors)
	{

		game_input->readInput();
		indoorInput();
		//gameMenu->drawBorder(18,13,FLOORTILES_KITCHEN);
		gameMenu->drawBorder(18,13,FLOORTILES_WOOD);
		//gameMenu->drawBorder(18,13,FLOORTILES_PLAIN);
		
		if (playerAbove.isWalk())
		{
				if (playerAbove.frame_dir == 0) 
				{
					playerAbove.changeFrame(0.1); 
				}
				else if (playerAbove.frame_dir == 1) 
				{
					playerAbove.changeFrame(-0.01); 
				}
				
				if (playerAbove.getFrame() < -0.01) 
				{
					playerAbove.setFrame(0.05);
					walkFramePos = 0.6;
					playerAbove.frame_dir = 0;
				}
				else if (playerAbove.getFrame() > 4.0) 
				{
					playerAbove.setFrame(3.95);
					walkFramePos = 4;
					playerAbove.frame_dir = 1;
				}
		}
		else 
		{
			playerAbove.setFrame(2.0);
		}
		walkFramePos = playerAbove.getFrame();


		if (walkFramePos > 4)
		{
			walkFramePos = 4;
			playerAbove.frame_dir = 1;
		}
		else if (walkFramePos < 0)
		{
			walkFramePos = 0;
			playerAbove.frame_dir = 0;
		}


		pX = playerAbove.getX();
		pY = playerAbove.getY();
		frameP = playerAbove.getFrame();
		
		game_graphics->drawSprite(playerAbove.indoorSprite, 
								(int)walkFramePos * 64, playerAbove.getDir() * 64, 
								(int)pX, (int)pY,
								 64, 64);

		printf("about to start the sprites...\n");
		drawRoomSprites(roomNumber);
		//game_graphics->drawSprite(tempDESK,0,0,190,105,128,64);
		

		game_graphics->endScene();
	}
	//delete playerAbove;

	
}

void IndoorHandler::drawRoomSprites(int roomNum)
{
	int mapPlace = 0;
	Coords holdDimensions;
	//indoor map is 16 x 11 tiles, but starts at tile (2, 2). so range is y:2 -> 13 and x:2 ->18  
	printf("here goes...\n");
	printf("should be 0: %d...\n", indoorMaps[roomNum][mapPlace]);
	for (int y = 2; y < 13; y++) 
	{
		for (int x = 2; x < 18; x++) 
		{
			if (indoorMaps[roomNum][mapPlace] != 0)
			{
				printf("and...\n");
				holdDimensions = getIndoorObjDimensions(indoorMaps[roomNum][mapPlace]);
				printf("1...\n");
				game_graphics->drawSprite(getIndoorObjSurface(indoorMaps[roomNum][mapPlace]), 0, 0, x * 32, y * 32, holdDimensions.getX(), holdDimensions.getY());
				printf(".2..\n");
			}
			mapPlace++;
		}
	}
}


void IndoorHandler::goInside(int roomNumber)
{
	printf("Entering room #%d\n", roomNumber);
	isIndoors = true;
	drawRoomView(0);
}

void IndoorHandler::goOutside()
{
	isIndoors = false;
}


void IndoorHandler::indoorInput()
{
   bool* keysHeld = game_input->getInput();
   bool* keysHit = game_input->getSlowInput();
   

	if (keysHit[SDLK_ESCAPE])
	{
      isIndoors = false;
      keysHit[SDLK_ESCAPE] = false;

	}
	if (keysHeld[SDLK_RIGHT])
	{
      playerAbove.changeX(0.2);
      playerAbove.setDir(PLAYER_RIGHT);
      playerAbove.startWalk();      
      //keysHit[SDLK_RIGHT] = false;
	}
	if (keysHeld[SDLK_LEFT])
	{
      playerAbove.changeX(-0.2);
      playerAbove.setDir(PLAYER_LEFT);
      playerAbove.startWalk();
      //keysHit[SDLK_LEFT] = false;
	}
	if (keysHeld[SDLK_UP])
	{
      playerAbove.changeY(-0.2);
      playerAbove.setDir(PLAYER_UP);
      playerAbove.startWalk();      
      //keysHit[SDLK_RIGHT] = false;
	}
	if (keysHeld[SDLK_DOWN])
	{
      playerAbove.changeY(0.2);
      playerAbove.setDir(PLAYER_DOWN);
      playerAbove.startWalk();
      //keysHit[SDLK_LEFT] = false;
	}

	if (!keysHeld[SDLK_DOWN] && !keysHeld[SDLK_UP] && !keysHeld[SDLK_LEFT] && !keysHeld[SDLK_RIGHT])
	{
		playerAbove.stopWalk();
	}

}

SDL_Surface* getIndoorObjSurface(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else if (objType == 01)
		{
			return indoorDesk;
		}

		
}


Coords getIndoorObjDimensions(int objType)
{
		Coords retCoords;
		
		if (objType == 0)
		{
			retCoords.setX(0);
			retCoords.setY(0);
		}
		else if (objType == 01) //desk
		{
			retCoords.setX(128);
			retCoords.setY(64);
		}
		return retCoords;
}
