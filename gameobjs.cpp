#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "SDLGraphics.h"
#include "gameobjs.h"


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
	
	x = y = 10;
	
	walking = false;
	
}

Player::~Player()
{
	SDL_FreeSurface(playerBMP);
}
