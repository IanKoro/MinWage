	//Start of Map X: 4 Y: 5
	//No. sprites: 3

	smallHead[2] = 4; //map X loc
	smallHead[3] = 5; //map Y loc
	smallHead[4] = 3; //no. sprites
	datfile.write((char *)&smallHead, sizeof(smallHead));

	spriteToWrite.setX(4);
	spriteToWrite.setY(3);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(8);
	spriteToWrite.setY(5);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(11);
	spriteToWrite.setY(8);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

