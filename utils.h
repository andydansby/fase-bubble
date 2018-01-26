/*
 * FASE utils
 *
 * Copyright (c) 2014 David Colmenero Aka D_Skywalk
 * Copyright (c) 2014 antonio villena
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 *   Simple custom utils
 *
**/

char _g_string[32];
int _g_number = 23;
short _g_str_x = 0;
short _g_str_y = 0;
//unsigned char _g_color = 0;
unsigned char _g_mask = 0;

unsigned char _old_tile = 0xff, _cur_attr = 0xff;

void _show_str();
void _itoa(int number);

/*

  Public macros

*/

#define gettile(x,y) tiles[x + (y << 4) - y ]

#define getroom() (mapy * mapw) + mapx
#define setroom(x)  mapy = x/mapw; \
                    mapx = x%mapw; \
                    update_screen()

//#define settile(x,x, val) tiles[x + (y << 4) - y ] = val

#define drawtile(x,y,val)   tiles[y*scrw+x] = 68; \
                            tilepaint(x, y, x, y)


/*
  Public funcs
*/


void print_str(unsigned char x, unsigned char y, unsigned char mask, unsigned char *s)
{
    _g_str_x = x;
    _g_str_y = y;
    _g_mask = mask;

    ptr_tmp = _g_string; // copy str
    while (*s)
        *ptr_tmp++ = *s++;
    *ptr_tmp = '\0';

    // print with engine sync
    if(fase_status == FASE_RUNNING)
        *drwout = (unsigned int) _show_str;
    else
        _show_str();
}

void print_value(unsigned char x, unsigned char y, int number)
{
    _g_str_x = x;
    _g_str_y = y;
    _g_mask = 1;

    _itoa(number); // g_string saved in func

    // print with engine sync
    if(fase_status == FASE_RUNNING)
        *drwout = (unsigned int) _show_str;
    else
        _show_str();
}

unsigned char check_tile(unsigned char x, unsigned char y)
{
    _g_str_x = x + (y << 4) - y;
    if(_old_tile == tiles[_g_str_x])
        return _cur_attr;
    
    // prepare pointers
    ptr_tmp = &tiles[_g_str_x];
    ptr_jmp = &map_attr[_g_str_x]; 
    
    // get current attr value...
    if (*ptr_jmp == 0xff)
    {
        _cur_attr = 
        *ptr_jmp = comportamiento_tiles[tiles[_g_str_x]];        
    }
    
    //print_value(3,10, (int) _g_str_x);
    
    return *ptr_jmp;
}


void remove_bullet( char k ){
    if( num_bullets )
    {
        num_bullets--;
        while ( k<num_bullets )
        {
            dirbul[k] = dirbul[k+1];
            bullets[k].x = bullets[k+1].x;
            bullets[k].y = bullets[++k].y;
        }
        bullets[k].y= 255;
    }
}


/*

  Screen funcs

*/

void prepare_screen( void )
{
    *screen = mapy * mapw + mapx;
    
    //we force update screen to be able to catch the tileset for the attr
    fase_dwframe();
    ptr_tmp = &tiles[0];
    ptr_jmp = map_attr;
    
    j = 150;
    do
    {
        //*ptr_jmp++ = comportamiento_tiles[*ptr_tmp++];//behavior_tiles
        *ptr_jmp++ = 0xff; //blank
    }while(--j);
        
}


void update_screen()
{
    prepare_screen();
    
    // respawn enemies
    for ( j = 1; j < 5; j++ )
        if ( sprites[j].n >= ENEMY_DEAD )
            sprites[j].n -= ENEMY_DEAD;
}


/*

  Private funcs

*/


/*
  modify g_string with the number passed by parameters
*/
void _itoa(int number) {
    int i = number < 0 ? 3 : 2;
    int t = abs(number);

    while (t = t / 10)
        ++i;
    _g_string[--i] = '\0';
    t = abs(number);

    while (i) {
        _g_string[--i] = '0' + (t % 10);
        t = t / 10;
    }
    
    if (number < 0)
        _g_string[0] = '-';
}

/*
  this function can not have parameters since the engine, 
  only allows calling void / void functions
  so all those variables g_ must be prepared before entering.
*/
void _show_str()
{
    unsigned char * s = _g_string;
    unsigned int scr, dst;
    char count;

    // no fona para mayores de 8
	// not with a for over 8
    if( _g_str_y < 9)
        dst= (_g_str_y << 5 ) + _g_str_x + 0x4000 | *shadow << 8;
    else
        dst= ((_g_str_y - 9 ) << 5 ) + _g_str_x + 0x5000 | *shadow << 8;


    if(_g_mask)
        _g_mask = 0xff;
    
	while (*s)	{
	    scr= 0x3c00 + (*s++ << 3);
	    
        for ( count= 0; count < 8; count++ )
        {
            zxmem[dst] = zxmem[scr++] ^ _g_mask;
            dst+= 0x100;
        }

        dst-= 0x7ff;

    }
}



