#ifndef INDOORS_H
#define INDOORS_H
#include "gameobjs.h"


//SDL_Surface* getIndoorObjSurface(int objType);
Coords getIndoorObjDimensions(int objType);
int getIndoorFloor(int roomNum);

class IndoorHandler
{
		public:
			IndoorHandler();
			~IndoorHandler();
			void drawRoomView(int roomNumber);
			void drawRoomSprites(int roomNum);
			
			bool isInside() {return isIndoors;}
			void goInside(int roomNumber);
			void goOutside();
			
			//void indoorInput();		
			
			SDL_Surface* getIndoorObjSurface(int objType);
			
			int collideObjTest(int chX, int chY);
			int collideWith(int collideItem);
			//Coords getIndoorObjDimensions(int objType);
			//int getIndoorFloor(int roomNum);
			
		private:
			bool isIndoors;
			bool firstLoad;
			
			
			std::vector <Coords> indoorObjLocations;
			
};


#endif
