#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <map>
#include <iostream>
#include "main.h"
#include "SDLGraphics.h"
#include "gameobjs.h"
#include "mapobjs.h"
#include "maps.h"


Player::Player()
{
	//Load image assets into playerBMP
	//SDL_Surface* bitmap = SDL_LoadBMP("images/sprite3.bmp");
	SDL_Surface* bitmap = IMG_Load("images/sprite44.png");

	SDL_SetColorKey(bitmap,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(bitmap->format, 255, 0, 255));

	playerBMP = bitmap;
	
	//set other vars
	
	xvel = yvel = 0;
	
	mapX = mapY = 0;
	
	x = y = 10;
	
	walking = false;
	
}

Player::~Player()
{
	SDL_FreeSurface(playerBMP);
}

void Player::moveChar()
{
	

		//fill this with new movement code
		int collideHolder = 0;
		if (xvel > 0)
		{
			collideHolder = collideMapObjTest(MOVE_SIZE, 0);
			/*if (!collideHolder)
			{
				changeX(xvel);
			}*/
			
			if ((getX() + 1) > (SCREEN_WIDTH - SPRITE_WIDTH))
			{
				if ((getMapX() < (MAPSIZE_X - 1)))
				{
					mapChange(1, 0);
				}
			}
			else if (!collideHolder)
			{changeX(xvel);startWalk();}
			else 
			{collidedWith(collideHolder);}
		}
		else if (xvel < 0)
		{
			collideHolder = collideMapObjTest(-MOVE_SIZE, 0);
			/*if (!collideHolder)
			{
				changeX(xvel);
			}*/
			
			if ((getX() - 1) < 0)
			{
				if ((getMapX() > 0))
				{
					mapChange(-1, 0);
				}
			}
			else if (!collideHolder)
			{changeX(xvel);startWalk();}
			else 
			{collidedWith(collideHolder);}


		}

		if (yvel > 0)
		{
			collideHolder = collideMapObjTest(0, MOVE_SIZE);
			/*if (!collideHolder)
			{
				changeY(yvel);
			}*/
			if ((getY() + 1) > (SCREEN_HEIGHT - SPRITE_HEIGHT)) 
			{
				if ((getMapY() < (MAPSIZE_Y - 1)))
				{
					mapChange(0,1);
				}

			}
			else if (!collideHolder)
			{
				changeY(yvel);
				startWalk();
			}
			else 
			{collidedWith(collideHolder);}
		}
		else if (yvel < 0)
		{ 
			collideHolder = collideMapObjTest(0, -MOVE_SIZE);
			/*if (!collideHolder)
			{
				changeY(yvel);
			}*/
			
			
			if ((getY() - 1) < 0)
			{
				if (getMapY() > 0)
				{
					mapChange(0, -1);
				}
			
			}
			else if (!collideHolder)
			{changeY(yvel);startWalk();}
			else 
			{collidedWith(collideHolder);}
		}


	if (yvel == 0 && xvel == 0)
	{
		stopWalk();
	}

}

void GameObject::set_sprite(SDL_Surface *sprData)
{
	std::cout << "loading srpdat..";
	SDL_SetColorKey(sprData,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(sprData->format, 255, 0, 255));
	std::cout << "11\n";
	spriteData = sprData;
}

SDL_Surface* getObjSurface(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else
		{
			return AllGameObjects[objType].get_sprite();	
		}

}

SDL_Surface* getObjSurfaceMasks(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else
		{			
			return AllGameObjects[01].get_sprite();
		}

}

Coords getObjDimensions(int objType)
{
		Coords retCoords;
		retCoords = AllGameObjects[objType].getDimensions();



		return retCoords;
}
