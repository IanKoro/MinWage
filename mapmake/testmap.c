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

