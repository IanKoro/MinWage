#ifndef MENUCLASS_H
#define MENUCLASS_H

#include <string>
#include <vector>

#define MENU_TOP_LEFT  		0
#define MENU_TOP_RIGHT		1

#define MENU_BOTTOM_LEFT 	2
#define MENU_BOTTOM_RIGHT	3

#define MENU_TOP			4
#define MENU_BOTTOM			5

#define MENU_LEFT			6
#define MENU_RIGHT  		7

#define MENU_BLANK			8

#define FLOORTILES_KITCHEN  		9
#define FLOORTILES_PLAIN  			10
#define FLOORTILES_PLAIN_SMALL  	11

class menuItem
{
		
	public:
		menuItem();
		~menuItem();
		
		std::string caption;
		int x_coord;
		int y_coord;
		
		int tR, tG, tB;
		int bR, bG, bB;
	
};

class menuClass
{
	public:
		menuClass();
		~menuClass();
		
		void displayMenu();
		
		void drawMenuItems(int selectedItem);
		
		void doMenuItem(int menuSel);
		   
		int menuState();
		
		void drawBorderBackup();
		void drawBorder(int menuW, int menuH, int bgTile = 0);
	private:
		std::vector <menuItem> menuItemList;
		
};

#endif
