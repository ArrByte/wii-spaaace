#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <fat.h>

typedef struct {
    wsp::Quad left;
    wsp::Quad top;
    wsp::Quad right;
    wsp::Quad bottom;
} bounds_t;

extern wsp::GameWindow     gwd;
extern wsp::Image          imgPlayers[2];
extern wsp::Image          imgAliens[2];
extern wsp::LayerManager   manager;
extern bounds_t	    	   bounds;

#endif
