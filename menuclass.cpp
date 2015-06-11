#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>


#include "menuclass.h"
#include "mapobjs.h"
#include "gameobjs.h"
#include "SDLGraphics.h"
#include "main.h"

std::vector <SDL_Surface *> menuBorder(12);
SDL_Surface* menuDot = IMG_Load("images/bluedot.png");

menuItem::menuItem()
{
		caption = "";
		x_coord = 0;
		y_coord = 0;
		
		tR = 0;
		tG = 0;
		tB = 0;

		bR = 0;
		bG = 0;
		bB = 0;
}

menuItem::~menuItem()
{}

menuClass::menuClass()
{

		menuItem tempItem;
		
		menuBorder.at(MENU_TOP_LEFT) = IMG_Load("images/menu/TL.png");
		menuBorder.at(MENU_TOP_RIGHT) = IMG_Load("images/menu/TR.png");
		
		menuBorder.at(MENU_BOTTOM_LEFT) = IMG_Load("images/menu/BL.png");
		menuBorder.at(MENU_BOTTOM_RIGHT) = IMG_Load("images/menu/BR.png");

		menuBorder.at(MENU_TOP) = IMG_Load("images/menu/TH.png");
		menuBorder.at(MENU_BOTTOM) = IMG_Load("images/menu/BH.png");
		
		menuBorder.at(MENU_LEFT) = IMG_Load("images/menu/LV.png");
		menuBorder.at(MENU_RIGHT) = IMG_Load("images/menu/RV.png");
		
		menuBorder.at(8) = blackTile;
		menuBorder.at(9) = IMG_Load("images/floorTiles.png");
		menuBorder.at(10) = IMG_Load("images/floorTiles2.png");
		menuBorder.at(11) = IMG_Load("images/floorTiles3.png");
				
		tempItem.caption = "Inventory";
		tempItem.x_coord = 75;
		tempItem.y_coord = 84;
		
		tempItem.tR = 250;


		menuItemList.push_back(tempItem);

		tempItem.caption = "Stats";
		tempItem.x_coord = 75;
		tempItem.y_coord = 114;
		
		tempItem.tR = 250;


		menuItemList.push_back(tempItem);

		tempItem.caption = "Cell Phone";
		tempItem.x_coord = 75;
		tempItem.y_coord = 144;
		
		tempItem.tR = 250;


		menuItemList.push_back(tempItem);

		tempItem.caption = "Save Game";
		tempItem.x_coord = 75;
		tempItem.y_coord = 320;
		
		tempItem.tR = 250;

		menuItemList.push_back(tempItem);
		
		tempItem.caption = "Load Game";
		tempItem.x_coord = 75;
		tempItem.y_coord = 350;
		
		tempItem.tR = 250;

		menuItemList.push_back(tempItem);

		tempItem.caption = "Quit";
		tempItem.x_coord = 75;
		tempItem.y_coord = 380;
		
		tempItem.tR = 250;

		menuItemList.push_back(tempItem);
		
		tempItem.caption = "Back to game";
		tempItem.x_coord = 75;
		tempItem.y_coord = 410;
		
		tempItem.tR = 250;


		menuItemList.push_back(tempItem);
		
		SDL_SetColorKey(menuDot,
                   SDL_SRCCOLORKEY,
                   SDL_MapRGB(menuDot->format, 255, 0, 255));
				
}

menuClass::~menuClass()
{}

void menuClass::displayMenu()
{
	
	int menuPos = 0;

	drawBorder(18, 13);

	while (inMenu)
	{

		drawMenuItems(menuPos);
		game_graphics->endScene();

		int tempNum = menuState();
		
		if (tempNum != 3) //sloppy, I'm sure... but '3' represents a selection
		{
			menuPos += tempNum;
		
			if (menuPos < 0) {menuPos = (menuItemList.size() - 1);}
			else if (menuPos > (menuItemList.size() - 1)) {menuPos = 0;}	
		}
		else if (tempNum == 3)
		{
			doMenuItem(menuPos);
		}	
		
	}


}

void menuClass::drawMenuItems(int selectedItem)
{
	int itemCount = 0;
		
		
	game_graphics->drawText("Game Menu", 30, 245, 40 ,250,75,0,0,0,0);
	for (itemCount = 0; itemCount < menuItemList.size(); itemCount++)
	{
		if (selectedItem == itemCount)
		{
			game_graphics->drawSprite(menuDot, 0, 0,menuItemList.at(itemCount).x_coord - 32,menuItemList.at(itemCount).y_coord + 5,18,18);
		}
		else
		{
			game_graphics->drawSprite(blackTile, 0, 0,menuItemList.at(itemCount).x_coord - 32,menuItemList.at(itemCount).y_coord + 5,18,18);
		}
		game_graphics->drawText(menuItemList.at(itemCount).caption.c_str(), 24, menuItemList.at(itemCount).x_coord, menuItemList.at(itemCount).y_coord, menuItemList.at(itemCount).tR, menuItemList.at(itemCount).tG, menuItemList.at(itemCount).tB, menuItemList.at(itemCount).bR, menuItemList.at(itemCount).bG, menuItemList.at(itemCount).bB);
	}
}

void menuClass::doMenuItem(int menuSel)
{
	
	printf("MenuSel: %d\n", menuSel);
	printf("listSize: %d\n", menuItemList.size());
	if (menuSel == (menuItemList.size() - 1)) //last selection is "return to game".
		{
			printf("nomenu\n");
			inMenu = false;
		}
	else if (menuSel == (menuItemList.size() - 2)) //2nd last is 'exit'
		{
			printf("Quit\n");
			gameIsRunning = false;
			inMenu = false;
		}
	else if (menuSel == 0) //inventory
		{printf("Inventory\n");}
	else if (menuSel == 1) //stats
		{printf("Stats\n");}
	else if (menuSel == 2) //cell phone
		{printf("Cell phone\n");}
	else if (menuSel == 3) //save 
		{printf("Save Game\n");}
	else if (menuSel == 4) //load
		{printf("Load Game\n");}


}

int menuClass::menuState()
{
	game_input->readInput();
	bool* keysHeld = game_input->getInput();

	int change = 0;
	if (keysHeld[SDLK_UP])
	{
		change = -1;
		keysHeld[SDLK_UP] = false;
	}

	if (keysHeld[SDLK_DOWN])
	{
		change = 1;
		keysHeld[SDLK_DOWN] = false;
	}

	if (keysHeld[SDLK_ESCAPE])
	{
		inMenu = false;
		keysHeld[SDLK_ESCAPE] = false;
	}

	if (keysHeld[SDLK_RETURN])
	{
		change = 3;
		keysHeld[SDLK_RETURN] = false;
	}
	
	return change;
}

void menuClass::drawBorderBackup()
{
	int menuW = 18;
	int menuH = 13;
	
	int xTile, yTile;
	xTile = yTile = 1;

	int curTile = 8;
	
	
		for (yTile = 1; yTile < ((SCREEN_HEIGHT / 32) - 1); yTile++)
		{
				for (xTile = 1; xTile < ((SCREEN_WIDTH / 32) - 1); xTile++)
				{
						if (xTile == 1 && yTile == 1)
							{curTile = MENU_TOP_LEFT;}
						else if (xTile == 1 && yTile == ((SCREEN_HEIGHT / 32) - 2))
							{curTile = MENU_BOTTOM_LEFT;}
						else if (xTile == ((SCREEN_WIDTH / 32) - 2))
							{
								if (yTile == 1)
									{curTile = MENU_TOP_RIGHT;}
								else if (yTile == ((SCREEN_HEIGHT / 32) - 2) )
									{curTile = MENU_BOTTOM_RIGHT;}
								else
									{curTile = MENU_RIGHT;}
								
							}
						else if (xTile == 1)
							{curTile = MENU_LEFT;}
						else if (yTile == 1)
							{curTile = MENU_TOP;}
						else if (yTile == ((SCREEN_HEIGHT / 32) - 2))
							{curTile = MENU_BOTTOM;}
						else {curTile = MENU_BLANK;}
						
						game_graphics->drawSprite(menuBorder.at(curTile), 0, 0, xTile * 32, yTile * 32, 32, 32);
						
				}
		}	
	
}

void menuClass::drawBorder(int menuW, int menuH, int bgTile)
{
	
	int menuXspace = ((SCREEN_WIDTH / 32) - menuW);
	int menuYspace = ((SCREEN_HEIGHT / 32) - menuH);
	
	printf("Hello from the drawBorder function... is bgTile 0? It is: %d\n", bgTile);
	
	if (menuXspace % 2 == 0 && menuYspace % 2 == 0)
	{
		
		menuXspace = menuXspace / 2;
		menuYspace = menuYspace / 2;
		int xTile, yTile;
		xTile = yTile = 1;

		int curTile = 8;
	
	
		for (yTile = menuYspace; yTile < ((SCREEN_HEIGHT / 32) - menuYspace); yTile++)
		{
				for (xTile = menuXspace; xTile < ((SCREEN_WIDTH / 32) - menuXspace); xTile++)
				{
						if (xTile == menuXspace && yTile == menuYspace)
							{curTile = MENU_TOP_LEFT;}
						else if (xTile == menuXspace && yTile == ((SCREEN_HEIGHT / 32) - (menuYspace + 1)))
							{curTile = MENU_BOTTOM_LEFT;}
						else if (xTile == ((SCREEN_WIDTH / 32) - (menuXspace + 1)))
							{
								if (yTile == menuYspace)
									{curTile = MENU_TOP_RIGHT;}
								else if (yTile == ((SCREEN_HEIGHT / 32) - (menuYspace + 1)) )
									{curTile = MENU_BOTTOM_RIGHT;}
								else
									{curTile = MENU_RIGHT;}
								
							}
						else if (xTile == menuXspace)
							{curTile = MENU_LEFT;}
						else if (yTile == menuYspace)
							{curTile = MENU_TOP;}
						else if (yTile == ((SCREEN_HEIGHT / 32) - (menuYspace + 1)))
							{curTile = MENU_BOTTOM;}
						else 
							{
								if (bgTile > 8 && bgTile < menuBorder.size())
									{
										curTile = bgTile;
									}
								else
									{curTile = MENU_BLANK;}
							}
						
						game_graphics->drawSprite(menuBorder.at(curTile), 0, 0, xTile * 32, yTile * 32, 32, 32);
						
				}
		}
		//game_graphics->endScene();	

	}	
	else
	{
		printf("Error in menu border size, resorting to default...\n");
		drawBorderBackup();
	}
}
