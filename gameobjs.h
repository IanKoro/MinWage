#ifndef GAMEOBJS_H
#define GAMEOBJS_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <vector>

#define SPRITE_WIDTH   32
#define SPRITE_HEIGHT  32
//34x52

#define SCREEN_WIDTH  640 // 20 * 32
#define SCREEN_HEIGHT 480 // 15 * 32


#define PLAYER_UP		1
#define PLAYER_DOWN		0
#define PLAYER_LEFT		2
#define PLAYER_RIGHT	3

SDL_Surface* getObjSurface(int objType);

SDL_Surface* getObjSurfaceMasks(int objType);

class Player
{
	public:
	
		Player();
		~Player();
		
		void setX(int xval) {x = xval;}
		void setY(int yval) {y = yval;}
		
		int getX() {return x;}
		int getY() {return y;}
		
		int getXvel() {return xvel;}
		int getYvel() {return yvel;}

		void setXvel(int xvval) {xvel = xvval;}
		void setYvel(int yvval) {yvel = yvval;}
				
		void throttleX(int xch) {xvel += xch;}
		void throttleY(int ych) {yvel += ych;}

		void changeX(int xch) {x += xch;}
		void changeY(int ych) {y += ych;}

		void setMapX(int xval) {mapX = xval;}
		void setMapY(int yval) {mapY = yval;}
		
		int getMapX() {return mapX;}
		int getMapY() {return mapY;}

		void changeMapX(int xch) {mapX += xch;}
		void changeMapY(int ych) {mapY += ych;}
		
		SDL_Surface* playerBMP;
		
		//these next two sets of functions are kind of redundant, but meh...

		void zeroX() {xvel = 0;}
		void zeroY() {yvel = 0;}


	
		void startWalk() {walking = true;}
		void stopWalk() {walking = false;}
		
		bool isWalk() {return walking;}
		
		void setDir(int dir) {direction = dir;}
		int getDir() {return direction;}
		
		void moveChar();
		
	private:
		int x;
		int y;
		int xvel;
		int yvel;
		
		int mapX;
		int mapY;
		
		int direction; //0-down 1-up 2-left 3-right
		
		bool walking;
		
		
};

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

class GameObject
{
	public:
		//GameObject();
		//~GameObject();
		
		void set_sprite(SDL_Surface *sprData);
		void set_spriteMask(SDL_Surface *sprmskData) {spriteMaskData = sprmskData;}		
		
		SDL_Surface* get_sprite() {return spriteData;}
		SDL_Surface* get_spriteMask() {return spriteMaskData;}
		
		
		void setDimensions(int width, int height) {objDimensions.setX(width); objDimensions.setY(height);}
		Coords getDimensions() {return objDimensions;}
		void setDimensions(Coords setDim) {objDimensions = setDim;}
		
		void clear() {spriteData = NULL; spriteMaskData = NULL;}
		
	private:
		Coords objDimensions;
		
		SDL_Surface *spriteData;
		SDL_Surface *spriteMaskData;
};

Coords getObjDimensions(int objType);

#endif
