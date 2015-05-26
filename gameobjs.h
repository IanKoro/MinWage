#ifndef GAMEOBJS_H
#define GAMEOBJS_H

#include <SDL.h>
#include <SDL_ttf.h>
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
		
		void throttleX(int xch) {xvel += xch;}
		void throttleY(int ych) {yvel += ych;}

		void changeX(int xch) {x += xch;}
		void changeY(int ych) {y += ych;}
		
		SDL_Surface* playerBMP;
		
		//these next two sets of functions are kind of redundant, but meh...

		void zeroX() {xvel = 0;}
		void zeroY() {yvel = 0;}

		void setXvel(int xvval) {xvel = xvval;}
		void setYvel(int yvval) {yvel = yvval;}
	
		void startWalk() {walking = true;}
		void stopWalk() {walking = false;}
		
		bool isWalk() {return walking;}
		
		void setDir(int dir) {direction = dir;}
		int getDir() {return direction;}
		
	private:
		int x;
		int y;
		int xvel;
		int yvel;
		
		int direction; //0-down 1-up 2-left 3-right
		
		bool walking;
		
		
};

class Coords
{
	public:
		void setX(int xval) {x = xval;}
		void setY(int yval) {y = yval;}

		int getX() {return x;}
		int getY() {return y;}
		
	private:
		int x;
		int y;
};

#endif
