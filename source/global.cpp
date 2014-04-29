#include "global.h"

wsp::GameWindow     gwd;
wsp::Image          imgPlayers[NUM_PLAYERS];
wsp::Image          imgAliens[NUM_ALIEN_TYPES];
wsp::Image			imgBgs[NUM_SPACE_BGS];
wsp::Image			imgPlayerBullet;
wsp::Image			imgAlienBullet;
wsp::Image			imgFont;
wsp::Sprite			font;
wsp::LayerManager   manager(NUM_PLAYERS + NUM_ALIENS + NUM_SHOTS_PLAYERS + NUM_SHOTS_ALIENS + NUM_SPACE_BGS + 4);
bounds_t	    	bounds;
int					score = 0;
int 				lifes = 10;
int 				numPlayers = 2;

s32  my_reader(void *fp,void *dat, s32 size)
{
	return fread(dat, 1, size, (FILE *)fp);
}
