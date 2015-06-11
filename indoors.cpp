#include "main.h"
#include "mapobjs.h"
#include "indoors.h"


IndoorHandler::IndoorHandler()
{
	isIndoors = false;
}

IndoorHandler::~IndoorHandler()
{}

void IndoorHandler::drawRoomView()
{
	//gameMenu->drawBorder(18,13,FLOORTILES_KITCHEN);
	gameMenu->drawBorder(18,13,FLOORTILES_PLAIN);
	game_graphics->drawSprite(tempOVERHEAD,0,0,275,175,64,64);
	game_graphics->endScene();
	SDL_Delay(1000);
	
}

void IndoorHandler::goInside(int roomNumber)
{
	printf("Entering room #%d\n", roomNumber);
	isIndoors = true;
}

void IndoorHandler::goOutside()
{
	isIndoors = false;
}
