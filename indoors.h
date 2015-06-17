#ifndef INDOORS_H
#define INDOORS_H
#include "gameobjs.h"


SDL_Surface* getIndoorObjSurface(int objType);
Coords getIndoorObjDimensions(int objType);


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
			
			void indoorInput();		
			
		private:
			bool isIndoors;
			
};


#endif
