#ifndef MAPS_H
#define MAPS_H

//#define MAPSIZE_X		3
//#define MAPSIZE_Y		2

#define MAPSIZE_X		2
#define MAPSIZE_Y		3




class AllMaps
{
	public:
		AllMaps();
		~AllMaps();
		char *gameMaps[MAPSIZE_Y][MAPSIZE_X];
		
		void loadMapfromFile(int x, int y);
		
		bool checkFileHeader(std::string fileName);
		/*
		int *gameMaps[MAPSIZE_Y][MAPSIZE_X] = 
		{
			{overlayMap01, overlayMap02, overlayMap03}, 
			{overlayMap04, overlayMap05, overlayMap06},
		};*/
};
#endif
