#include "makeMap.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>




int makeMap()
{
	Coords spriteToWrite;
	char headerData[7] = {0xD0, 0xCE, 0xD1, 0xBA, 0, 0, 5};

	std::string filename = "datfile.dat";

	std::ofstream datfile;
	datfile.open(filename.c_str(), std::ios::binary);

	datfile.write((char *)&headerData, sizeof(headerData));

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
	
	datfile.close();

/*  Coords sprIn[2];

  std::ifstream datfileIn;
  datfileIn.open(filename.c_str(), std::ios::binary);
  datfileIn.read((char *)&sprIn, sizeof(sprIn));
  datfileIn.close();
*/
	return 0;

}

int loadMapFile(std::string fileName, int loadMapsX, int loadMapsY)
{
	
		//int loadMapX, loadMapY;
		int loadMapPosition = 0;
		
		
		Coords spriteHolder;
		//std::vector <Coords> bunchaSprites;
	
		char properHeader[4] = {0xD0, 0xCE, 0xD1, 0xBA};
		std::ifstream datfile;

		datfile.open(fileName.c_str(), std::ios::binary);
		datfile.seekg(0, datfile.end);
		int filelength = datfile.tellg();

		datfile.seekg(0, datfile.beg);
		
		char *hdata = new char[7];
		char *topData = new char[5];
		printf("Checking file header...\n");
		datfile.read(hdata, 7);
		loadMapPosition += 7;
		
		bool isGood = true;
		
		
		int byteCount = 0;
		while (isGood && byteCount < 4)
		{
			if (properHeader[byteCount] != hdata[byteCount])
			{
				isGood = false; 
			}
			
			byteCount++;
			
		}
		int totalMapsX;
		int totalMapsY;
			int numSprites;
		
		if (isGood == true)
		{
			totalMapsX = hdata[4];
			totalMapsY = hdata[5];
			numSprites = hdata[6];
			
			while (totalMapsX != loadMapsX || totalMapsY != loadMapsY)
			{
				for (int skipCount = 0; skipCount < numSprites; skipCount++)
				{
					datfile.read((char *)&spriteHolder, sizeof(spriteHolder));
				}
				datfile.read(topData, 5);
				if (topData[0] != properHeader[2] || topData[1] != properHeader[3])
				{
					exitMessage("Can't read map file!");
				}
				totalMapsX = topData[2];
				totalMapsY = topData[3];
				numSprites = topData[4];
				
			}
				
			int sprCounter;
			mapObjLocations.clear();
			
			
			for (sprCounter = 0; sprCounter < numSprites; sprCounter++)
			{
				datfile.read((char *)&spriteHolder, sizeof(spriteHolder));
				mapObjLocations.push_back(spriteHolder);
			}
			

		}
		else 
		{std::cout << "Bad datafile. BAD.\n";}
		datfile.close();
		return 0;
}
