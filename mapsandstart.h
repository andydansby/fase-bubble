//map and starting positions work

//void startingPosition (short levelPositioning[]);
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



//void readScreenTiles (unsigned char x1[], unsigned char y1[], unsigned char tileAttribute[]);
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



//void enemyStart(short level);
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
