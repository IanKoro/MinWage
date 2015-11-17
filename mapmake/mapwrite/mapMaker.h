#ifndef MAPMAKER_H
#define MAPMAKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class Coords
{
	public:
		//Coords() {isWall = false;}
		//~Coords();
		void setX(int xval) {x = xval;}
		void setY(int yval) {y = yval;}

		int getX() {return x;}
		int getY() {return y;}
		
		void setObjType(int objVal) {objType = objVal;}
		int getObjType() {return objType;}
		
		bool isWall;
		

		
	private:
		int x;
		int y;
		
		int objType;
};



#endif
