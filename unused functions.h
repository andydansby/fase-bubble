void obsticleCollision (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[])
{	
	//these are going to be hard numbers
	//in the shapes of the boxes that surround
	//the obstacle.	
	short xx1,xx2,yy1,yy2;
	short iterator;
	

	if (level == 0)
	{
		//array is edges of rectangles
		//based on character position 16x16		
		//red square
		x1[0] = 4;
		y1[0] = 4;
		//moon
		x1[2] = 13;
		y1[2] = 8;
		
		x1[90] = 99;
	}	
	
	for (iterator = 0; iterator < 50; iterator++)
	{
		xx1 = (x1[iterator]<<4) -24;
		xx2 = (x1[iterator]<<4) + 8;
		yy1 = (y1[iterator]<<4) -24;
		yy2 = (y1[iterator]<<4) + 8;		
		
		if (playerX > xx1 && playerX < xx2 && playerY > yy1 && playerY < yy2)
		{
			zx_border(6);
		}
		if (playerX > 186 && playerX < 215 && playerY > 9 && playerY < 39)
		{
			zx_border(6);
			x = 0x3000;
			y = 0x1000;
		}
		if (x1[iterator] == 99)
			break;
	}
	
	xx = playerX;//xx = playerX >> 4;
	yy = playerY;//yy = playerY >> 4;
	//printtester2(xx,yy);
		// tmpx= sprites[i].x>>4;
		// tmpy= sprites[i].y>>4;	
		
	//printtester2(xx,yy);
}


void attributeCollision (unsigned char playerX, unsigned char playerY)
{

	unsigned char xxxx;
	unsigned char yyyy;	
	unsigned char *address;
	unsigned char color;
	
/*
		char *ptr;
		char ch;
		ptr = (char *) 0x4711; // address to be peeked 
		c  = *ptr;
*/
	
	xxxx = playerX >> 3;//0 to 30
	yyyy = playerY >> 3;//0 to 20
	
	
	
	
	//address = zx_pxy2saddr(xxxx,yyyy,&mask) ;
	
	//*zx_cyx2saddr(uchar row, uchar col) __smallc;
	//cx    = character x coordinate (0..31)
	//cy    = character y coordinate (0..23)
	//cxy   = character (x,y) coordinate
	//uchar *zx_cyx2aaddr(uchar row, uchar col)
	address = zx_cyx2aaddr(yyyy,xxxx);//row first then column
	//gets the address of the attribute block
	
	//color = peek_function((unsigned char *)address);
	
	//color = bpeek(address);
	
	//bpoke(address , 71);

	
	
	//address = zx_pxy2aaddr(xxxx,yyyy);

	
	
	//printtester2(xxxx,yyyy);
	//printtester4((short)address);
	//printtester1(color);
	
	
}


void pixelCollision (unsigned char playerX, unsigned char playerY)
{
	unsigned char *address;
	unsigned char mask = 0;
	unsigned char xxxx = playerX;
	unsigned char yyyy = playerY;
	
	
//	*address = *zx_pxy2saddr(xxxx,yyyy,&mask) ;	
/*
	unsigned char *address;
	unsigned char mask;
	   
	address = zx_pxy2saddr(x,y,&mask);
	*address |= mask;
	   
	*zx_saddr2aaddr(address) = attr;
*/	
	address = zx_pxy2saddr(xxxx,yyyy,&mask) ;
	
	//printtester2(playerX, playerY);
	//printtester1(*address & mask);
	
	
/*
		tiles[((sprites[i].y+3)>>4)*scrw+(sprites[i].x+3)>>4] ; left-up
		tiles[((sprites[i].y+3)>>4)*scrw+(sprites[i].x+13)>>4] ; right-up
		tiles[((sprites[i].y+13)>>4)*scrw+(sprites[i].x+3)>>4] ; left-down
		tiles[((sprites[i].y+13)>>4)*scrw+(sprites[i].x+13)>>4] ; right-down
*/

}


void tileBasedCollision (unsigned char playerX, unsigned char playerY)
{
	//this version you do not have to have a separate array
	//more memory friendly, but based on 16x16 tile space
	unsigned char attribute = 0;
	playerX = playerX >> 4;
	playerY = playerY >> 4;
	
	attribute = tiles[playerY * scrw + playerX];
	
	//tiles[y*scrw+x]
	//printtester1(attribute);
	//printtester2(playerX, playerY);
	
	if (attribute > 0)
	{
		//collision detected
		M_OUTP(0xfe, 4);//changes border color
	}	
}


void obsticleCollision2 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[])
{
	unsigned char iterator;
	//unsigned char xx1,xx2,yy1,yy2;
	//unsigned char obsticleX, obsticleY;
	//unsigned char attribute;
	
	//printtester2(playerX, playerY);
	
	for (iterator = 0; iterator < 90; iterator ++)
	{
		unsigned char obsticleX = x1[iterator];
		unsigned char obsticleY = y1[iterator];
		unsigned char attribute = tileAttribute[iterator];
		
		unsigned char xx1 = (obsticleX * 16) - 8;
		unsigned char xx2 = xx1 + 32;
		
		unsigned char yy1 = (obsticleY * 16) - 8;
		unsigned char yy2 = yy1 + 32;
		
		if ((playerX > xx1) && (playerX < xx2) && (playerY > yy1) && (playerY < yy2))
		{
			//we found a collision
			zx_border(6);
		}		
		if (attribute == 99) break;// break out of the loop earlier if we encounter 99
	}
}



