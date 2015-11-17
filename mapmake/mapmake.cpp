#include <ctype.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_events.h>

#include "SDLGraphics.h"
#include "mapmake.h"



bool keysHeld[323];
bool keysHit[323];

SDL_Event m_event;	
SDLGraphics *editor_graphics = NULL;

//SpriteType spriteRock;
//SpriteType spriteBigRock;
//SpriteType spriteBar;
//SpriteType spriteApart;

std::map <int, GameObject> AllGameObjects;
//std::vector <SpriteType> gameSprites;
std::vector <Coords> mapObjLocations;


int main()
{

	Coords tempCoord;

	SDL_Surface *cursorTile = IMG_Load("hilite.png");
	
	SDL_SetColorKey(cursorTile,
					SDL_SRCCOLORKEY,
					SDL_MapRGB(cursorTile->format, 255, 0, 255));
					
	SDL_Surface *sepBar = IMG_Load("sepBar.png");
					
	int positionX, positionY;
	
	int spr_sel = 1;
	char spr_selDisp[4];

	Coords dimHolder;
		
	positionX = positionY = 0;
	
	editor_graphics = new SDLGraphics(SCREEN_WIDTH+150, SCREEN_HEIGHT, "MW MapEd", 0,90,0);

	setup_sprites();
	editor_graphics->beginScene();
	get_input();

	while (keysHeld[SDLK_ESCAPE] == false)
	{
			clearKeys();
			editor_graphics->beginScene();
			draw_sprites();
			editor_graphics->drawSprite(cursorTile, 0, 0, positionX * 32, positionY * 32, 32, 32);
			
			sprintf(spr_selDisp, "%d", spr_sel);
			editor_graphics->drawText(spr_selDisp, 30, 655, 10, 0, 50, 150, 0, 0, 0 );
			
			dimHolder = AllGameObjects[spr_sel].getDimensions();
			editor_graphics->drawSprite(sepBar, 0, 0, 640, 0, 7, 480);			
			editor_graphics->drawSprite(AllGameObjects[spr_sel].get_sprite(), 0,0, 650, 50, dimHolder.getX(), dimHolder.getY());
			
			editor_graphics->endScene();
			get_input();
			if (keysHit[SDLK_DOWN]) 
				{
					if ((positionY * 32) < 448) {positionY++;}
				}
			if (keysHit[SDLK_UP])
				{
					if (positionY > 0) {positionY--;}
				}			
			if (keysHit[SDLK_LEFT]) 
				{
					if (positionX > 0) {positionX--;}
				}
			if (keysHit[SDLK_RIGHT])
				{
					if ((positionX * 32) < 608) {positionX++;}
				}

			if (keysHit[SDLK_a])
				{
					if (spr_sel > 1)
					{
						spr_sel--;
					}
				}

			if (keysHit[SDLK_z])
				{

					if (spr_sel < 7)
					{
						spr_sel++;
					}
				}

			if (keysHit[SDLK_c])
				{
					clearMap();
				}

			if (keysHit[SDLK_w])
				{
					writeToFile();
				}
				
			if (keysHit[SDLK_SPACE])
				{
					tempCoord.setX(positionX);
					tempCoord.setY(positionY);
					tempCoord.setObjType(spr_sel);
					mapObjLocations.push_back(tempCoord);
					SDL_Delay(50);
				}

			if (keysHit[SDLK_DELETE])
				{
					if (mapObjLocations.size() > 0)
					{
						mapObjLocations.pop_back();
						SDL_Delay(50);
					}
				}

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

void setup_sprites()
{
	
	GameObject tempObj;
	
	
	tempObj.set_sprite(IMG_Load("../images/rock.png"));
	tempObj.setDimensions(32,32);
	AllGameObjects[1] = tempObj;
	
	tempObj.set_sprite(IMG_Load("../images/bigrock.png"));
	tempObj.setDimensions(32,32);
	AllGameObjects[2] = tempObj;
	
	tempObj.set_sprite(IMG_Load("../images/bar.png"));
	tempObj.setDimensions(94,64);
	AllGameObjects[3] = tempObj;

	tempObj.set_sprite(IMG_Load("../images/building.png"));
	tempObj.setDimensions(128, 288);
	AllGameObjects[4] = tempObj;

	tempObj.set_sprite(IMG_Load("../images/tree.png"));
	tempObj.setDimensions(32, 64);
	AllGameObjects[5] = tempObj;

	tempObj.set_sprite(IMG_Load("../images/shrub.png"));
	tempObj.setDimensions(32, 32);
	AllGameObjects[6] = tempObj;

	tempObj.set_sprite(IMG_Load("../images/tree2.png"));
	tempObj.setDimensions(50, 110);
	AllGameObjects[7] = tempObj;
}


void draw_sprites()
{
	int sprHolder;
	Coords dimHolder;
	for (int i = 0; i < mapObjLocations.size(); i++)
	{
		sprHolder = mapObjLocations.at(i).getObjType();
		dimHolder = AllGameObjects[sprHolder].getDimensions();
		editor_graphics->drawSprite(AllGameObjects[sprHolder].get_sprite(), 0,0, mapObjLocations.at(i).getX() * 32, mapObjLocations.at(i).getY() * 32, dimHolder.getX(), dimHolder.getY());
	}
}

/*
SpriteType get_spritedata(int spriteNum)
{
	
	return AllGameObjects[spriteNum];
	
	if (spriteNum == 1)
	{
		return spriteRock;
	}
	else if (spriteNum == 2)
	{
		return spriteBigRock;
	}
	else if (spriteNum == 3)	
	{
		return spriteBar;
	}
	else if (spriteNum == 4)
	{
		return spriteApart;
	}
	
}
*/

void get_input()
{	
   if (SDL_PollEvent(&m_event))
   {
      if (m_event.type == SDL_QUIT)
      {
      }

      if (m_event.type == SDL_KEYDOWN)
      {
         keysHeld[m_event.key.keysym.sym] = true;
         keysHit[m_event.key.keysym.sym] = false;
      }

      if (m_event.type == SDL_KEYUP)
      {
         keysHeld[m_event.key.keysym.sym] = false;
         keysHit[m_event.key.keysym.sym] = true;
      }
   }
 

}

void clearKeys()
{
	int i = 0;
	for (i = 0; i < 323; i++)
	{
		keysHeld[i] = false;
		keysHit[i] = false;
	}
}

void writeToFile()
{
	std::string fileName;
	char charInput;
	int mapLocX, mapLocY;

	std::cout << "[A]ppend or [N]ew file?";
	std::cin >> charInput;
	charInput = toupper(charInput);
	
	while (charInput != 'A' && charInput != 'N')
	{
		std::cout << "Invalid option.\n";
		std::cout << "[A]ppend or [N]ew file?";
		std::cin >> charInput;
		charInput = toupper(charInput);
	}
	
	
	std::cout << "Enter filename: ";
	std::cin >> fileName;

	std::cout << "Enter map X:";
	std::cin >> mapLocX;

	std::cout << "Enter map Y:";
	std::cin >> mapLocY;
	
	std::ofstream outputFile;
	
	if (charInput == 'N')
	{
		outputFile.open(fileName.c_str());
	}
	else
	{
		outputFile.open(fileName.c_str(), std::ios_base::app);
	}

	//Actually writing to file now...

	outputFile << "\t//Start of Map X: " << mapLocX << " Y: " << mapLocY << "\n";
	outputFile << "\t//No. sprites: " << mapObjLocations.size() << "\n\n";	
	outputFile << "\tsmallHead[2] = " << mapLocX << "; //map X loc\n";
	outputFile << "\tsmallHead[3] = " << mapLocY << "; //map Y loc\n";
	outputFile << "\tsmallHead[4] = " << mapObjLocations.size() << "; //no. sprites\n";
	outputFile << "\tdatfile.write((char *)&smallHead, sizeof(smallHead));\n\n";

	for (int i = 0; i < mapObjLocations.size(); i++)
	{
			outputFile << "\tspriteToWrite.setX(" << mapObjLocations.at(i).getX() << ");\n";
			outputFile << "\tspriteToWrite.setY(" << mapObjLocations.at(i).getY() << ");\n";
			outputFile << "\tspriteToWrite.setObjType(" << mapObjLocations.at(i).getObjType() << ");\n";	
			outputFile << "\tdatfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));\n\n";
	}
	outputFile.close();
	std::cout << "Finished writing to file.\n"; 

}

void clearMap()
{
	mapObjLocations.clear();
}
