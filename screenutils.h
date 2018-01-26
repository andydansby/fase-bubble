#include <stdio.h>//being used to convert ints to strings
#include <input.h>//used to read keys
#include "spectrum.h"

void printtester1(unsigned char info)
{
	char text[10];
	//unsigned char info2 = (unsigned char)info;
	//PrintStr("          ", 321);
	PrintStr("    ", 821);
	sprintf(text, "%d", info);
	//sprintf(text, "%d", info);//prints in decimal
	//sprintf(text, "%x", info);//prints in hex	
	//char* text = "bob";//works
	
	PrintStr(text, 821);	
}

void printtester2(unsigned char info, unsigned char info2)
{
	char text[10];
	PrintStr("          ", 321);	
	sprintf(text, "%d:%d", info,info2);
	PrintStr(text, 321);
}

void printtester3(unsigned short info, unsigned short info2)
{
	char text[20];
	PrintStr("            ", 321);	
	sprintf(text, "%hu:%hu", info,info2);
	//sprintf(text, "%x:%x", info,info2);
	PrintStr(text, 321);
}


void printtester4(short info)
{
	char text[10];
	
	PrintStr("    ", 821);
	sprintf(text, "%d", info);
	PrintStr(text, 821);
}

void printtester5(int info, int info2)
{
	char text[20];
	PrintStr("            ", 321);	
	sprintf(text, "%d:%d", info,info2);
	//sprintf(text, "%x:%x", info,info2);
	PrintStr(text, 321);
}

void printtester6(unsigned char info, unsigned char info2,unsigned char info3, unsigned char info4)
{
	char text[10];
	PrintStr("          ", 321);	
	sprintf(text, "%d:%d:%d:%d", info,info2,info3,info4);
	PrintStr(text, 321);
}

void printtester7(long info)
{
	char text[10];
	
	PrintStr("          ", 821);
	sprintf(text, "%ld", info);
	PrintStr(text, 821);
}


void printtester99(unsigned char *info)
{
	char text[10];
	
	PrintStr("    ", 821);
	sprintf(text, "%s", info);
	PrintStr(text, 821);
}




