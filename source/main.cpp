#include "global.h"
#include "player.h"
#include "alien.h"

using namespace wsp;

Player players[NUM_PLAYERS];
Alien *aliens[NUM_ALIENS];


void initBoundaries() {
    bounds.left.SetPosition(-1, 0);
    bounds.left.SetWidth(1);
    bounds.left.SetHeight(480);

    bounds.right.SetPosition(640, 0);
    bounds.right.SetWidth(1);
    bounds.right.SetHeight(480);
    
    bounds.top.SetPosition(0, -1);
    bounds.top.SetWidth(640);
    bounds.top.SetHeight(1);

    bounds.bottom.SetPosition(0, 480);
    bounds.bottom.SetWidth(640);
    bounds.bottom.SetHeight(1);
}

void loadPlayerSprites() {
    const char *imgPaths[2] = { "/apps/Spaaace/images/ship.png", "/apps/Spaaace/images/ship2.png" };
    int i;
    for(i=0;i<NUM_PLAYERS;i++) { 
        if(imgPlayers[i].LoadImage(imgPaths[i]) != IMG_LOAD_ERROR_NONE) exit(1);
        players[i].SetImage(&imgPlayers[i]);
        players[i].SetPosition(100, 100);
        manager.Append(&players[i]);
    }
}

void initAliens(unsigned int maxAliens) {
	if(imgAliens[0].LoadImage("/apps/Spaaace/images/alien3.png") != IMG_LOAD_ERROR_NONE) exit(1);
	int i;
	for(i=0;i<maxAliens;i++) {
		aliens[i] = new Alien(&imgAliens[0]);
		manager.Append(aliens[i]);
	}
}


int main(int argc, char **argv) {
    gwd.InitVideo();
    gwd.SetBackground((GXColor){ 0, 0, 0, 255 });
 
    fatInitDefault();
    
    WPAD_Init();

    loadPlayerSprites();
    initBoundaries();
	initAliens(NUM_ALIENS);

    while(true) {
        WPAD_ScanPads();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;
        int i;

		for(i=0;i<NUM_ALIENS;i++) {
			aliens[i]->update();
		}

        for(i=0;i<NUM_PLAYERS;i++) {
            u32 pressed = WPAD_ButtonsHeld(i);
            players[i].update(pressed);
        }

        manager.Draw(0,0);
        gwd.Flush();
    }
    return 0;
}
