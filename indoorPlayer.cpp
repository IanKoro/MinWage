#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "gameobjs.h"
#include "main.h"
#include "indoorPlayer.h"

IndoorPlayer::IndoorPlayer()
{
	indoorSprite = IMG_Load("images/OverheadPlayer.png");
	
	p_frame = 2.0;
	frame_dir = 0;
	
	xvel = yvel = 0;

	
	direction = PLAYER_UP;
		SDL_SetColorKey(indoorSprite,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorSprite->format, 255, 0, 255));

	playerAbove.setXvel(0);playerAbove.setYvel(0);
}

IndoorPlayer::~IndoorPlayer()
{
	
}

void IndoorPlayer::changeX(float changex)
{
	
	indoorx += changex;
	if (indoorx < 64) {indoorx = 64;}
	if (indoorx > (SCREEN_WIDTH - 128)) {indoorx = (SCREEN_WIDTH - 128);}	
}

void IndoorPlayer::changeY(float changey)
{
	indoory += changey;
	if (indoory < 64) {indoory = 64;}
	if (indoory > (SCREEN_HEIGHT - 128)) {indoory = (SCREEN_HEIGHT - 128);}
}

void IndoorPlayer::moveChar()
{
	if (xvel != 0)
	{
		if (!gameIndoors->collideObjTest(indoorx, indoory)){}
		{
			changeX(xvel);
		}
		playerAbove.startWalk();
	}

	if (yvel != 0)
	{
		if (!gameIndoors->collideObjTest(indoorx, indoory)){}
		{
			changeY(yvel);
		}		
		playerAbove.startWalk();
	}
	
	if (yvel == 0 && xvel == 0)
	{
		playerAbove.stopWalk();
	}
	//refer to gameobjs.
}

void IndoorPlayer::handleIndoorInput()
{
	
	    //If a key was pressed
    if( game_event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( game_event.key.keysym.sym )
        {
            case SDLK_UP: throttleY(-MOVE_SIZE);  setDir(PLAYER_UP); break;
            case SDLK_DOWN: throttleY(MOVE_SIZE);  setDir(PLAYER_DOWN); break;
            case SDLK_LEFT: throttleX(-MOVE_SIZE);  setDir(PLAYER_LEFT); break;
            case SDLK_RIGHT: throttleX(MOVE_SIZE);  setDir(PLAYER_RIGHT); break;
            case SDLK_ESCAPE: inMenu = true; break;
        }
    }
       //If a key was released
    else if( game_event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( game_event.key.keysym.sym )
        {
            //case SDLK_UP: throttleY(MOVE_SIZE); break;
            case SDLK_UP: playerAbove.setYvel(0); break;
            //case SDLK_DOWN: throttleY(-MOVE_SIZE); break;
            case SDLK_DOWN: playerAbove.setYvel(0); break;
			//case SDLK_LEFT: throttleX(MOVE_SIZE); break;
            case SDLK_LEFT: playerAbove.setXvel(0); break;
            //case SDLK_RIGHT: throttleX(-MOVE_SIZE); break;
            case SDLK_RIGHT: playerAbove.setXvel(0); break;
            case SDLK_c: std::cout << "x velocity: " << xvel << "  y velocity: " << yvel << "\n"; break;
            case SDLK_v: playerAbove.setXvel(0);playerAbove.setYvel(0); break;
        }
    }
	
	


}
