#include "global.h"

wsp::GameWindow     gwd;
wsp::Image          imgPlayers[NUM_PLAYERS];
wsp::Image          imgAliens[NUM_ALIEN_TYPES];
wsp::LayerManager   manager(NUM_PLAYERS + NUM_ALIENS + NUM_SHOTS + 4);
wsp::LayerManager   bgManager(NUM_SPACE_BGS);
bounds_t	    	bounds;
