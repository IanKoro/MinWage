#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "SDLGraphics.h"
#include "gameobjs.h"
#include "mapobjs.h"


Player::Player()
{
	//Load image assets into playerBMP
	
	SDL_Surface* bitmap = SDL_LoadBMP("images/sprite3.bmp");

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

SDL_Surface* getObjSurface(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else if (objType == 01)
		{
			return rockTile;
		}
		else if (objType == 02)
		{
			return bigRockTile;
		}
		else if (objType == 03)
		{
			return barBldg;
		}
		else if (objType == 04)
		{
			return apartBldg;
		}
		
}

SDL_Surface* getObjSurfaceMasks(int objType)
{
		if (objType == 0)
		{
			return NULL;
		}
		else if (objType == 01)
		{
			return rockTile;
		}
		else if (objType == 02)
		{
			return bigRockTile;
		}
		else if (objType == 03)
		{
			return barBldg;
		}
		else if (objType == 04)
		{
			return apartBldgMask;
		}
		
}

Coords getObjDimensions(int objType)
{
		Coords retCoords;
		
		if (objType == 0)
		{
			retCoords.setX(0);
			retCoords.setY(0);
		}
		else if (objType == 01 || objType == 02)
		{
			retCoords.setX(32);
			retCoords.setY(32);
		}
		else if (objType == 03) //bar obj, 3x2 tiles
		{
			retCoords.setX(32 * 3);
			retCoords.setY(32 * 2);
		}
		else if (objType == 04) //apartment obj 128x288 (4x9 tiles)
		{
			retCoords.setX(32 * 4);
			retCoords.setY(32 * 9);
		}	
		return retCoords;
}
