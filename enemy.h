void enemy_handler(char num_bullets, char killed)
{
	char i = 0;
	char j = 0;
	unsigned char tmpx, tmpy;
	
	// movement of enemies
	for ( i = 1; i < 15; i++ )
	{
		if( sprites[i].n<0x80 )
		{
			for ( j= 0; j < num_bullets; j++ )
					
				if( abs(bullets[j].x-sprites[i].x) + abs(bullets[j].y-sprites[i].y) < 10 )
				{
					sprites[i].n+= 0x80;
					remove_bullet( j );
					tmpx= sprites[i].x>>4;
					tmpy= sprites[i].y>>4;
					tiles[tmpy*scrw+tmpx]= 68;
					tilepaint(tmpx, tmpy, tmpx, tmpy);
					Sound(EFFX, 1+killed++%5);
						
					
						
					
				}
					
				if( sprites[i].f&1 )
					if( sprites[i].y>0 )
					{
						sprites[i].y--;
					}
					
				else
					sprites[i].f^= 1;
					
				else
					if( sprites[i].y<scrh*16 )
						sprites[i].y++;
				else
					sprites[i].f^= 1;
					
				if( sprites[i].f&2 )
					if( sprites[i].x>0 )
						sprites[i].x--;
				else
					sprites[i].f^= 2;
				else
				  if( sprites[i].x<scrw*16 )
					sprites[i].x++;
				else
					sprites[i].f^= 2;
		}
	}
}