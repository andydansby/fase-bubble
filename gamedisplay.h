
#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#define max(x,y) (((x)>(y))?(x):(y))
#define min(x,y) (((x)<(y))?(x):(y))

#define printInk(k)			printf("\x10%c", (k))
#define printPaper(k)		printf("\x11%c", (k))
#define printMode(mode)		printf("\x01%c", (mode))
#define printAt(row, col)	printf("\x16%c%c", ' '+(row), ' '+(col))
#define FLASH_ON			printf("\x12\x31")
#define printCls()			printf("\x0c")
#define printInk(k)			printf("\x10%c", (k))
#define printPaper(k)		printf("\x11%c", (k))

//these must be public to pass onto _show_str
//int _g_number;
//short _g_str_x;
//short _g_str_y;
//unsigned char _g_mask;
//unsigned char *textString;
//unsigned char *ptr_tmp;
//these must be public to pass onto _show_str

/*
  this function can not have parameters since the engine, 
  only allows calling void / void functions
  so all those variables g_ must be prepared before entering.
  16384-22528 pixel data
*/

	void cls()
	{		
		zx_border(0);
		printPaper(0);
		printInk(2);
		printCls();
	}

	void z88dkPrint(unsigned char *string, unsigned char x, unsigned char y)
	{
		printMode(32);//how many columns
		printAt(x, y);
		printf(string);//printf("GAME OVER");
	}

void clearScreen()
{
	//clear the sprites
	for (screenCounter = 0; screenCounter < 5; ++ screenCounter )
	{
		sprites[screenCounter].n = 129;
	}
	
	for (screenScanY = 0; screenScanY < 10; ++ screenScanY)
	{
		for (screenScanX = 0; screenScanX < 15; ++ screenScanX)
		{
			tiles[screenScanY * scrw + screenScanX] = 0;
		}
	}
	//#define tilepaint(from_x, from_y, to_x, to_y)
	tilepaint(0, 0, 14, 9) | *shadow << 8;
	FRAME;
}

	void blockClear()
	{
		Bitmap(1, 0);
		Bitmap(1, 1);
		Bitmap(1, 2);
	}

	void insertionSort()
	{
		char hiTemp[4];
		
		i = 0;
		j = 0;
		
		for(i = 1; i < 6; ++i)
		{
			key = scores[i].hiScoreList;
			
			strcpy(hiTemp, scores[i].hiInitals);//copies the value of initials[i] to hiTemp
			j = i - 1;
			
			
			while( key > scores[j].hiScoreList && j >= 0)
			{
				//swap scores
				scores[j + 1].hiScoreList = scores[j].hiScoreList;
				
				//copy initials
				strcpy(scores[j + 1].hiInitals, scores[j].hiInitals);
				
				-- j;
			}
			
			scores[j + 1].hiScoreList = key;// place temp value in slot
			strcpy(scores[j + 1].hiInitals, hiTemp);
		}
	}
	
	void update_scoreboard()
	{
		ltoa(yourScore,yourScoreTXT , 10);//use lota for long variables
		//PrintStr(yourScoreTXT, 0x0701);
		PrintStr128(yourScoreTXT, 1,7);
		//PrintStr(scoreTxT, 0x0101);
		PrintStr128("Score", 1, 1);
		
		itoa(yourLives,yourLivesTXT , 10);
		PrintStr(yourLivesTXT, 0x1901);
		PrintStr(livesTxT, 0x1301);
	}


/*print_value
void print_value(unsigned char x, unsigned char y, int number)
{
    _g_str_x = x;
    _g_str_y = y;
    _g_mask = 1;

    //_itoa(number); // g_string saved in func
	itoa(number, yourLivesTXT, 10);
	textString = yourLivesTXT;

    // print with engine sync
    //if(fase_status == FASE_RUNNING)
    //    *drwout = (unsigned int) _show_str;
    //else
    //    _show_str();
}
*/




void update_screen()
{
	//*screen= mapy * mapw + mapx;
	
	*screen = gameMap;
	
	for ( j = 1; j < 5; ++j )
	{
		if( sprites[j].n > 0x7f )
			sprites[j].n -= 0x80;
	}
}

void displayStart()
{
	count = 30;	
	for (iterator = 0; iterator < 3; ++ iterator )
	{
		PrintStr(gameStartTXT, 0x1001);
		Pause (count);
		PrintStr(clearTXT, 0x1001);
		Pause (count);
		count = count - 10;
		
		//print_str(unsigned char x, unsigned char y, unsigned char mask, unsigned char *s)
		
		//beepfx(0);
		//FRAME;
		//Sound(EFFX, 6);
		//#asm 
		//ld hl,2 
		//#endasm		
	}
}


void printHighScores()
{
	screenCounter = 0;	
	insertionSort();
	
	//PrintStr128(highScoreText, 01, 01);
	//FRAME;
	//z88dkPrint(highScoreText, 9, 6);
	//z88dkPrint(highScoreText, 9, 6) | *shadow << 8;
	PrintStr128(highScoreText, 6, 9);	
	
	xx = 11;//xx = 0x0403;
	
	for (screenCounter = 0; screenCounter < 5; screenCounter++ )
	{
		strcpy (str," ");
		strcat (str,scores[screenCounter].hiInitals);	//Concatenate strings
		strcat (str,"....");
		
		ltoa(scores[screenCounter].hiScoreList, yourScoreTXT , 10);//use lota for long variables
		strcat (str,yourScoreTXT);
		
		PrintStr128(str, 9, xx);		
		xx ++;		
	}	
}

void highScore()
{
	letter = 65;//starting at the letter A
	arrayCounter = 0;

	if (speccy128k == true){
		//EXIT;
	}
	
	#asm
		ld hl,$5c01
		ld a,127
		ld (hl),a
		ld a,0
		ld (hl),a		
	#endasm
	
	PrintStr128("CONGRATULATIONS", 9, 5);
	PrintStr128("YOU HAVE A NEW HIGH SCORE", 4,7);
	
	PrintStr128("Enter your initals with", 2,17);// 
	PrintStr128("UP/Down/FIRE", 9,18);

//	firstInital = 65;//letter A
//	secondInital = 65;//letter A
//	thirdInital = 65;//letter A
		
/*	
	while (1)
	{
		//now we have down doing the same as up for testing
		if( Input() & 0x04 )// A go down
		{
			++ letter;
		}
		if( Input() & 0x08 )// Q go up
		{
			-- letter;			
		}
		if( Input() & 0x10) // Space (FIRE)
		{
			//Sound(EFFX, 0);
			//i= Input() & 0x0f;
			++ arrayCounter;
		}
		
		if (letter > 90) letter = 65;//if you go past Z, roll back to A
		if (letter < 65) letter = 90;//if you go past A, roll back to Z

		initials[arrayCounter] = letter;
		
		sprintf(buffer, "%c", letter);
		
		if (arrayCounter == 0)
		{
			z88dkPrint(buffer, 20,12);
			//firstInital = buffer;
		}		
		if (arrayCounter == 1)
		{
			z88dkPrint(buffer, 20,13);
			//secondInital = buffer;
		}		
		if (arrayCounter == 2)
		{
			z88dkPrint(buffer, 20,14);
			//thirdInital = buffer;
		}		
		if (arrayCounter == 3)
		{	break;}
		
		//FRAME;
		Pause (150);
	}
*/
	
	scores[5].hiInitals[0] = (initials[0]);
	scores[5].hiInitals[1] = (initials[1]);
	scores[5].hiInitals[2] = (initials[2]);
	scores[screenCounter].hiScoreList = yourScore;

	//sort high score table
	insertionSort();
	
	//print high score table
	//printHighScores();
}





//notes
//need to rewrite end game to only have 1 frame at the end

// special attention needs to be given during high score print
// and high score entry

//You must add shadow<<8 to the address before write because in 128K mode there is another screen between 0xc000 and 0xdaff. 
	//| *shadow << 8;
	//dst= 0x50de | *shadow << 8;
	//z88dkPrint("GAME OVER", 3,11);
	//z88dkPrint("GAME OVER", 3,11) | *shadow << 8;
// Game Over


void endgame()
{
	
	clearScreen();

	//check to see if your current score is a new high score
	if (yourScore > scores[4].hiScoreList)
	{
		//if (speccy128k == true){			
		//}
		highScore();
	}
	else
	{
		//FRAME;//only use one FRAME at the very end
		//PrintStr128("GAME OVER", 11, 3);
		//z88dkPrint("GAME OVER", 3,11);
		#asm
			ld hl,$5c01
			ld a,0
			ld (hl),a
		#endasm

		PrintStr128("Game Over", 11, 3);
		
	}
	
	printHighScores();
	
	FRAME;
	Pause (300);//Pause (120);
}




#endif
