#ifndef COLLISION_H
#define COLLISION_H

void blockMinMax()
{
	//for clearing a block of tiles
	//especially key and gate tiles

	minRedrawX = min(gateX1,keyX);
	minRedrawY = min(gateY1,keyY);
	maxRedrawX = max(gateX1,keyX);
	maxRedrawY = max(gateY1,keyY);
}


void playerDeath()
{
	yourLives --;
	
	M_OUTP(0xfe, 5);//changes border color
	//place sound effect here		 
	
	clearScreen();
	
	bullets[0].x = bullets[0].y = 1;
	// animation squeance
	// sound effect
	// pause
	
	//debug = true;
	
	// setup screen
	isLevelRead = false;
}

void warpLevel()
{
	runOnce = true;//only happens once per level
	isLevelRead = false;
	
	//debug = true;
	
	if (mapx > 15)
		mapx ++;
	else
		mapx = 0;
	
	level ++;
	gameMap ++;
	//bullets[0].x = bullets[0].y = 1;							 
}

void warpScreen()
{
	xx1 = (warpX << 4) + 8;
	yy1 = (warpY << 4) + 8;
	
	sprites[0].n = 129;	
	
	sprites[0].x = tmpx1;
	sprites[0].y = tmpy1;
	playerXpos = tmpy1;
	playerYpos = tmpy1;
	playerCharX = warpX;
	playerCharY = warpY;
	//place sound effect here

	sprites[0].n = 0;
	
	x = xx1 << 8;
	y = yy1 << 8;
}

void collect1up()
{
	if ((oneUpCollected == false) && (oneUpDisplay == false))
	{
		tiles[oneUpY * scrw + oneUpX] = 14;//tile number for 1UP
	}
	if ((oneUpCollected == true) && (oneUpDisplay == false))
	{
		tiles[oneUpY * scrw + oneUpX] = 0;		
		oneUpCollected = true;
		oneUpDisplay = true;
		//game stops here when collected
		//Pause (0);
	}
	if (oneUpDisplay == true)
	{
		tiles[oneUpY * scrw + oneUpX] = 0;
		oneUpCollected = true;
		oneUpDisplay = true;
		tilepaint(oneUpX, oneUpY, oneUpX, oneUpY);
	}
	//maxRedrawX = compareX2;
	//maxRedrawY = compareY2;
	
	//place sound effect here		 
	yourLives ++;
}

void removeGate1()
{
	//gate at 1,7
	if (keyCollected == false)
	{
		tiles[gateX1 + scrw * gateY1] = 20;
	}
	//remove gate
	if (keyCollected == true)
	{
		tiles[gateX1 + scrw * gateY1] = 0;
	}
}


void collectKey()
{
	if (keyCollected == false)
	{
		//add key
		tiles[keyX + scrw * keyY] = 13;
		gateOpen = false;
	}
	if (keyCollected == true)
	{
		tiles[keyX + scrw * keyY] = 0;
		tiles[gateX1 + scrw * gateY1] = 0;
		gateOpen = true;
		keyCollected = true;
	}
	//tilepaint(keyX, keyY, keyX, keyY);
	
	blockMinMax();
	
	tilepaint(minRedrawX, minRedrawY, maxRedrawX, maxRedrawY);
	
	//removeGate1();
}


void tileCollision()
{
	tileType = 0;	
	//players sprite
	xx1 = (sprites[0].x - 6) >> 4;
	xx2 = (sprites[0].x + 5) >> 4;
	yy1 = (sprites[0].y - 6) >> 4;
	yy2 = (sprites[0].y + 5) >> 4;

	xx3 = sprites[0].x;
	yy3 = sprites[0].y;
	
	xx4 = sprites[0].x >> 4;
	yy4 = sprites[0].y >> 4;	
	//tileType = tiles[xx4 + scrw * yy4];
		
	if (tiles[xx1 + scrw * yy1] > 0)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx1 + scrw * yy1];
	}
	if (tiles[xx2 + scrw * yy1] > 0)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx2 + scrw * yy1];
	}
	if (tiles[xx1 + scrw * yy2] > 0)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx1 + scrw * yy2];
	}
	if (tiles[xx2 + scrw * yy2] > 0)
	{
		//M_OUTP(0xfe, 3);
		tileType = tiles[xx2 + scrw * yy2];
	}

	switch(tileType)
	{
		//do nothing
		case 0://empty square
		{
			break;
		}
		case 1://bottom edge
		{
			break;
		}
		case 2://top edge
		{
			break;
		}
		case 3://left edge
		{
			break;
		}
		case 4://right edge
		{
			break;
		}
		case 5://left top corner
		{
			break;
		}
		case 6://right top corner
		{
			break;
		}
		case 7://left bottom corner
		{
			break;
		}
		case 8://right bottom corner
			break;
		
		case 9://warp
		{
			warpLevel();
			break;
		}
		
		case 10://warp destination
			//do nothing
			break;
		
		case 11://in screen warp
			warpScreen();
			break;
			
		case 12://in screen warp
			warpScreen();
			break;
		
		case 13://key
		{
			keyCollected = true;
			collectKey();			
			break;
		}
		
		case 14://1UP		
			oneUpCollected = true;
			collect1up();
			break;
		
		case 15://enemy launcher / deadly
		{
			playerDeath();
			break;
		}
		case 16://red diamond obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 17://yellow diamond obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 18://yellow spikes obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 19://red spikes obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 20://gate obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 21://gate obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		case 22://gate obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		
		case 23://gate obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}
		
		case 24://gate obsticle
		{
			M_OUTP(0xfe, 6);
			//playerDeath();
			break;
		}

		//removeGate1();
			
	}
	

}


//Check vertical border / edges
//void verticalEdge ();
void verticalEdge ()
{
	//mapx is char
	//mapy is char

	vy += ay;
	y += vy;
	
	if( vy + 8 >> 3 )
	{
		ay = -vy >> 3;
	}
	else
	{
		ay = vy = 0;
	}

	if( (unsigned int)y > scrh << 12 )
	{
		if( vy > 0 )
		{
			if( mapy < maph - 1 )
			{
				y = scrh << 12;
				vy= 0;
				playerDeath();//zx_border(3);
			}
		}

		//screen top
		if( vy < 0 )
		{
			if( mapy < 8)
			{
				y = 0;
				playerDeath();//zx_border(3);
			}
		}

		//screen bottom
		if( vy > scrh)
		{
			y = scrh << 4;
			playerDeath();//zx_border(3);
		}
	}
}

//Check horizontal border / edges
//void horizontalEdge ();
void horizontalEdge ()
{
	//mapx is char
	//mapy is char

	vx += ax;
	x += vx;

	if( vx + 8 >> 3 )
	{
		ax = -vx >> 3;
	}
	else
	{
		ax = vx = 0;
	}

	if( (unsigned int)x > scrw << 12 )
	{
		if( vx > 0 )
		{
			if( mapx < mapw - 2 )
			{
				x = scrw << 12;
			}
		}

		//screen left
		if( vx < 0 )
		{
			if( mapx < 16)
			{
				x = 24;
				playerDeath();//zx_border(3);
			}
		}

		//screen right
		if( vx > scrw)
		{
			x = scrw << 12;;
			playerDeath();//zx_border(3);
		}
	}
}


#endif