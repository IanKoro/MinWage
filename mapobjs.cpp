#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <map>
#include <vector>

#include "SDLGraphics.h"
#include "gameobjs.h"
#include "main.h"
#include "mapobjs.h"




SDL_Surface* grassTiles;
SDL_Surface* fullGrass;

SDL_Surface*  blackTile;
SDL_Surface*  sepBar;
SDL_Surface*  playerMask;
SDL_Surface* indoorDesk;

SDL_Surface* indoorWayTop;
SDL_Surface* indoorWayBottom;
SDL_Surface* indoorWayLeft;
SDL_Surface* indoorWayRight;


SDL_Surface* dollarSprite;
SDL_Surface* deskMan;



void setupTiles()
{
	GameObject spriteHolder;

	grassTiles = SDL_LoadBMP("images/grassALL.bmp");

	fullGrass = IMG_Load("images/bg.png");

	blackTile = IMG_Load("images/black.bmp");

	playerMask = IMG_Load("images/pmask.png");

	sepBar = IMG_Load("images/sepBar.png");

	spriteHolder.set_sprite(IMG_Load("images/rock.png"));
	spriteHolder.setDimensions(32, 32);
	AllGameObjects[1] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/bigrock.png"));
	spriteHolder.setDimensions(32, 32);
	AllGameObjects[2] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/bar.png"));//3  door 91 3x2
	spriteHolder.setDimensions(96, 64);
	AllGameObjects[3] = spriteHolder;
	
	spriteHolder.set_sprite(IMG_Load("images/building.png"));//4 door 92 4x9
	spriteHolder.setDimensions(128,288);
	AllGameObjects[4] = spriteHolder;
		
	spriteHolder.set_sprite(IMG_Load("images/tree.png"));
	spriteHolder.setDimensions(32, 64);
	AllGameObjects[5] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/shrub.png"));
	spriteHolder.setDimensions(32, 32);
	AllGameObjects[6] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/tree2.png"));
	spriteHolder.setDimensions(50, 110);
	AllGameObjects[7] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/barDoor.png"));//bar doorway
	spriteHolder.setDimensions(96,32);
	AllGameObjects[91] = spriteHolder;

	spriteHolder.set_sprite(IMG_Load("images/bldgDoor.png"));//building doorway
	spriteHolder.setDimensions(128,32);
	AllGameObjects[92] = spriteHolder;




indoorDesk = IMG_Load("images/desk.png");

indoorWayTop = IMG_Load("images/inDoorTop.png");
indoorWayBottom = IMG_Load("images/inDoorBottom.png");
indoorWayLeft = IMG_Load("images/inDoorLeft.png");
indoorWayRight = IMG_Load("images/inDoorRight.png");


dollarSprite = IMG_Load("images/dollar.png");
deskMan = IMG_Load("images/deskman.png");



	SDL_SetColorKey(playerMask,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(playerMask->format, 255, 0, 255));



	SDL_SetColorKey(indoorDesk,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorDesk->format, 255, 0, 255));



	SDL_SetColorKey(indoorWayTop,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorWayTop->format, 255, 0, 255));

	SDL_SetColorKey(indoorWayBottom,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorWayBottom->format, 255, 0, 255));

	SDL_SetColorKey(indoorWayLeft,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorWayRight->format, 255, 0, 255));
                   
	SDL_SetColorKey(indoorWayRight,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorWayRight->format, 255, 0, 255));                   
             




	SDL_SetColorKey(dollarSprite,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(dollarSprite->format, 255, 0, 255));


                   
	SDL_SetColorKey(deskMan,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(deskMan->format, 255, 0, 255));
}
