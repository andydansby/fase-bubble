#include <stdio.h>//being used to convert ints to strings
#include <stdlib.h>//standard library
#include  "fase.h"//our sprite library
#include "spectrum.h"//spectrum related utilities
#include "screenutils.h"
#include <variables.h>
//also wpoke
//#include <math.h>


#define gettile(x,y) tiles[x + (y << 4) - y ]
//static unsigned char jz,jsr=5;
//#define SHR3 (jz=jsr, jsr^=(jsr<<7), jsr^=(jsr>>5), jsr^=(jsr<<3),jz+jsr)


//255 will go to 32640

//<< left shift 7 bits
//>> right shift 5 bits
//<< left shift 3 bits

#define SHR3 (jz=jsr, jsr^=(jsr<<7), jsr^=(jsr>>5), jsr^=(jsr<<3),jz+jsr)





#define gconst  20
#define maxvx   600
#define maxvy   600


////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////
//     moved to variables.h       //
////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////

//vx velocity_X ?



// ****** DEFINE FUNCTIONS, BUT PLACE THEM AT BOTTOM
void update_scoreboard();

void remove_bullet(char k);

//void update_tilecode();

void update_screen();

void verticalEdge ();

void horizontalEdge ();

void enemyStart(short level);

void moveMainCharacter(unsigned char movePlayer);

void startingPosition (short levelPositioning[]);

void obsticleCollision3 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[]);

void obsticleCollision4 (unsigned char playerX, unsigned char playerY, unsigned char level, unsigned char x1[], unsigned char y1[]);

void readScreenTiles (unsigned char x1[], unsigned char y1[], unsigned char tileAttribute[]);

/*
unsigned int RND(unsigned int range) {
   return (unsigned int)(((long)(range) * rand()) / (long)(RAND_MAX));
}*/
//this causes crashs





// ****** DEFINE FUNCTIONS, BUT PLACE THEM AT BOTTOM


// ****** FUNCTIONS STILL WORKING ON

/*void random(unsigned char seedNumber[], unsigned char max)
{
	//look at system clock
	//using the frame as the seed
	unsigned char out;
	unsigned char seed;
	seed = bpeek (23672);
	
	seed ^= (seed << 3);
	seed ^= (seed >> 2);
	seed ^= (seed << 1);
	
	out = seed % max;
	
	seedNumber[0] = out;
	
	//return seedNumber;
}*/




//remember that this is called once for every enemy
//artificial stupidity 2
void enemyAI(unsigned char enemyData[], unsigned char playerX, unsigned char playerY)
{
	unsigned char enemyX,enemyY,enemyF,enemyImage,enemyStatus;
	unsigned short decision;
	unsigned char range;
	unsigned char randombit2;
	
	range = 4;//hard number to say our randomize is from 0 to 4
	
	//artificial stupidity 2
	enemyX = enemyData[0];
	enemyY = enemyData[1];
	enemyImage = enemyData[2];
	enemyF = enemyData[3];
	enemyStatus = enemyData[4];
	
	decision = SHR3 %4;//our random number from the macro
	//255 will max out to 32640
	// 5 which is what we are using in this case will max out to 640
	
	//<< left shift 7 bits
	//>> right shift 5 bits
	//<< left shift 3 bits


	//printtester1(decision);// comment this when not testing	
	//Pause(4);

	
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

// ****** FUNCTIONS STILL WORKING ON



main()
{
   
	start:
	{//at the start of a game
		Sound(LOAD, 0);
                
			//is the game 128k
			/*if( *is128 )
			{
				EI;
				*intadr= IsrSound;
			}*/
			
			
	}
  
	while (1)//main menu
	{		
		i= inp(0xf7fe) & 0x1f;
		
		if( i==0x1e )//press 1, select kempston joystick
		{
			Input= Joystick;
			//kempston joystick
			//zx interface 2, port 1
			break;
		}
		
		else if( i==0x1d )//press 2, select cursor joystick
		{
			Input= Cursors;
			//cursor joystick
			break;
		}
		
		else if( i==0x1b )//press 3, select keyboard control
		{
			Input= Keyboard;
			//QAOP space
			break;
		}
		
		else if( i==0x17 )//press 4 redefine keys
		{
			Redefine();
		}
	}
    
	DI;
	
	//initialize variables
	killed = 0;
	mapx = 0;
	mapy = 0;
	spacepressed = 0;
	num_bullets = 0;
	level = 0;
	buildMap = 0;
	*shadow= 0;	
	
	movePlayer = 0;
	
	//artificial stupidity part 2
	enemyData[0] = 0;
	enemyData[1] = 0;
	enemyData[2] = 0;
	enemyData[3] = 0;
	enemyData[4] = 0;
	
	
	//clear array on startup
	for (iterator = 0; iterator < 40; iterator++)
	{
		x1[iterator] = 0;
		y1[iterator] = 0;
	}
        
	//initialize variables
	isLevelRead = 0;//used to read level into array
	
	update_scoreboard();

	// initialize engine
	INIT;
	Sound(LOAD, 1);

	// pass data to sprites and bullets
	for ( i = 0; i < 5; i++ )
	{
		sprites[i].n = data[0 | i<<2],
		sprites[i].x = data[1 | i<<2],
		sprites[i].y = data[2 | i<<2],
		sprites[i].f = data[3 | i<<2];
		
		//reset all to 0 which is chase mode
		
		//sprites[i].x && sprites[i].y == direction of sprites
		//sprites[i].n == The .n is the number of the sprite (will draw a different sprite if changed
		//the .f has no effect on the engine, but it's used by the demo to store the direction of movement (it's diagonal movement so only 4 directions).
	}

	for ( i = 0; i < 4; i++ )
	{
		bullets[i].y = 255;
	}
  
	// display the first screen at the beginning and marker
	*screen= 0;
	
	while(1)//game loop
	{
		// this causes the engine to process a frame generating the scenario		
		FRAME;// we seem to have to refresh again when we read the tiles
		   M_OUTP(0xfe, 2);//changes border color	//M_OUTP(0xfe, 0);
		   
		   
		//we need to read level into array
		if (isLevelRead == 0)
		{
			FRAME;// we force update screen to be able to catch the tile-set for the attributes
			
			
			readScreenTiles(x1,y1,tileAttribute);
			//now that we have read our tiles, we need to select our starting level
			
			levelPositioning[2] = ((short)level);//recast level to fit properly in array 
			startingPosition((short)levelPositioning);
			x = levelPositioning[0];
			y = levelPositioning[1];
				
			enemyStart(level);
		
			isLevelRead = 1;//level has now been read
				
			enemySlowDown = 0;
			enemySpeedUp --;//lower is faster
			if (enemySpeedUp < 0) enemySpeedUp = 0;
			
			//artificial stupidity part 2
			//unsigned char enemyData{4} = {0,0,0,0};//used to send enemy AI to function
			
			romCounter = 0;//randomize function
		}
			
			//note WHEN LEVEL IS COMPLETE, WE WILL NEED TO READ THE LEVEL INTO THE ARRAY
			//I.E. /*if (isLevelComplete){	isLevelRead = 0;do something}*/

			//printtester3(x,y);//this crashes game on game over
			
		// movement of enemy sprites
		for ( i = 1; i < 5; i++ )
		{
			if( sprites[i].n < 128 )
			//if( sprites[i].n < 128 )//if( sprites[i].n < 0x80 )
			{
				for ( j= 0; j < num_bullets; j++ )//cycle through all of the bullets
				{
					
					//does your bullet hit a baddie, 10 is an offset from center of baddie sprite
					if( abs(bullets[j].x-sprites[i].x) + abs(bullets[j].y-sprites[i].y) < 10)
					{
						//sprites[i].n += 128;//sprites[i].n += 0x80;
						remove_bullet(j);
						
						tmpx = sprites[i].x>>4;
						tmpy = sprites[i].y>>4;
						
						//artificial stupidity part 2
						//unsigned char enemyData{4} = {0,0,0,0};//used to send enemy AI to function
						
						enemyData[4] = 1;//indicates run away
						
						//start a timer for each sprite hit, timer should start at 5 seconds initially
						
						
						
						//tiles[tmpy * scrw + tmpx]= 66;//where enemy dies??
						//tilepaint(tmpx, tmpy, tmpx, tmpy);
						
						Sound(EFFX, 1+killed++%5);				
						*drwout= (unsigned int)update_scoreboard;
					}
				}
				
				// to be added for artificial stupidity
				{
					enemyData[0] = sprites[i].x;
					enemyData[1] = sprites[i].y;
					enemyData[2] = sprites[i].n;
					enemyData[3] = sprites[i].f;

					
					//artificial stupidity 2
					enemyAI(enemyData, playerXpos, playerYpos);
					
					
					//artificial stupidity 2
					sprites[i].x = enemyData[0];
					sprites[i].y = enemyData[1];
					sprites[i].n = enemyData[2];
					sprites[i].f = enemyData[3];

					//tester for just 1 sprite
					enemyData[0] = sprites[1].x;
					enemyData[1] = sprites[1].y;
					enemyData[2] = sprites[1].n;
					enemyData[3] = sprites[1].f;
					
					//artificial stupidity 2
					sprites[1].x = enemyData[0];
					sprites[1].y = enemyData[1];
					sprites[1].n = enemyData[2];
					sprites[1].f = enemyData[3];

				}
				
				
				
				
				
				//sprites[i].x && sprites[i].y == direction of sprites
				//sprites[i].n == The .n is the number of the sprite 
				//(will draw a different sprite if changed
				//the .f has no effect on the engine, but it's used by 
				//the demo to store the direction of movement 
				//(it's diagonal movement so only 4 directions).
				
				
				
				if (enemySlowDown == 0)
				{
					enemySlowDown = 0;
				}
				enemySlowDown ++;
				if (enemySlowDown == enemySpeedUp) enemySlowDown = 0;
				
				//eventually enemySpeedUp will count down with each new level 
				// to be added for artificial stupidity
				
			}
		}
		
		//game over check
		if( killed == 2 ) //end game
		{
			Sound(STOP, 0);

			
			EXIT;
			//	Bitmap(1, 0)
			//	Pause(50);
			//	Bitmap(3, 1);
			//	Pause(50);
			//	Bitmap(2, 1);//this is ok
			//	Pause(50);
			//	Bitmap(0, 0);//crashes game. why??						
			Pause(50);
			Bitmap(2, 0);							
			buildMap = 0;			
			isLevelRead = 0;//reset flag to re read level
				goto start;
		}
		

		// movement of bullets
		for ( i = 0; i < num_bullets; i++ )
		{
			if( dirbul[i]&3 )
			{
				if( dirbul[i]&1 )
				{
					if( bullets[i].x < scrw * 16 )
						bullets[i].x += 4;
					else
						remove_bullet(i);
				}				
				else
				{
					if( bullets[i].x > 4 )
						bullets[i].x -= 4;
					else
						remove_bullet(i);
				}
			}
			
			if( dirbul[i]&12 )
			{
				if( dirbul[i]&4 )
				{
					if( bullets[i].y<scrh*16 )
						bullets[i].y+= 4;
					else
					remove_bullet(i);
				}
				else
				{
					if( bullets[i].y>4 )
						bullets[i].y-= 4;
					else
						remove_bullet(i);
				}
			}
		}
	
		//check edges
		{
			//vertical edge
			verticalEdge();
			
			//horizontal edge
			horizontalEdge();
			
			//bob = (unsigned char)(x >> 8);//(char)(x >> 12);//x >> 8
			//bob = (unsigned char)(y >> 8);
			//printtester(bob);
			//here X>>8 is from 0 to 240
			//here Y>>8 is from 0 to 159
			//here Y>>9 is from 0 to 207
			
			
			
			
			
			playerXpos = (unsigned char)(x >> 8);
			playerYpos = (unsigned char)(y >> 8);
			//playerXattr = (unsigned char)(playerXpos >> 4);
			//playerYattr = (unsigned char)(playerYpos >> 4);
			
			
			//printtester2(playerXattr,playerYattr);
			//printtester2(bob,sue);
			
		//	obsticleCollision(playerXpos,playerYpos,level,x1,y1);
		//	obsticleCollision3(playerXpos,playerYpos,level,x1,y1);
		//	obsticleCollision4(playerXpos,playerYpos,level,x1,y1);
		//	maskCollision();

		
		}
		
		sprites[0].x = x >> 8;
		sprites[0].y = y >> 8;

		
		//directional movement of the character
		{
			movePlayer ++;
			if (movePlayer > 16) movePlayer = 0;
			moveMainCharacter(movePlayer);			
		}

	
	}
	
}//end of game loop




//Check vertical border / edges
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

void readScreenTiles (unsigned char x1[], unsigned char y1[], unsigned char tileAttribute[])
{
	count = 0;
	tile = 0;
	attribute = 0;
	
	//FRAME;// we force update screen to be able to catch the tile-set for the attributes
	// as per Antonio, tile array is unsigned char.
	//scrw - screen width is constant
	//unsigned char *tiles= 0x5b40;
	//only called when isLevelRead == 0
	
	//clear out array from prior level
	//have no more than 89 objects
	//make everything 99, this is a trigger to stop
	//scanning the tiles array to speed up
	//collision detection
	for (tile = 0; tile < 40; tile++)
	{
		x1[tile] = 99;
		y1[tile] = 99;
		tileAttribute[tile] = 99;
	}
	
	//now test to make sure all are 99
	//good
	/*
	for (tile = 0; tile < 40; tile++)
	{
		screenX = x1[tile];
		screenY = y1[tile];
		attribute = tileAttribute[tile];
		
		FRAME;
		printtester2(tile, attribute);	
		zx_border(2);
		Pause (10);
	}*/
	count = 0;
	tile = 0;
	attribute = 0;
	
	
	//screenX 0 to 15
	//screenY 0 to 9
	for ( screenY = 0; screenY < 10; screenY++)
	{
		for (screenX = 0; screenX < 16; screenX++)
		{
			attribute = tiles[screenY * scrw + screenX];

			//if (checking the tile <> 0)
			//tile 0 is a blank tile to travel
		
			//good
			/*printtester1(attribute);
			printtester2(screenX, screenY);			
			FRAME;// we force update screen to be able to catch the tile-set for the attributes
			zx_border(0);
			Pause(15);*/
			
			
			if ((attribute > 0) && (attribute < 99))
			{
				//mark the x & y position and place it 
				//in the array
				//this is where the problem lies
				//writing to array x1
				// check to make sure less than 99 as well
				
				x1[count] = screenX;
				y1[count] = screenY;				
				tileAttribute[count] = attribute;
				
				count++;//increment the counter for the next slot in array
			}
		}
	}	
	//now lets print back our values
	
	/*for (tile = 0; tile < 40; tile ++)
	{
		screenX = x1[tile];
		screenY = y1[tile];
		attribute = tileAttribute[tile];
		printtester1(attribute);
		printtester2(screenX, screenY);			
		FRAME;// we force update screen to be able to catch the tile-set for the attributes
		Pause (100);
		
		if (attribute == 99) break;// break out of the loop earlier if we encounter 99
	}*/
}



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


void startingPosition (short levelPositioning[])
{
	short xxx = 0;// = levelPositioning[0];// to be used for output
	short yyy = 0;// = levelPositioning[1];
	short Level = levelPositioning[2];

	if (Level == 0)
	{
		//xxx = 50;
		//yyy = 120;//yyy = 16;
		//xxx = 200;
		//yyy = 24;//yyy = 16;
		
		xxx = 200;
		yyy = 55;
	}
	
	//to adjust to scale.
	xxx = xxx * 256;
	yyy = yyy * 256;
	
	//returns
	levelPositioning[0] = xxx;
	levelPositioning[1] = yyy;	
}


void enemyStart(short level)
{
	short Level = level;
	
	if (Level == 0)
	{
		//enemy 1 - 8, 8, 8, 3
		data[4] = 8;//n 
		data[5] = 16;//x position
		data[6] = 16;//y position
		data[7] = 2;//sprite number
		
		//enemy 2 - 9, 230, 8, 3		
		data[8] = 16;
		data[9] = 224;//x position
		data[10] = 8;//y position
		data[11] = 3;//sprite number
		
		//enemy 3 - 10, 5, 150, 1		
		data[12] = 10;
		data[13] = 16;//x position
		data[14] = 140;//y position
		data[15] = 1;//sprite number
		
		//enemy 2 - 12, 230, 150, 2		
		data[16] = 12;
		data[17] = 224;//x position
		data[18] = 140;//y position
		data[19] = 2;//sprite number
		M_OUTP(0xfe, 1);//changes border color
	}
	
	//comes after the level data is set to initilize sprites
	for ( i = 0; i < 5; i++ )
	{
		sprites[i].n = data[0 | i<<2],
		sprites[i].x = data[1 | i<<2],
		sprites[i].y = data[2 | i<<2],
		sprites[i].f = data[3 | i<<2];
	}
}

void moveMainCharacter(unsigned char movePlayer)
{
	unsigned char spriteFrame;
	
	if (movePlayer > 8) spriteFrame = 1;
	if (movePlayer < 8) spriteFrame = 0;
	
	// motion of the protagonist
	if( Input() & 0x01 ) // P - go right
	{
		sprites[0].n = 0 + spriteFrame;//bubble orientation right 4th sprite over
		ax = vx < maxvx ? 40 : 0;
	}

	if( Input() & 0x02 ) // O - go left
	{	
		sprites[0].n = 2 + spriteFrame;//bubble orientation left 4th sprite over
		ax = vx > -maxvx ? -40 : 0;
	}

	//now we have down doing the same as up for testing
	if( Input() & 0x04 )// A go down
	{
		sprites[0].n = 4 + spriteFrame;//bubble orientation down 4th sprite over
		ay = (vy < maxvy) ? 40 : 1;
	}

	if( Input() & 0x08 )// Q go up
	{
		sprites[0].n = 6 + spriteFrame;//bubble orientation up 4th sprite over
		ay = (vy > -maxvy) ? -40 : -1;
	}

	if( Input() & 0x10 && !spacepressed && num_bullets<4 )
	{ // Space (FIRE)
		Sound(EFFX, 0);
		bullets[num_bullets].x= sprites[0].x;
		bullets[num_bullets].y= sprites[0].y;
		i= Input() & 0x0f;
		dirbul[num_bullets]= i ? i : 1;
		num_bullets++;
	}

	spacepressed= Input() & 0x10;
}


void remove_bullet(char k)
{
	//char k;
	
	//k = *k;
	
	if( num_bullets )
	{
		num_bullets --;

		while ( k < num_bullets )
		{
			dirbul[k] = dirbul[k + 1],
			bullets[k].x = bullets[k + 1].x;
			bullets[k].y = bullets[++k].y;
			//bullets[k].y = bullets[k + 1].y;
		}
		bullets[k].y = 255;
	}
}

void update_scoreboard()
{
	unsigned int scr, dst;
	char count;
	
	scr= 0x3d80+killed*8;
	
	//PrintStr("cadena", 321);
	dst= 0x403e|*shadow<<8;
	for ( count= 0; count<8; count++ )
	{
		zxmem[dst]= zxmem[scr++]^0xff,
		dst+= 0x100;
	}
}

void update_screen()
{
	*screen= mapy * mapw + mapx;
	
	for ( j= 1; j < 5; j++ )
	{
		if( sprites[j].n > 0x7f )
			sprites[j].n -= 0x80;
	}
}





eof