
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
				zx_border(6);
			}
		}

		//screen right
		if( vx > scrw)
		{
			x = scrw << 12;;
			zx_border(6);
		}
	}
}

//void obsticleCollision3 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[]);
//square detection
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


//circle detection
//void obsticleCollision4 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[]);
void obsticleCollision4 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[])
{
	objectRadius = 15;
	
	for (iterator = 0; iterator < 40; iterator ++)
	{
		screenX = x1[iterator];;//screenX stepping through obsticle array
		screenY = y1[iterator];;//screenY stepping through obsticle array
		attribute = tileAttribute[iterator];

		//center point of the tiles
		xx1 = (screenX * 16) + 8;
		yy1 = (screenY * 16) + 8;
	
		//differences between the objects
		differenceX = abs(playerX - xx1);
		differenceY = abs(playerY - yy1);
		
		//now square the objects
		squaredDifferenceX = differenceX * differenceX;
		squaredDifferenceY = differenceY * differenceY;
		
		//now square the radius
		//This could be done outside the loop as the radius don't change
		squaredRadius = objectRadius * objectRadius;
	
		//Pythagoras theorm
		if ( ( squaredDifferenceX ) + ( squaredDifferenceY ) < objectRadius * objectRadius )
		{
			zx_border(6);
			
			//force a break below as we have already found a collision
			//needs to be the last line in this if statement
			attribute = 99;
		}

		if (attribute == 99) break;// break out of the loop earlier if we encounter 99
	}	
}
