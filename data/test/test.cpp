#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


class SpriteObj
{
public:
  int isWall;
  //char isWall;
  int xpos;
  int ypos;
  int thing_num;

};

int main()
{

  SpriteObj spr1;

  spr1.isWall = 1;
  spr1.xpos = 12;
  spr1.ypos = 22;
  spr1.thing_num = 132;


  SpriteObj spr2;

  spr2.isWall = 0;
  spr2.xpos = 65;
  spr2.ypos = 4;
  spr2.thing_num = 88;


  std::string filename = "datfile.dat";

  std::ofstream datfile;
  datfile.open(filename.c_str(), std::ios::binary);

  

  datfile.write((char *)&spr1, sizeof(spr1));
  datfile.write((char *)&spr2, sizeof(spr2));
  datfile.close();

  SpriteObj sprIn[2];

  std::ifstream datfileIn;
  datfileIn.open(filename.c_str(), std::ios::binary);
  datfileIn.read((char *)&sprIn, sizeof(sprIn));
  datfileIn.close();

  std::cout << "Sprite 1 Data\n\nIsWall: ";
  if (spr1.isWall == 0) {std::cout << "Yes";}
  else if (spr1.isWall == 1) {std::cout << "No";}
  std::cout << "\n";
  std::cout << "X: " << spr1.xpos << "\nY: " << spr1.ypos << "\nID Num: " << spr1.thing_num << std::endl;

  std::cout << "Sprite 2 Data\n\nIsWall: ";
  if (spr2.isWall == 0) {std::cout << "Yes";}
  else if (spr2.isWall == 1) {std::cout << "No";}
  std::cout << "\n";
  std::cout << "X: " << spr2.xpos << "\nY: " << spr2.ypos << "\nID Num: " << spr2.thing_num << std::endl;


  std::cout << "Sprite 1 File\n\nIsWall: ";
  if (sprIn[0].isWall == 0) {std::cout << "Yes";}
  else if (sprIn[0].isWall == 1) {std::cout << "No";}
  std::cout << "\n";
  std::cout << "X: " << sprIn[0].xpos << "\nY: " << sprIn[0].ypos << "\nID Num: " << sprIn[0].thing_num << std::endl;

  std::cout << "Sprite 2 File\n\nIsWall: ";
  if (sprIn[1].isWall == 0) {std::cout << "Yes";}
  else if (sprIn[1].isWall == 1) {std::cout << "No";}
  std::cout << "\n";
  std::cout << "X: " << sprIn[1].xpos << "\nY: " << sprIn[1].ypos << "\nID Num: " << sprIn[1].thing_num << std::endl;



  return 0;
}

