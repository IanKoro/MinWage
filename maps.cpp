#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "maps.h"

/************************************
 *  Find an order for the maps in the dat file, 
 * and a way to find which byte to start at. 
 * (order # * 300 bytes)
 ***********************************/ 


AllMaps::AllMaps()
{
	//y = 2 x = 3
	    checkFileHeader("data/map33.dat");
		loadMapfromFile(0,0);
		loadMapfromFile(0,1);
		loadMapfromFile(0,2);
		loadMapfromFile(1,0);
		loadMapfromFile(1,1);
		loadMapfromFile(1,2);


}

AllMaps::~AllMaps()
{}


/******
 * 	Find position in file:
 * 		((MAPSIZE_X * x)	+ y) * 300 bytes
 *****/

 
void AllMaps::loadMapfromFile(int x, int y)
{
	
		int header_offset = 20;
		std::string filename = "data/map33.dat";
		std::ifstream datfile;
		int fileMapPosition = header_offset + (((MAPSIZE_X * x) + y) * 300);
		datfile.open(filename.c_str(), std::ios::binary);
		datfile.seekg(0, datfile.end);
		int filelength = datfile.tellg();

		datfile.seekg(fileMapPosition, datfile.beg);
		
		char *data = new char[300];
		//int mapData[300];

		datfile.read(data, 300);
		
		//printf("Filelength: %d\nChar length: %d\n", filelength, strlen(data));

		gameMaps[x][y] = data;
		
		datfile.close();

}

bool AllMaps::checkFileHeader(std::string fileName)
{
	
		char properHeader[4] = {0xD0, 0xCE, 0xD1, 0xBA};
//		std::string filename = "data/map33.dat";
		std::ifstream datfile;

		datfile.open(fileName.c_str(), std::ios::binary);
		datfile.seekg(0, datfile.end);
		int filelength = datfile.tellg();

		datfile.seekg(0, datfile.beg);
		
		
		char *data = new char[19];
		printf("Checking file header...\n");
		datfile.read(data, 20);
		bool isGood = true;
		
		
		int byteCount = 0;
		while (isGood && byteCount < 4)
		{
			if (properHeader[byteCount] != data[byteCount])
			{
				isGood = false; 
			}
			
			byteCount++;
			
			
		}
			/****
		if (properHeader[0] == data[0])
		{
				printf("Byte 1 matches!\n");
				if (properHeader[1] == data[1])
				{
					printf("Byte 2 matches!\n");
					if (properHeader[2] == data[2])
					{
						printf("Byte 3 matches!\n");
						if (properHeader[3] == data[3])
						{
							printf("Byte 4 matches!\n");
							
							isGood = true;
					}
				}
		}***/
		
	if (isGood)
	{printf("Good\n");}
	else
	{printf("Bad\n");}	
	
	return isGood;
			
	
	
	
}
