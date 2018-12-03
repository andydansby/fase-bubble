#ifndef ENEMY_H
#define ENEMY_H

#define SHR3 (jz=jsr, jsr^=(jsr<<7), jsr^=(jsr>>5), jsr^=(jsr<<3),jz+jsr)


void transportEnemy()
{
	//M_OUTP(0xfe, 6);//flashes to show that sprite has touched a barrier
	//enemyX = 24;
	//enemyY = 24;
	
	
	
	enemyX = enemyLaunchX;
	enemyY = enemyLaunchY;
	
	//enemyLaunchX, enemyLaunchY;
	sprites[i].x = enemyLaunchX;
	sprites[i].y = enemyLaunchY;	
	
	sprites[i].n -= 128;//make sprite reappear
	
	//FRAME;// we force update screen to be able to catch the tile-set for the attributes	
	
	//beepfx(4);
	
	//yourScore ++;
	yourScore +=10;
}


void bulletHits()
{
	if( sprites[i].n < 128 )
	//does your bullet hit a baddie, 10 is an offset from center of baddie sprite
	for ( j= 0; j < num_bullets; ++j )
	{
		
		if( abs(bullets[j].x-sprites[i].x) + abs(bullets[j].y-sprites[i].y) < 10 )
		{
			// go subroutine enemy death
			sprites[i].n += 128;//make sprite disappear 
			remove_bullet(j);
			
			//tmpx= sprites[i].x>>4;
			//tmpy= sprites[i].y>>4;
			//tiles[tmpy*scrw+tmpx]= 68;//marker where enemy dies
			//tilepaint(tmpx, tmpy, tmpx, tmpy);
			//Sound(EFFX, 1+killed++%5);//registers how many enemies are killed
			
			singleBullet = 1;//can now fire again
			
			 //place sound effect here  
			transportEnemy();
			
			//sprites[i].x = 24;
			//sprites[i].y = 24;
			//sprites[i].n -= 128;//make sprite reappear
			//killed ++;
			//*drwout= (unsigned int)update_scoreboard;
		}

		tmpx1 = bullets[j].x >> 4;
		tmpy1 = bullets[j].y >> 4;
		center = tmpx1 + scrw * tmpy1;
		
		if (tiles[center] > 15)//if (tiles[center] > 0)
		{
			remove_bullet(j);
			singleBullet = 1;//can now fire again
		}
		
		if (bullets[j].x > 232)
		{
			remove_bullet(j);
			singleBullet = 1;//can now fire again
		}
		if (bullets[j].x < 8)
		{
			remove_bullet(j);
			singleBullet = 1;//can now fire again
		}
		if (bullets[j].y < 8)
		{
			remove_bullet(j);
			singleBullet = 1;//can now fire again
		}
		if (bullets[j].y > 152)
		{
			remove_bullet(j);
			singleBullet = 1;//can now fire again
		}
		
		
	}

	
}


// ****** FUNCTIONS STILL WORKING ON
//void enemyCollision(unsigned char playerX, unsigned char playerY, unsigned char enemyXX, unsigned char enemyYY, unsigned char enemyFF)


/*
void printGrassFire()
{	
	center = 0;	
	screenScanX = screenScanY = 0;
	
	for (screenCounter = 0; screenCounter < 150; ++ screenCounter )
	{
		if (screenScanX == 15)
		{
			screenScanX = 0;
			++ screenScanY;			
		}
		if (screenScanY == 10)
		{
			screenScanY = 0;
			screenScanX = 0;
		}
		center = screenScanX + scrw * screenScanY;//ok
		
		{
			strcpy (str,"");
			
			itoa(screenScanY, yourScoreTXT, 10);
			strcat (str,yourScoreTXT);		
			strcat (str,":");
			
			itoa(screenScanX, yourScoreTXT, 10);
			strcat (str,yourScoreTXT);
			strcat (str,":");
			
			//itoa(tiles[center], yourScoreTXT, 10);
			itoa(grassfire[center], yourScoreTXT, 10);
			
			strcat (str,yourScoreTXT);
			strcat (str,":");
			
			PrintStr(str, 0x0101);
			
			Pause (30);
			
			strcat (str,"                   ");
		}
		++ screenScanX;//move over a column
	}
}
*/

void cleanTaxicab()
{
	center = 0;	
	screenScanX = 0;
	screenScanY = 0;
	
	//array is 150 slots big
	for (screenCounter = 0; screenCounter < 150; ++screenCounter)
		//for (screenCounter = 0; screenCounter < 150; screenCounter ++)
	{
		if (screenScanX == 15)
		{
			screenScanX = 0;
			++ screenScanY;			
		}
		if (screenScanY == 10)
		{
			screenScanY = 0;
			screenScanX = 0;
		}
		center = screenScanX + scrw * screenScanY;//ok		
		grassfire[center] = 0;		
		++ screenScanX;//last line
	}		
}


void TaxicabDifference()
{
	center = 0;	
	screenScanX = 0;
	screenScanY = 0;
	screenCounter = 0;
	
	//array is 150 slots big
	for (screenCounter = 0; screenCounter < 150; ++screenCounter)
	{
		if (screenScanX == 15)
		{
			screenScanX = 0;
			++ screenScanY;			
		}
		if (screenScanY == 10)
		{
			screenScanY = 0;
			screenScanX = 0;
		}
		
		center = screenScanX + scrw * screenScanY;//array index
		
		attribute = tiles[center];
		
		differenceX = abs(playerCharX - screenScanX);
		differenceY = abs(playerCharY - screenScanY);
		
		if (attribute > 15)
		{
			difference = 255;
		}
		else
		{
			//if no obsticle calculate taxicab distance
			difference = differenceX + differenceY;
		}
		
		grassfire[center] = difference;//note removed high offset

		++ screenScanX ;//last line
	}
}


void continousGrassFire()
{
	grassfire[playerCharX + scrw * playerCharY] = 1;	
	screenCounterEnd = screenCounterStart + scrw;//scan an entire line
	//screenCounterEnd = screenCounterStart + 5;//scans 5 character blocks  faster
	
	//for(screenCounter = screenCounterStart; screenCounter < screenCounterEnd; screenCounter++)
	for(screenCounter = screenCounterStart; screenCounter < screenCounterEnd; ++screenCounter)
	{
		//so we do not go out of bounds of the array
		{
			//makes sure the array is properly traveresed
			if(screenScanX == scrw)
			{
				screenScanX = 0;//set to first column
				++ screenScanY;//move down a row
			}
			if(screenScanY == scrh)
			{
				screenScanY = 0;//set to first row
				screenScanX = 0;//set to first column
			}
			if (screenCounterEnd > 150)
			{
				screenCounterStart = 0;
				screenCounter = 0;
				screenCounterEnd = 0;
			}
		}//makes sure the array is properly traveresed
		
		center = screenScanX + scrw * screenScanY;
		north = screenScanX + scrw * (screenScanY - 1);
		south = screenScanX + scrw * (screenScanY + 1);
		east = screenScanX + 1 + scrw * screenScanY;
		west = screenScanX - 1 + scrw * screenScanY;
			
		// the idea is to see if there are any numbers in the north, south, east or west 
		// of the center of the kernel other than 255
		// if there are are any numbers in the north, south, east or west 
		// then find the smallest of the number(s) of the kernel, add 1 and place it in the center.
			
		centerValue = grassfire[center];
		
		//refresh the barriers to make sure they stay intact
		if (tiles[center] > 15)
		{
			grassfire[center] = 255;
		}
		else
		//not a barrier
		if (centerValue != 255)
		{
			// if the kernel edge is out of range of the array
			// assign a high value so, it will not be taken into account
			
			if (screenScanY < 1)//control borders of array
				northValue = 255;
				else//read array value
					northValue = grassfire[north];
			
			if (screenScanX < 1)//control borders of array
				westValue = 255;
				else//read array value
					westValue = grassfire[west];

			if (screenScanY > (scrh - 2))//control borders of array
				southValue = 255;
				else//read array value
					southValue = grassfire[south];

			if (screenScanX > scrw - 2)//control borders of array
				eastValue = 255;
				else//read array value
					eastValue = grassfire[east];
			
			compare1 = min(northValue, southValue);
			compare2 = min(eastValue, westValue);
			compare3 = min(compare1, compare2);
			
			/*(northValue) < (southValue) ? (compare1 = northValue):(compare1 = southValue);
			(eastValue) < (westValue) ? (compare2 = eastValue):(compare2 = westValue);
			(compare1) < (compare2) ? (compare3 = compare1):(compare3 = compare2);*/

			//here is where the central tile is assigned a value
			if (centerValue != 1)
			{
				centerValue = compare3 + 1;
			}
			else
			{
				centerValue = 1;
			}
				
			grassfire[center] = centerValue;
		}//end center value not 255
		
		++ screenScanX;		
		screenCounterStart += screenCounterEnd;
	}//end arrayCounter look	
}

void enemyCollision()
{
	xx1 = enemyX + 10;//xx1 = enemyXX + 14;
	xx2 = enemyX - 10;//xx2 = enemyXX - 14;
	yy1 = enemyY + 10;//yy1 = enemyYY + 14;
	yy2 = enemyY - 10;//yy2 = enemyYY - 14;

	//collision with enemy
	if ((playerXpos < xx1) && (playerXpos > xx2) && (playerYpos < yy1) && (playerYpos > yy2))
	{
		playerDeath();
	}
}

/*void enemyCollision(unsigned char enemyXX, unsigned char enemyYY)
{
	xx1 = enemyXX + 10;//xx1 = enemyXX + 14;
	xx2 = enemyXX - 10;//xx2 = enemyXX - 14;
	yy1 = enemyYY + 10;//yy1 = enemyYY + 14;
	yy2 = enemyYY - 10;//yy2 = enemyYY - 14;

	//collision with enemy
	if ((playerXpos < xx1) && (playerXpos > xx2) && (playerYpos < yy1) && (playerYpos > yy2))
	{
		playerDeath();
	}
}*/

//ATTENTION
//center of tile = (half_tileSize + (tileSize * tileNumber))
//ATTENTION
void moveEnemy(unsigned char enemyXX, unsigned char enemyYY, unsigned char enemyFF)
{
	//unsigned char border;
	enemySteps = enemyFF << 4;//shift left 4 places	
	enemySteps = enemySteps >> 4;
	enemyDirection = enemyFF << 1;
	enemyDirection = enemyDirection >> 5;
	enemyRetreat = enemyFF >> 7;
	
	//playerX pixel range 0 - 240
	//playerY pixel range 0 - 160
	//enemyX & enemyXX pixel range 0 - 240
	//enemyY & enemyYY pixel range 0 - 160	
	//screen is 15 tiles wide and 10 tiles high
	
	//adjust enemy to character placement from pixel placement
	enemyCharX = enemyXX >> 4;//enemyCharX character range 0 - 15
	enemyCharY = enemyYY >> 4;//enemyCharY character range 0 - 9
	
	//ATTENTION	
	//CenterofTile = (half_tileSize + (tileSize * tileNumber))	
	xCenterofTile = (8 + (enemyCharX << 4));
	//	xCenterofTile = (8 + (16 * enemyCharX));
	yCenterofTile = (8 + (enemyCharY << 4));
	//	yCenterofTile = (8 + (16 * enemyCharY));
	//ATTENTION		
	
	center = enemyCharX + scrw * enemyCharY;
	north = enemyCharX + scrw * (enemyCharY - 1);
	south = enemyCharX + scrw * (enemyCharY + 1);
	east = enemyCharX + 1 + scrw * enemyCharY;
	west = enemyCharX - 1 + scrw * enemyCharY;	
		
	//try to keep the enemies from going into barriers
	if (tiles[north] > 15)
	{
		grassfire[north] = 255;
	}
	if (tiles[south] > 15)
	{
		grassfire[south] = 255;
	}
	if (tiles[east] > 15)
	{
		grassfire[east] = 255;
	}
	if (tiles[west] > 15)
	{
		grassfire[west] = 255;
	}
	
	//printtester5(playerXpos,playerYpos);
	//printtester5(playerCharX,playerCharY);	
	//printtester5(enemyXX,enemyYY);
	//printtester5(enemyCharX,enemyCharY);
	//printtester1(center);
	//printtester3(xCenterofTile,yCenterofTile);	
	//Pause (20);
	
	
	
	//if the enemy is in the center of the tile, need to look which direction we need to travel
	if ((enemyXX == xCenterofTile) && (enemyYY == yCenterofTile))
	{		
		centerValue = grassfire[center];
		northValue = grassfire[north];
		southValue = grassfire[south];
		eastValue = grassfire[east];
		westValue = grassfire[west];
		
		//decide which way the enemy should travel
		if ((northValue < southValue) && (northValue < eastValue) && (northValue < westValue))
		{
			//go north
			enemyDirection = 1;
		}
		else
		if ((southValue < northValue) && (southValue < eastValue) && (southValue < westValue))
		{
			//go south
			enemyDirection = 2;
		}
		else
		if ((eastValue < northValue) && (eastValue < southValue) && (eastValue < westValue))
		{
			//go east
			enemyDirection = 3;
		}		
		else
		if ((westValue < northValue) && (westValue < southValue) && (westValue < eastValue))
		{
			//go west
			enemyDirection = 4;
		}		
		else
		if (centerValue == 1)
		{
			// STOP, found the target
			enemyDirection = 5;
		}
		//decide which way the enemy should travel		
	}//end decisions
	

	//keep enemies from going past border
	//need hard numbers
	{
		if (enemyY > 152)
		{
			-- enemyY;
			enemyDirection = 1;//need to go north
		}
		if (enemyY < 8)
		{
			++enemyY;
			enemyDirection = 2;//need to go south
		}
		if (enemyX < 8)
		{
			++ enemyX;
			enemyDirection = 3;//need to go east
		}
		if (enemyX > 232)
		{
			-- enemyX;
			enemyDirection = 4;//need to go west
		}
	}
	
	switch(enemyDirection)
	{
		case 1:
			-- enemyY;
			break;
			
		case 2:
			++ enemyY;
			break;
			
		case 3:
			++ enemyX;
			break;
			
		case 4:
			-- enemyX;
			break;
		
		case 5:
			break;
	}
	
	
	// reduce clustering
	grassfire[center] += 16;
	//to help with clustering
	
	//enhancement
	//collision for enemies
	//transport to another area of the screen
	//if an enemy touches a barrier, transport it to a starting position
	if (tiles[center] > 15)
	{
		sprites[i].n += 128;
		//place sound effect here	  
		transportEnemy();
	}
		
	enemyDirection = enemyDirection << 4;
	enemyRetreat = enemyRetreat << 7;
	enemyF = enemySteps | enemyDirection | enemyRetreat;	
}

#endif