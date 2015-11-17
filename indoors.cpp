#include "main.h"
#include "mapobjs.h"
#include "gameobjs.h"
#include "indoors.h"
#include "indoorPlayer.h"
#include "indoorMaps.h"
#include "SDL_collide.h"


IndoorHandler::IndoorHandler()
{
	isIndoors = false;
}

IndoorHandler::~IndoorHandler()
{}


void IndoorHandler::drawRoomView(int roomNumber)
{


	float walkFramePos = 2;

	float pX, pY, frameP;
	

	while (isIndoors && gameIsRunning)
	{


		//game_input->readInput();
		//indoorInput();
		gameMenu->drawBorder(18,13,getIndoorFloor(roomNumber));		
		
		std::cout << "Again111: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 

		//while (playerAbove.getYvel() == 3){}
		
		
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
		
		drawRoomSprites(roomNumber);
	
		//game_graphics->drawSprite(tempDESK,0,0,190,105,128,64);
		

		game_graphics->endScene();
		
		if (inMenu)
		{
			gameMenu->displayMenu();
		}
		inMenu = false;
		
		//Cap the frame rate
        if( game_timer.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - game_timer.get_ticks() );
        }

	std::cout << "Again2: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 
        
		while( SDL_PollEvent( &game_event ) )
		{
			playerAbove.handleIndoorInput();
			if( game_event.type == SDL_QUIT )
			{
				//Quit the program
				gameIsRunning = false;
			}
		}
	std::cout << "Again3: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 
		
		//std::cout << "Again4: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 
		playerAbove.moveChar();
	std::cout << "Again4: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 
	}
	indoorObjLocations.clear();
	//delete playerAbove;

	if (!gameIsRunning)
	{exitGame();}
	
}


//This section will need rewriting.
void IndoorHandler::drawRoomSprites(int roomNum)
{
	int mapPlace = 0;
	Coords holdDimensions;
	Coords tempCoords;
	//indoor map is 16 x 11 tiles, but starts at tile (2, 2). so range is y:2 -> 13 and x:2 ->18  



	for (int y = 2; y < 13; y++) 
	{
		for (int x = 2; x < 18; x++) 
		{
			if (indoorMaps[roomNum][mapPlace] != 0)
			{
				if (firstLoad)
				{
					tempCoords.setX(x);
					tempCoords.setY(y);
					tempCoords.setObjType(indoorMaps[roomNum][mapPlace]);
					indoorObjLocations.push_back(tempCoords);
				}
				holdDimensions = getIndoorObjDimensions(indoorMaps[roomNum][mapPlace]);
				game_graphics->drawSprite(gameIndoors->getIndoorObjSurface(indoorMaps[roomNum][mapPlace]), 0, 0, x * 32, y * 32, holdDimensions.getX(), holdDimensions.getY());
			}
			mapPlace++;
		}
	}

	firstLoad = false;

}


void IndoorHandler::goInside(int roomNumber)
{
	printf("Entering room #%d\n", roomNumber);
	std::cout << "x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 

	firstLoad = true;

	//playerAbove.setX(305);
	//playerAbove.setY(335);
	
	playerAbove.setX(305);
	playerAbove.setY(265);
	playerAbove.setDir(PLAYER_UP);


	SDL_Delay(100);
	isIndoors = true;

	playerAbove.setXvel(0);
	playerAbove.setYvel(0);
	playerAbove.stopWalk();
	std::cout << "Again: x velocity: " << playerAbove.getXvel() << "  y velocity: " << playerAbove.getYvel() << "\n"; 		
	drawRoomView(roomNumber);

}

void IndoorHandler::goOutside()
{
	//XiXX - fix the problem where the player auto re-enters.
	//std::cout << "Whoopsiedoodle\n";
	p1.setXvel(0);
	p1.setYvel(0);
	p1.changeY(35);	
	firstLoad = false;
	isIndoors = false;
	

}

/**
void IndoorHandler::indoorInput()
{
   bool* keysHeld = game_input->getInput();
   bool* keysHit = game_input->getSlowInput();
   int collideHolder = 0;

	if (keysHit[SDLK_ESCAPE])
	{
		inMenu = true;
		keysHit[SDLK_ESCAPE] = false;
		keysHeld[SDLK_ESCAPE] = false;

	}
	if (keysHeld[SDLK_RIGHT])
	{
	  collideHolder = collideObjTest(1,0);
      if (!collideHolder)
      {
		playerAbove.changeX(0.2);
		playerAbove.setDir(PLAYER_RIGHT);
		playerAbove.startWalk();      
		//keysHit[SDLK_RIGHT] = false;
	  }
	  else
	  {
		  collideWith(collideHolder);
	  }
	}
	if (keysHeld[SDLK_LEFT])
	{
	  collideHolder = collideObjTest(-1,0);
      if (!collideHolder)
      {
		playerAbove.changeX(-0.2);
		playerAbove.setDir(PLAYER_LEFT);
		playerAbove.startWalk();
		//keysHit[SDLK_LEFT] = false;
      }
	  else
	  {
		  collideWith(collideHolder);
	  }
	}
	if (keysHeld[SDLK_UP])
	{
	  collideHolder = collideObjTest(0,-1);
      if (!collideHolder)
      {
		playerAbove.changeY(-0.2);
		playerAbove.setDir(PLAYER_UP);
		playerAbove.startWalk();      
		//keysHit[SDLK_RIGHT] = false;
	  }
	  else
	  {
		  collideWith(collideHolder);
	  }
	}
	if (keysHeld[SDLK_DOWN])
	{
	  collideHolder = collideObjTest(0,1);
	  if (!collideHolder)
	  {
		playerAbove.changeY(0.2);
		playerAbove.setDir(PLAYER_DOWN);
		playerAbove.startWalk();
		//keysHit[SDLK_LEFT] = false;
      }
      else
	  {
		  collideWith(collideHolder);
	  }
	}

	
	playerAbove.stopWalk();
}
**/

SDL_Surface* IndoorHandler::getIndoorObjSurface(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else if (objType == 01)
		{
			return indoorWayTop;
		}
		else if (objType == 02)
		{
			return indoorWayBottom;
		}
		else if (objType == 03)
		{
			return indoorWayLeft;
		}
		else if (objType == 04)
		{
			return indoorWayRight;
		}
		else if (objType == 05)
		{
			return indoorDesk;
		}


		else if (objType == 11)
		{
			return dollarSprite;
		}
		
		else if (objType == 14)
		{
			return deskMan;
		}
}

int IndoorHandler::collideObjTest(int chX, int chY)
{
		int retVal = 0;

		SDL_Surface *tempPMask;
		SDL_Rect srcRect;
		
		srcRect.w = 64;
		srcRect.h = 64;
		
		srcRect.x = 0;
		srcRect.y = 0;
		//srcRect.x = playerAbove.getFrame() * 64;
		//srcRect.y = playerAbove.getDir() * 64;

		tempPMask = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64,
											game_graphics->returnScreen()->format->BitsPerPixel,
											game_graphics->returnScreen()->format->Rmask,
											game_graphics->returnScreen()->format->Gmask,
											game_graphics->returnScreen()->format->Bmask,
											game_graphics->returnScreen()->format->Amask
										);

		SDL_BlitSurface(playerAbove.indoorSprite, &srcRect, tempPMask, NULL);


/****		
		//printf("temp Mask W: %d  H: %d\n", tempPMask->w, tempPMask->h);
		game_graphics->beginScene();
				printf("go..3\n");
		game_graphics->drawSprite(tempPMask, 0,0,0,0,128,128);
				printf("go..4\n");
		game_graphics->endScene();
		SDL_Delay(2000);
****/	

		if (firstLoad == false)
		{
			for (int mapObjCount = 0; mapObjCount < indoorObjLocations.size(); mapObjCount++)
			{
				if(SDL_CollidePixel(tempPMask, playerAbove.getX() + chX, playerAbove.getY() + chY, getIndoorObjSurface(indoorObjLocations.at(mapObjCount).getObjType()), indoorObjLocations.at(mapObjCount).getX() * 32, indoorObjLocations.at(mapObjCount).getY() * 32))
				{
						
						retVal = indoorObjLocations.at(mapObjCount).getObjType();
						
				}
				
			}
		}
	
		return retVal;
}

int IndoorHandler::collideWith(int collideItem)
{
		printf("You collided with: %d\n", collideItem);
		if (collideItem == 2)
			{	
				//isIndoors = false;
				goOutside();
			}
		return 0;
}

Coords getIndoorObjDimensions(int objType)
{
		Coords retCoords;
		
		if (objType == 0)
		{
			retCoords.setX(0);
			retCoords.setY(0);
		}
		else if (objType == 01 || objType == 02)
		{
			retCoords.setX(96);
			retCoords.setY(32);
		}
		else if (objType == 03 || objType == 04)
		{
			retCoords.setX(32);
			retCoords.setY(96);

		}
		else if (objType == 05) //desk
		{
			retCoords.setX(128);
			retCoords.setY(64);
		}
		else if (objType == 11) //dollar
		{
			retCoords.setX(32);
			retCoords.setY(32);
		}
		else if (objType == 14) //deskman
		{
			retCoords.setX(64);
			retCoords.setY(64);
		}


		return retCoords;
}

int getIndoorFloor(int roomNum)
{
		if (roomNum == 0)
		{		
			return FLOORTILES_WOOD;
		}
		else if (roomNum == 1)
		{
			return FLOORTILES_KITCHEN;
		}
		else if (roomNum == 2)
		{
			return FLOORTILES_PLAIN;
		}
}
