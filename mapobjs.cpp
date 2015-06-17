#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>

#include "SDLGraphics.h"
#include "gameobjs.h"
#include "mapobjs.h"


SDL_Surface* grassTiles = SDL_LoadBMP("images/grassALL.bmp");

SDL_Surface*  blackTile = SDL_LoadBMP("images/black.bmp");


SDL_Surface*  rockTile = IMG_Load("images/rock.png");
SDL_Surface*  bigRockTile = IMG_Load("images/bigrock.png");


SDL_Surface*  playerMask = IMG_Load("images/pmask.png");

SDL_Surface* barBldg = IMG_Load("images/bar.png");

SDL_Surface* apartBldg = IMG_Load("images/building.png");
SDL_Surface* apartBldgMask = IMG_Load("images/building_mask.png");


SDL_Surface* indoorDesk = IMG_Load("images/desk.png");


void setupTiles()
{
	

	SDL_SetColorKey(playerMask,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(playerMask->format, 255, 0, 255));
	
	SDL_SetColorKey(rockTile,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(rockTile->format, 255, 0, 255));

	SDL_SetColorKey(bigRockTile,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(bigRockTile->format, 255, 0, 255));

	SDL_SetColorKey(barBldg,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(barBldg->format, 255, 0, 255));

	SDL_SetColorKey(apartBldg,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(apartBldg->format, 255, 0, 255));
 

	SDL_SetColorKey(apartBldgMask,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(apartBldgMask->format, 255, 0, 255));



	SDL_SetColorKey(indoorDesk,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorDesk->format, 255, 0, 255));


}
