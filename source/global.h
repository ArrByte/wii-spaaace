#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <fat.h>

#define NUM_ALIENS 		 	 5
#define NUM_ALIEN_TYPES  	 1
#define NUM_PLAYERS 	 	 2
#define NUM_SHOTS			50

typedef struct {
    wsp::Quad left;
    wsp::Quad top;
    wsp::Quad right;
    wsp::Quad bottom;
} bounds_t;

extern wsp::GameWindow     gwd;
extern wsp::Image          imgPlayers[NUM_PLAYERS];
extern wsp::Image          imgAliens[NUM_ALIEN_TYPES];
extern wsp::LayerManager   manager;
extern bounds_t	    	   bounds;

#endif
