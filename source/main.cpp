#include "global.h"
#include "player.h"

using namespace wsp;

Player players[2];


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
    for(i=0;i<2;i++) { 
        if(imgPlayers[i].LoadImage(imgPaths[i]) != IMG_LOAD_ERROR_NONE) exit(1);
        players[i].SetImage(&imgPlayers[i]);
        players[i].SetPosition(100, 100);
        manager.Append(&players[i]);
    }
}

int main(int argc, char **argv) {
    gwd.InitVideo();
    gwd.SetBackground((GXColor){ 0, 0, 0, 255 });
 
    fatInitDefault();
    
    WPAD_Init();

    loadPlayerSprites();
    initBoundaries();

    while(true) {
        WPAD_ScanPads();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;
        int i;

        for(i=0;i<2;i++) {
            u32 pressed = WPAD_ButtonsHeld(i);
            players[i].update(pressed);
        }

        manager.Draw(0,0);
        gwd.Flush();
    }
    return 0;
}
