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

GameWindow gwd;
Image           imgPlayer[2];
Sprite          player[2];
LayerManager    manager(100);
bounds_t        bounds;

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
        if(imgPlayer[i].LoadImage(imgPaths[i]) != IMG_LOAD_ERROR_NONE) exit(1);
        player[i].SetImage(&imgPlayer[i]);
        player[i].SetPosition(100, 100);
        manager.Append(&player[i]);
    }
}

int main(int argc, char **argv) {
    gwd.InitVideo();
    gwd.SetBackground((GXColor){ 0, 0, 0, 255 });
 
    fatInitDefault();
    
    WPAD_Init();

    loadPlayerSprites();
    initBoundaries();

    position_t playerPos[2];
    playerPos[0].x =  50;
    playerPos[0].y = 100;

    playerPos[1].x =  50;
    playerPos[1].y = 200;


    while(true) {
        WPAD_ScanPads();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;
        int i;

        for(i=0;i<2;i++) {
            u32 pressed = WPAD_ButtonsHeld(i); 
            if(pressed & WPAD_BUTTON_RIGHT && !player[i].CollidesWith(bounds.top.GetRectangle())) {
                playerPos[i].y -= 5;
            } else if(pressed & WPAD_BUTTON_LEFT 
                    && !player[i].CollidesWith(bounds.bottom.GetRectangle())) {
                playerPos[i].y += 5;
            }

            if(pressed & WPAD_BUTTON_UP && !player[i].CollidesWith(bounds.left.GetRectangle())) {
                playerPos[i].x -= 2;
            } else if(pressed & WPAD_BUTTON_DOWN 
                    && !player[i].CollidesWith(bounds.right.GetRectangle())) {
                playerPos[i].x += 2;
            }

            if(pressed & WPAD_BUTTON_2) {
                //Shoot?
            }

            player[i].SetPosition(playerPos[i].x, playerPos[i].y);
        }

        manager.Draw(0,0);
        gwd.Flush();
    }
    return 0;
}
