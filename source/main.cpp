#include "player.h"
#include "alien.h"
#include "shot.h"
#include "global.h"

using namespace wsp;

Player players[NUM_PLAYERS];
Alien *aliens[NUM_ALIENS];
Shot *playerShots[NUM_SHOTS_PLAYERS];
Shot *alienShots[NUM_SHOTS_ALIENS];
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
        players[i].setShots((Shot **)&playerShots, NUM_SHOTS_PLAYERS, true);
        players[i].setShots((Shot **)&alienShots,  NUM_SHOTS_ALIENS,  false);
        manager.Append(&players[i]);
    }
}

void initAliens(unsigned int maxAliens) {
	if(imgAliens[0].LoadImage("/apps/Spaaace/images/alien3.png") != IMG_LOAD_ERROR_NONE) exit(1);
	int i;
	for(i=0;i<maxAliens;i++) {
		aliens[i] = new Alien(&imgAliens[0]);
        aliens[i]->setShots((Shot **)&playerShots, NUM_SHOTS_PLAYERS, false);
        aliens[i]->setShots((Shot **)&alienShots,  NUM_SHOTS_ALIENS,  true);
		manager.Append(aliens[i]);
	}
}

void initShots() {
	if(imgPlayerBullet.LoadImage("/apps/Spaaace/images/bullet.png") != IMG_LOAD_ERROR_NONE) exit(1);
	if(imgAlienBullet.LoadImage("/apps/Spaaace/images/bullet_enemy.png") != IMG_LOAD_ERROR_NONE) exit(1);
	int i;
	for(i=0;i<NUM_SHOTS_PLAYERS;i++) {
		playerShots[i] = new Shot(&imgPlayerBullet, -100, -100);
		manager.Append(playerShots[i]);
	}
	
	for(i=0;i<NUM_SHOTS_ALIENS;i++) {
		alienShots[i] = new Shot(&imgAlienBullet, -100, -100);
		manager.Append(alienShots[i]);
	}
}

void initFont() {
	if(imgFont.LoadImage("/apps/Spaaace/images/font.png") != IMG_LOAD_ERROR_NONE) exit(1);
	font.SetImage(&imgFont, 25, 24);
}

void drawNumber(int number, int x, int y) {
	char str[20];
	int i;
	sprintf(str, "%i", number);
	for(i=0;i<strlen(str);i++) {
		font.SetFrame(26 + str[i] - 48);
		font.Draw(x + i*26, y);
	}
}

void drawString(char *str, int x, int y) {
	int i;
	for(i=0;i<strlen(str);i++) {
		if(str[i] == ' ') continue;
		if(str[i] <= '9') font.SetFrame(26 + str[i] - 48);
		else font.SetFrame(str[i] - 97);
		font.Draw(x + i*26, y);
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
	initFont();
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
	
	bool inGame = false;
	players[1].SetPosition(-300, -300);
	numPlayers = 1;
	
    while(true) {
        WPAD_ScanPads();

        if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;        
        
        if(!inGame) {
			if(lifes <= 0) {
				drawString("game over", 223, 202);

			}
			drawString("player 1 a to start", 93, 228);
			if(numPlayers == 1) drawString("player 2 a to join", 106, 254);
			else drawString("player 2 ready", 158, 254);

			gwd.Flush();

			if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_HOME) break;        

			if(WPAD_ButtonsDown(WPAD_CHAN_1) & WPAD_BUTTON_A) {
				numPlayers = 2;
				players[1].SetPosition(100, 100);
			}
			
			if(WPAD_ButtonsDown(WPAD_CHAN_0) & WPAD_BUTTON_A) {
				score = 0;
				lifes = 10;
				inGame = true;
			}			
			
			continue;
		}
        
        int i;
		for(i=0;i<NUM_ALIENS;i++) {
			aliens[i]->update();
		}

        for(i=0;i<numPlayers;i++) {
            u32 held    = WPAD_ButtonsHeld(i);
            u32 pressed = WPAD_ButtonsDown(i);
            players[i].update(held, pressed, (wsp::Sprite **)aliens);
        }
        
        for(i=0;i<NUM_SHOTS_PLAYERS;i++) {
			playerShots[i]->update();
			if(lifes <= 0) inGame = false; 
		}

        for(i=0;i<NUM_SHOTS_ALIENS;i++) {
			alienShots[i]->update();
		}

		for(i=0;i<NUM_SPACE_BGS;i++) {
			bgs[i].Move(-1, 0);
			if(bgs[i].GetX() < -640) {
				bgs[i].SetPosition(1920, 0);
			}
		}

        manager.Draw(0,0);
        drawString("score", 0, 0);
		drawNumber(score, 156, 0);

        drawString("ships x", 380, 0);
		drawNumber(lifes, 562, 0);
		gwd.Flush();	
    }

    MP3Player_Stop();
    if(musicFile != NULL) fclose(musicFile);

    return 0;
}
