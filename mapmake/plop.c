	//Start of Map X: 0 Y: 1
	//No. sprites: 7

	smallHead[2] = 0; //map X loc
	smallHead[3] = 1; //map Y loc
	smallHead[4] = 7; //no. sprites
	datfile.write((char *)&smallHead, sizeof(smallHead));

	spriteToWrite.setX(1);
	spriteToWrite.setY(1);
	spriteToWrite.setObjType(1);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(1);
	spriteToWrite.setY(3);
	spriteToWrite.setObjType(2);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(3);
	spriteToWrite.setY(0);
	spriteToWrite.setObjType(3);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(6);
	spriteToWrite.setY(0);
	spriteToWrite.setObjType(4);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(10);
	spriteToWrite.setY(0);
	spriteToWrite.setObjType(5);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(11);
	spriteToWrite.setY(0);
	spriteToWrite.setObjType(6);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

	spriteToWrite.setX(11);
	spriteToWrite.setY(1);
	spriteToWrite.setObjType(7);
	datfile.write((char *)&spriteToWrite, sizeof(spriteToWrite));

