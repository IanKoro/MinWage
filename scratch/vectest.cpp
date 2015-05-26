#include <iostream>
#include <stdio.h>
#include <vector>

class coords
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

int main()
{
	int wid = 640/32;
	int hei = 480/32;
	
	int x = 0;
	
	std::vector <coords> screenTiles(3);
	
	screenTiles.at(0).setX(55);

	x = screenTiles.at(0).getX();
	
	printf("HI: %d\n", x);
	//std::cout << "til1: " << screenTiles.at(0).getX() << std::endl;
	return 0;
}
