#include "alien.h"

Alien::Alien(wsp::Image *img) {
	SetImage(img);
	DefineCollisionRectangle(28, 14, 42, 55);
	resetMotion();
	resetPosition();
	resetShotCountdown();
}

void Alien::setShots(Shot **shots, unsigned int numberOfShots, bool isOwn) {
	if(isOwn) {
		ownShots = shots;
		numOwnShots = numberOfShots;
	} else {
		enemyShots = shots;
		numEnemyShots = numberOfShots;		
	}
}

void Alien::update() {
	Move(motionX, motionY);
	if(GetY() < 0) {
		SetY(0);
		resetMotion();
	}
	else if(GetY() > 480-GetHeight()) {
		SetY(480-GetHeight());
		resetMotion();
	}
	
	int i;
	for(i=0;i<numEnemyShots;i++) {
		if(enemyShots[i]->isFired() == false) continue;
		
		if(CollidesWith(enemyShots[i])) {
			enemyShots[i]->remove();
			resetPosition();
			resetMotion();
			resetShotCountdown();
			break;
		}
	}
	
	if(--lockMotionFrames == 0) resetMotion();	
	if(GetX() < 0) resetPosition();
	if(--nextShotCountdown == 0) {
		resetShotCountdown();
		for(i=0;i<numOwnShots;i++) {
			if(ownShots[i]->isFired() == false) {
				ownShots[i]->fire(GetX(), GetY() + (GetHeight() / 2) - 10, -6);
				break;
			}
		}
	}

}

void Alien::resetMotion() {
	motionX = -4;
	motionY = rand()%10 - 5;	
	lockMotionFrames = Alien::LOCK_MOTION_FRAME_COUNT;
}

void Alien::resetPosition() {
	SetPosition(640 + (rand()%Alien::MAX_OFFSCREEN_OFFSET), rand() % (480-GetHeight()));
}

void Alien::resetShotCountdown() {
	nextShotCountdown = 80 + rand()%41;
}

const int Alien::MAX_OFFSCREEN_OFFSET 		= 640;
const int Alien::LOCK_MOTION_FRAME_COUNT 	= 100;
