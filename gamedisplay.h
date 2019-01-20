
#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "gamedisplay1.h"



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



void printHighScores()
{
	screenCounter = 0;	
	insertionSort();
	
	PrintStr(highScoreText, 0x0609);// 9, 5
	
	//xx = 11;//xx = 0x0403;
	xx = 0x040b;
	
	for (screenCounter = 0; screenCounter < 5; screenCounter++ )
	{
		strcpy (str,"          ");
		strcat (str,scores[screenCounter].hiInitals);	//Concatenate strings
		strcat (str,"....");
		
		ltoa(scores[screenCounter].hiScoreList, yourScoreTXT , 10);//use lota for long variables
		strcat (str,yourScoreTXT);
		
		//PrintStr128(str, 9, xx);
		PrintStr(str, xx);
		
		xx ++;		
	}	
}


/*void _show_str(unsigned char *s, unsigned char g_str_y, unsigned char g_str_x)
{
    //unsigned char * s = g_string;

    // no fona para mayores de 8
    if( g_str_y < 9)
        dst= (g_str_y * 0x20 ) + g_str_x + 0x4000 | *shadow << 8;
    else
        dst= ((g_str_y - 9 ) * 0x20 ) + g_str_x + 0x5000 | *shadow << 8;

    
   while (*s)   {
       scr= 0x3c00 + *s++ * 8;
       
        for ( count= 0; count < 8; count++ )
        {
            zxmem[dst] = zxmem[scr++] ^ 0xff;
            dst+= 0x100;
        }

        dst-= 0x7ff;

    }
}*/

void printToMemory(unsigned char x, unsigned char y, unsigned char letter)
{
	*zxmem = 0;
	
	//0x3e08 = 15880 = letter A
	scr = 15872 + letter * 8;
	//dst = zx_cyx2saddr(y,x+i);
	
	if (speccy128k == true)
		dst = zx_cyx2saddr(y,x+i)|*shadow << 8;
	if (speccy128k == false)
		dst = zx_cyx2saddr(y,x+i);
	
	for ( count= 0; count < 8; count++ )
	{
		zxmem[dst] = zxmem[scr++]^0xff,
		dst+= 0x100;
	}
}

void highscoreEntry()
{
	unsigned char initial_1, initial_2, initial_3 = 65;
	arrayCounter = 0;
	letter = 1;//letter = 32; letter = 65;
	
	//while (1)
	while (arrayCounter < 3)
	{

		//letter tiles are 32 to 57
		//however sinclair ascii is from 65 to 90
		//if (letter > 90) letter = 65;//if you go past Z, roll back to A
		//if (letter < 65) letter = 90;//if you go past A, roll back to Z
		
		if (letter > 26) letter = 1;//if you go past Z, roll back to A
		if (letter < 1) letter = 26;//if you go past A, roll back to Z

		//initials[arrayCounter] = letter;
		//sprintf(buffer, "%c", letter);
		
		//tilepaint(0x0d, 0x0e, 0x0f, 0x0e);
		
		if (arrayCounter == 0)
		{
			initial_1 = letter;
			//PrintStr(&initial_1, 0x0D0E);
			//PrintStr(buffer, 0x0D0E);			
			//PrintStr((unsigned char*)initial_1, 0x0D0E);
			printToMemory(0x9, 0x0e, initial_1);

		}
		
		if (arrayCounter == 1)
		{
			initial_2 = letter;
			printToMemory(0x0A, 0x0e, initial_2);
		}
		
		if (arrayCounter == 2)
		{
			initial_3 = letter;
			printToMemory(0x0B, 0x0e, initial_3);
		}		
	
		if( Input() & 0x04 )// A go down
		{
			-- letter;
		}
		if( Input() & 0x08 )// Q go up
		{
			++ letter;			
		}
		if( Input() & 0x10) // Space (FIRE)
		{
			//Sound(EFFX, 0);
			//i= Input() & 0x0f;
			++ arrayCounter;
		}
		
		Pause (10);
		
		if (arrayCounter == 3)
		{	
			break;
		}
	}
	//scores[5].hiInitals[0] = (initials[0]);
	//scores[5].hiInitals[1] = (initials[1]);
	//scores[5].hiInitals[2] = (initials[2]);
	
	//scores[5].hiInitals[0] = initial_1;
	//scores[5].hiInitals[1] = initial_2;
	//scores[5].hiInitals[2] = initial_3;
	
	//+64 to adjust to sinclair ascii
	scores[5].hiInitals[0] = initial_1 + 64;
	scores[5].hiInitals[1] = initial_2 + 64;
	scores[5].hiInitals[2] = initial_3 + 64;
	scores[screenCounter].hiScoreList = yourScore;
}



void highScore()
{
	assemblyCLS();

	for ( x = 0; x < 200; ++ x )//approx 3 seconds 120
	{
		//if (speccy128k == false)
		{
			PrintStr(highScoreMessage1, 0x0905);// 9, 5
			PrintStr(highScoreMessage2, 0x0407);// 4,7
			PrintStr(highScoreMessage3, 0x0411);// 2,17
			PrintStr(highScoreMessage4, 0x0a12);//9,18
		}
	}

	//now we enter the hiscore initals
	highscoreEntry();

	//sort high score table
	insertionSort();
}

// Game Over
void endgame()
{
	assemblyCLS();
	{
		PrintStr(gameOverTXT, 0x0b03);
	}
	Pause (180);//Pause (120);
}




//via loader.asm
//ld a, ($5c01) ; toggle port value between 00 and 80 every frame


//via engine.asm
//ld a, (port&$ffff) ; toggle port value between 00 and 80 every frame
//xor $80
//ld (port&$ffff), a
//ld a, $18 ; also toggle between bank 5 & 7 for the screen
// jr z, do2 ; and 7 & 0 for the current paging at $c000
//dec a ; so we always show a screen and modify the other

//via engine
//; Initialisation code. The user call this routine to start the engine
//; This will paint clipping bars
//; In 48k also paint the sync bar
//; In 128k we copy from RAM bank 0 to RAM bank 7






	
//http://mdfs.net/Info/Comp/Spectrum/ProgTips/Printout/


//https://www.worldofspectrum.org/forums/discussion/51198/



#endif
