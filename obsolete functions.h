void verticalEdge (short vertical[])
{
	//mapx is char
	//mapy is char
	//vertical[0] = vy;
	//vertical[1] = ay;
	//vertical[2] = y;
	
	short vY1 = vertical[0];//vY1 goes from -660 to 660	
	short aY1 = vertical[1];//aY1 goes from -60 to 60
	short YY1 = vertical[2];//YY1 goes from -30324 to 723959

	
	
	//printtester4(vY1);

	vY1 += aY1;
	YY1 += vY1;
	
	if( vY1 + 8 >> 3 )
	{
		aY1 = -vY1 >> 3;
	}
	else
	{
		aY1 = vY1 = 0;
	}

	if( (unsigned int)YY1 > scrh << 12 )
	{
		if( vY1 > 0 )
		{
			if( mapy < maph - 1 )
			{
				YY1 = scrh << 12;
				vY1= 0;
				zx_border(3);
			}
		}

		//top
		if( vY1 < 0 )
		{
			if( mapy < 8)
			{
				YY1 = 0;
				zx_border(3);
			}
		}

		//screen bottom
		if( vY1 > scrh)
		{
			YY1 = scrh << 4;
			zx_border(6);
		}
	}
	
	//returns
	vertical[0] = vY1;
	vertical[1] = aY1;
	vertical[2] = YY1;
}

//Check horizontal border / edges
void horizontalEdge (short horizonal[])
{
	//mapx is char
	//mapy is char
	//vertical[0] = vx;
	//vertical[1] = ax;
	//vertical[2] = x;

	short vX1 = horizonal[0];//vX1 goes from -637 to 604
	short aX1 = horizonal[1];//aX1 goes from -60 to 60
	short XX1 = horizonal[2];//XX1 goes from -30324 to 723959

	vX1 += aX1;
	XX1 += vX1;

	if( vX1 + 8 >> 3 )
	{
		aX1 = -vX1 >> 3;
	}
	else
	{
		aX1 = vX1 = 0;
	}

	if( (unsigned int)XX1 > scrw << 12 )
	{
		if( vX1 > 0 )
		{
			if( mapx < mapw - 2 )
			{
				XX1 = scrw << 12;
			}
		}

		//screen left
		if( vX1 < 0 )
		{
			if( mapx < 16)
			{
				XX1 = 24;
				zx_border(6);
			}
		}

		//screen right
		if( vX1 > scrw)
		{
			XX1 = scrw << 12;;
			zx_border(6);
		}
	}
	//returns
	horizonal[0] = vX1;
	horizonal[1] = aX1;
	horizonal[2] = XX1;	
}


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
				zx_border(3);
			}
		}

		//top
		if( vy < 0 )
		{
			if( mapy < 8)
			{
				y = 0;
				zx_border(3);
			}
		}

		//screen bottom
		if( vy > scrh)
		{
			y = scrh << 4;
			zx_border(6);
		}
	}
}

//square detection
void obsticleCollision3 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[])
{
	//playerX & playerY localized only
	//unsigned char xx1,yy1;
	//unsigned char obsticleX, obsticleY;
	//unsigned char attribute;
	//unsigned char differenceX,differenceY;
	//unsigned char iterator;	
	//unsigned char objectRadius;	

	objectRadius = 15;
	
	for (iterator = 0; iterator < 40; iterator ++)
	{
		screenX = x1[iterator];//obsticleX = x1[iterator];
		screenY = y1[iterator];//obsticleY = y1[iterator];
		attribute = tileAttribute[iterator];

		//center point of the tiles
		tmpx = (screenX * 16) + 8;
		tmpy = (screenY * 16) + 8;
		differenceX = abs(playerX - tmpx);
		differenceY = abs(playerY - tmpy);

		if ((differenceX < objectRadius) && (differenceY < objectRadius))
		{
			zx_border(6);
			break;
		}

		if (attribute == 99) break;// break out of the loop earlier if we encounter 99
	}
}


void obsticleCollision3 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[])
{
	objectRadius = 15;
	
	for (iterator = 0; iterator < 40; iterator ++)
	{
		screenX = x1[iterator];//screenX stepping through obsticle array
		screenY = y1[iterator];//screenY stepping through obsticle array
		attribute = tileAttribute[iterator];

		//center point of the tiles
		tmpx = (screenX * 16) + 8;
		tmpy = (screenY * 16) + 8;
		differenceX = abs(playerX - tmpx);
		differenceY = abs(playerY - tmpy);

		if ((differenceX < objectRadius) && (differenceY < objectRadius))
		{
			zx_border(6);
			break;
		}

		if (attribute == 99) break;// break out of the loop earlier if we encounter 99
	}
}
















