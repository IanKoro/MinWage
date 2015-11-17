#include <SDL/SDL.h>
#include "SDLGraphics.h"

#define SPRITE_WIDTH   32
#define SPRITE_HEIGHT  32
//34x52

#define SCREEN_WIDTH  640 // 20 * 32
#define SCREEN_HEIGHT 480 // 15 * 32


#define PLAYER_UP		1
#define PLAYER_DOWN		0
#define PLAYER_LEFT		2
#define PLAYER_RIGHT	3

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

/*class SpriteType
{
	public:
		SDL_Surface *get_sprite() {return sprData;}
		void set_sprite(SDL_Surface *spriteDat) {sprData = spriteDat;}
	
		int get_idnum() {return id_num;}
		void set_idnum(int new_id) {id_num = new_id;}
		
		int width;
		int height;

	private:
		SDL_Surface *sprData;
		int id_num;
};*/

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

extern SDLGraphics *editor_graphics;
extern void setup_sprites();
extern void draw_sprites();
extern void get_input();
extern void clearKeys();

extern void writeToFile();
extern void clearMap();
//extern SpriteType get_spritedata(int spriteNum);
