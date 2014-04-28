#include "player.h"
#include "alien.h"
#include "shot.h"
#include "global.h"

using namespace wsp;

Player players[NUM_PLAYERS];
Alien *aliens[NUM_ALIENS];
Shot *shots[NUM_SHOTS];
wsp::Sprite bgs[NUM_SPACE_BGS];

void initBackgrounds()
{
	int i=0;
	for(int i=0;i<NUM_SPACE_BGS;i++) {
		char path[256];
		sprintf(path, "/apps/Spaaace/images/space-%i.png", i%2);
		if(imgBgs[i].LoadImage((const char *)path) != IMG_LOAD_ERROR_NONE) exit(1);
		bgs[i].SetImage(&imgBgs[i], 640, 480);
		bgs[i].SetPosition(i*640, 0);
		manager.Append(&bgs[i]);
	}
}

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
        if(i == 0) players[i].DefineCollisionRectangle(0, 2, 58, 76);
        else 	   players[i].DefineCollisionRectangle(6, 6, 62, 69);
        players[i].setShots((Shot **)&shots);
        manager.Append(&players[i]);
    }
}

void initAliens(unsigned int maxAliens) {
	if(imgAliens[0].LoadImage("/apps/Spaaace/images/alien3.png") != IMG_LOAD_ERROR_NONE) exit(1);
	int i;
	for(i=0;i<maxAliens;i++) {
		aliens[i] = new Alien(&imgAliens[0]);
        aliens[i]->setShots((Shot **)&shots);
		manager.Append(aliens[i]);
	}
}

void initShots() {
	if(bullet.LoadImage("/apps/Spaaace/images/bullet.png") != IMG_LOAD_ERROR_NONE) exit(1);
	int i;
	for(i=0;i<NUM_SHOTS;i++) {
		shots[i] = new Shot(&bullet, -100, -100);
		manager.Append(shots[i]);
	}
}

int main(int argc, char **argv) {
    gwd.InitVideo();
    gwd.SetBackground((GXColor){ 0, 0, 0, 255 });
 
    fatInitDefault();
    WPAD_Init();

    ASND_Init();
    MP3Player_Init();
	MP3Player_Volume(255);
	ASND_Pause(0);
	
	initShots();
    loadPlayerSprites();
    initBoundaries();
	initAliens(NUM_ALIENS);
    initBackgrounds();

	FILE *musicFile = NULL;
	musicFile = fopen("/apps/Spaaace/space.mp3", "r");
	if(musicFile == NULL) {
		ASND_End();
		exit(1);
		}
	MP3Player_PlayFile((void *)musicFile, my_reader, NULL);
	
    while(true) {
        WPAD_ScanPads();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;        
        
        int i;
		for(i=0;i<NUM_ALIENS;i++) {
			aliens[i]->update();
		}

        for(i=0;i<NUM_PLAYERS;i++) {
            u32 held    = WPAD_ButtonsHeld(i);
            u32 pressed = WPAD_ButtonsDown(i);
            players[i].update(held, pressed, (wsp::Sprite **)aliens);
        }
        
        for(i=0;i<NUM_SHOTS;i++) {
			shots[i]->update();
		}

		for(i=0;i<NUM_SPACE_BGS;i++) {
			bgs[i].Move(-1, 0);
			if(bgs[i].GetX() < -640) {
				bgs[i].SetPosition(1920, 0);
			}
		}

        manager.Draw(0,0);
        gwd.Flush();
    }

    MP3Player_Stop();
    if(musicFile != NULL) fclose(musicFile);

    return 0;
}
