void enemyAI(unsigned char enemyData[], unsigned char playerX, unsigned char playerY)
{
	unsigned char enemyX,enemyY,enemyF,enemyImage,enemyStatus;
	unsigned char randomNumber;
	unsigned char decision;
	
	romCounter ++;//randomize function
	if (romCounter > 8192) romCounter = 0;//randomize function	
	
	randomNumber = bpeek (romCounter);//randomize function
	
	//artificial stupidity 2
	enemyX = enemyData[0];
	enemyY = enemyData[1];
	enemyImage = enemyData[2];
	enemyF = enemyData[3];
	enemyStatus = enemyData[4];
	
	decision = ((unsigned char)randomNumber % 5);//randomize function
	//printtester1(decision);//printtester1(decision);// 23672	
	//Pause(4);

	//printtester2(sprites[1].x, sprites[1].y);
	//printtester2(enemyX, north);
	//printtester1(tempX);
	//printtester4(enemyStatus);//artificial stupidity 2
	
	//0 == enemy chasing
	//1 == enemy retreating

	if (decision == 0)
	{
		//do nothing
	}
	if (decision == 1)
	{
		//move toward player y
		if (enemyY > playerY)
		{
			enemyY--;
		}		
		if (enemyY < playerY)
		{
			enemyY++;
		}
	}
	if (decision == 2)
	{
		//move toward player x
		if (enemyX > playerX)
		{
			enemyX--;
		}
		if (enemyX < playerX)
		{
			enemyX++;
		}
	}
	if (decision == 3)
	{
		//move toward player x and y
		if (enemyX > playerX)
		{
			enemyX--;
		}
		if (enemyX < playerX)
		{
			enemyX++;
		}
		if (enemyY > playerY)
		{
			enemyY--;
		}
		if (enemyY < playerY)
		{
			enemyY++;
		}
	}	
	//artificial stupidity 2
	enemyData[0] = enemyX;
	enemyData[1] = enemyY;
	enemyData[2] = enemyImage;
	enemyData[3] = enemyF;
	enemyData[4] = enemyStatus;
}
