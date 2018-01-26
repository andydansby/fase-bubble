void enemyAI(unsigned char enemyData[], unsigned char playerX, unsigned char playerY)
{
	unsigned char enemyX,enemyY,enemyF,enemyImage,enemyStatus;
	unsigned char randomNumber;	
	unsigned char decision;
//	unsigned char a;//junk variable
//	unsigned char b;//junk variable
	
	//tiles array is unsigned char
	
//	unsigned char tileType;	
//	unsigned char north, south, east, west;
//	unsigned char northBarrierCheck, southBarrierCheck;
//	unsigned char eastBarrierCheck, westBarrierCheck;

//	a = 128;
//	b = 0;	
//b ^= a;

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

		
	//north = enemyY - 32;
	//south = enemyY + 32;
	//east = enemyX - 32;
	//west = enemyX + 32;
	
	//tempX = enemyX >> 4;//is tile position
	//northBarrierCheck = 
	
	
	//printtester2(sprites[1].x, sprites[1].y);
	//printtester2(enemyX, north);
	//printtester1(tempX);
	//printtester4(enemyStatus);//artificial stupidity 2
	
	//0 == enemy chasing
	//1 == enemy retreating

	
	//decision = rand()%5;	
	

	{//testing junk
		//artificial stupidity part 2
		
		//unsigned char enemyStatus [4] = {0,0,0,0}; //track each enemy for hits
		
		
			//sprites[i].x && sprites[i].y == direction of sprites
			//sprites[i].n == The .n is the number of the sprite (will draw a different sprite if changed
			//the .f has no effect on the engine, but it's used by the demo to store the direction of movement (it's diagonal movement so only 4 directions).
			
			
		/*		
					west = (sprites[0].x >> 4) - 1;
					east = (sprites[0].x >> 4) + 1;
					south  = (sprites[0].y >> 4) + 1;
					north  = (sprites[0].y >> 4) - 1;
					
					//enemy sprites
					tmpx = sprites[0].x;
					tmpy = sprites[0].y;
					tileType = tiles[tmpy * scrw + tmpx];
					
					westBarrierCheck  = tiles[tmpy * scrw + west];
					eastBarrierCheck  = tiles[tmpy * scrw + west];
					northBarrierCheck = tiles[north * scrw + tmpx];
					southBarrierCheck = tiles[south * scrw + tmpx];
		*/
					
				//	if (
					/*
						tmpx= sprites[i].x>>4;
						tmpy= sprites[i].y>>4;
						
							if ( tiles[tmpy*scrw+tmpx]== ? ){
								do stuff
							}*/
					
				//	printtester3(tmpx, tmpy);
				//	printtester4(north);//printtester1(tileType);

		//if (sprites[i].f < 128) {decision = RND(5);	}
		//if (sprites[i].f == 128) {decision = 200;}//run away	
		//if (enemyStatus == 0){decision = RND(5);	}
		//if (enemyStatus == 1){decision = 0;	}
	}
	
	
	
	if (decision == 0)
	{
		//do nothing
	}
else
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
else
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
else
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
else
	if (decision == 4)
	{//stop just shy of the players position, like a game of chicken
		if (enemyX > playerX + 16)
		{
			enemyX--;
		}
		if (enemyX < playerX - 16)
		{
			enemyX++;
		}
		
		if (enemyY > playerY + 16)
		{
			enemyY--;
		}
		if (enemyY < playerY - 16)
		{
			enemyY++;
		}
	}
else	
	if (decision == 99)
	{
		if (enemyY > playerY)
		{
			enemyY--;
		}
		
		
		if (enemyY < playerY)
		{
			enemyY++;
		}
	}
else
	if (decision == 100)
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
else
	if (decision == 200)
	{
		//retreat from player
		if (enemyX > playerX)
		{
			enemyX++;
		}
		if (enemyX < playerX);
		{
			enemyX--;
		}
		if (enemyY > playerY)
		{
			enemyY++;
		}
		if (enemyY < playerY)
		{
			enemyY--;
		}
	}
	
	
	
	
	//artificial stupidity 2
	enemyData[0] = enemyX;
	enemyData[1] = enemyY;
	enemyData[2] = enemyImage;
	enemyData[3] = enemyF;
	enemyData[4] = enemyStatus;
}
