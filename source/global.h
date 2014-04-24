#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <wiisprite.h>
#include <fat.h>

using namespace wsp;

typedef struct {
    int x;
    int y;
} position_t;

typedef struct {
    Quad left;
    Quad top;
    Quad right;
    Quad bottom;
} bounds_t;

GameWindow      gwd;
Image           imgPlayer[2];
Sprite          player[2];
LayerManager    manager(100);
bounds_t	    bounds;

#endif
