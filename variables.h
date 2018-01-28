////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////

//extern long heap(50000);
//#pragma output CLIB_MALLOC_HEAP_SIZE = 10000
//#pragma output STACKPTR = 64000 

unsigned char data[20]= 
{
  0, 66, 17, 0,
  8, 0, 0, 2,
  9, 0, 0, 3,
  10, 0, 0, 1,
  12, 0, 0, 2
};//enemy placement data

unsigned char x1[40] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};//changed from short to unsigned char

unsigned char y1[40] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};//changed from short to unsigned char

unsigned char tileAttribute[40] = {
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0
};//read tile value

// short horizonal [3] = {0,0,0};
// short vertical [3] = {0,0,0};


short levelPositioning [3] = {0,0,0};

//artificial stupidity 2
unsigned char enemyData[5] = {0,0,0,0,0};//used to send enemy AI to function

char dirbul[4];

//globals
char i, j;
char killed;
char mapx, mapy;
char spacepressed;

char num_bullets;
char k;

char buildMap;// are you currently playing
char loop;
char xx, yy;

unsigned int romCounter;//randomize function

short xx1;
short xx2;
short yy1;
short yy2;

//unsigned char screenX,screenY;//temporary

short isLevelRead;//used to read each level when loaded in memory

//short count;//count how many items are in the array	
//short tile;


char enemySlowDown;
char enemySpeedUp;

unsigned char lives;

unsigned char playerXpos;//player X position 0-255
unsigned char playerYpos;//player Y position 0-172
unsigned char playerXattr;//player x attribute position
unsigned char playerYattr;//player y attribute position

//these temporary variables are to be used with functions
unsigned char screenX;
unsigned char screenY;
unsigned char count;//count how many items are in the array	
unsigned char tile;
unsigned char attribute;
unsigned char objectRadius;
unsigned char differenceX,differenceY;
unsigned char tmpx, tmpy;
unsigned char iterator;
short squaredRadius, squaredDifferenceX, squaredDifferenceY;//these have to be shorts or larger because the numbers are too large to fit in char
//these temporary variables are to be used with functions


static unsigned short jz,jsr=5;//used in randomizer



unsigned char level;//which game level are we on



short x, vx, ax;
short y, vy, ay;
unsigned char movePlayer;

////   Moved from Function ////
//short vY1, aY1, YY1;//eliminated
//short vX1,aX1,XX1;

unsigned char bob;//used to print to screen
unsigned char sue;//used to print to screen also
unsigned char tim,tom;
////////////////////////////////////
//         GLOBAL VARIABLES       //
////////////////////////////////////
