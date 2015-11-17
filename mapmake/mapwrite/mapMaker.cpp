

#include "mapMaker.h"

int makeMap(std::string filename);


int main(int argc, char* argv[])
{
	
	  if (argc > 1)
		{
			std::string arg1(argv[1]);
			std::cout << "Yes.\n";
			makeMap(arg1);
		}
		else
		{
			std::cout << "No.\n";
		}
		return 0;
}


/*
int makeMap(std::string filename)
{
	Coords spriteToWrite;
	char headerData[2] = {0xD0, 0xCE};
	char smallHead[5] = {0xD1, 0xBA, 0, 0, 0};
	//std::string filename = "datfile.dat";

	std::ofstream datfile;
	datfile.open(filename.c_str(), std::ios::binary);

	datfile.write((char *)&headerData, sizeof(headerData));

////////////////
////SPLICE IN GENERATED MAP DATA HERE
////////////////

	//map 1 (0, 0) - 5 sprites (see headerData)
	smallHead[2] = 0; //x and y values of map2
	smallHead[3] = 0;	
	smallHead[4] = 5; //num of sprites
	datfile.write((char *)&smallHead, sizeof(smallHead));
	
	spriteToWrite.setX(2);
	spriteToWrite.setY(2);
	spriteToWrite.setObjType(1);	


	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));
	
	spriteToWrite.setX(4);
	spriteToWrite.setY(4);
	spriteToWrite.setObjType(2);	

	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(6);
	spriteToWrite.setY(6);
	spriteToWrite.setObjType(1);	

	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(11);
	spriteToWrite.setY(3);
	spriteToWrite.setObjType(3);	

	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));
	
	spriteToWrite.setX(11);
	spriteToWrite.setY(4);
	spriteToWrite.setObjType(91);	

	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));


	//map 2 (0, 1) - 4 sprites
	
	smallHead[2] = 0; //x and y values of map2
	smallHead[3] = 1;	
	smallHead[4] = 4; //num of sprites
	
	datfile.write((char *)&smallHead, sizeof(smallHead));
	
	spriteToWrite.setX(2);
	spriteToWrite.setY(2);
	spriteToWrite.setObjType(1);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(18);
	spriteToWrite.setY(12);
	spriteToWrite.setObjType(1);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(16);
	spriteToWrite.setY(10);
	spriteToWrite.setObjType(2);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(10);
	spriteToWrite.setY(7);
	spriteToWrite.setObjType(2);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));
		
		
	//map 3 (0, 2) - 2 sprites
	
	smallHead[2] = 0; //x and y values of map2
	smallHead[3] = 2;	
	smallHead[4] = 2; //num of sprites
	
	datfile.write((char *)&smallHead, sizeof(smallHead));
	
	spriteToWrite.setX(10);
	spriteToWrite.setY(2);
	spriteToWrite.setObjType(4);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(10);
	spriteToWrite.setY(10);
	spriteToWrite.setObjType(92);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));
	

	//map 4 - (1, 0)
	//Start of Map X: 1 Y: 0
	//No. sprites: 11

	smallHead[2] = 1; //map X loc
	smallHead[3] = 0; //map Y loc
	smallHead[4] = 11; //no. sprites
	datfile.write((char *)&smallHead, sizeof(smallHead));

	spriteToWrite.setX(6);
	spriteToWrite.setY(4);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(6);
	spriteToWrite.setY(6);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(9);
	spriteToWrite.setY(6);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(9);
	spriteToWrite.setY(4);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(7);
	spriteToWrite.setY(5);
	spriteToWrite.setObjType(6);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(8);
	spriteToWrite.setY(5);
	spriteToWrite.setObjType(6);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(11);
	spriteToWrite.setY(5);
	spriteToWrite.setObjType(7);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(13);
	spriteToWrite.setY(2);
	spriteToWrite.setObjType(5);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(14);
	spriteToWrite.setY(2);
	spriteToWrite.setObjType(5);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(7);
	spriteToWrite.setY(3);
	spriteToWrite.setObjType(2);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(8);
	spriteToWrite.setY(3);
	spriteToWrite.setObjType(2);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	

	
	//map 5 - (1, 1)
	
	smallHead[2] = 1; //x and y values of map2
	smallHead[3] = 1;	
	smallHead[4] = 3; //num of sprites
	
	datfile.write((char *)&smallHead, sizeof(smallHead));
	
	spriteToWrite.setX(17);
	spriteToWrite.setY(10);
	spriteToWrite.setObjType(1);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(18);
	spriteToWrite.setY(10);
	spriteToWrite.setObjType(2);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(19);
	spriteToWrite.setY(10);
	spriteToWrite.setObjType(1);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));	
	//map 6 - (1, 2)
	
	smallHead[2] = 1; //x and y values of map2
	smallHead[3] = 2;	
	smallHead[4] = 3; //num of sprites

	datfile.write((char *)&smallHead, sizeof(smallHead));

	spriteToWrite.setX(6);
	spriteToWrite.setY(7);
	spriteToWrite.setObjType(1);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));
	
	spriteToWrite.setX(7);
	spriteToWrite.setY(8);
	spriteToWrite.setObjType(5);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(7);
	spriteToWrite.setY(5);
	spriteToWrite.setObjType(6);	
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

////////////////
////END OF SPLICED IN MAP DATA 
////////////////



	datfile.close();


	return 0;

}
*/
