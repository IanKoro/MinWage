#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "gameobjs.h"
#include "indoorPlayer.h"

IndoorPlayer::IndoorPlayer()
{
	indoorSprite = IMG_Load("images/OverheadPlayer.png");
	
	p_frame = 2.0;
	frame_dir = 0;
	
	direction = PLAYER_UP;
		SDL_SetColorKey(indoorSprite,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(indoorSprite->format, 255, 0, 255));
}

IndoorPlayer::~IndoorPlayer()
{
	
}

void IndoorPlayer::changeX(float changex)
{
	
	x += changex;
	if (x < 64) {x = 64;}
	if (x > (SCREEN_WIDTH - 128)) {x = (SCREEN_WIDTH - 128);}	
}

void IndoorPlayer::changeY(float changey)
{
	y += changey;
	if (y < 64) {y = 64;}
	if (y > (SCREEN_HEIGHT - 128)) {y = (SCREEN_HEIGHT - 128);}
}
