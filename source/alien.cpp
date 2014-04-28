#include "alien.h"

Alien::Alien(wsp::Image *img) {
	SetImage(img);
	DefineCollisionRectangle(28, 14, 42, 55);
	resetMotion();
	resetPosition();
}

void Alien::setShots(Shot **shots) {
	this->shots = shots;
}

void Alien::update() {
	Move(motionX, motionY);
	if(GetY() < 0) SetY(0);
	else if(GetY() > 480-GetHeight()) SetY(480-GetHeight());

	int i;
	for(i=0;i<NUM_SHOTS;i++) {
		if(shots[i]->isFired() == false) continue;
		
		if(CollidesWith(shots[i])) {
			shots[i]->remove();
			resetPosition();
			resetMotion();
			break;
		}
	}
	
	if(--lockMotionFrames == 0) resetMotion();
	if(GetX() < 0) resetPosition();
}

void Alien::resetMotion() {
	motionX = -4;
	motionY = rand()%10 - 5;	
	lockMotionFrames = Alien::LOCK_MOTION_FRAME_COUNT;
}

void Alien::resetPosition() {
	SetPosition(640 + (rand()%Alien::MAX_OFFSCREEN_OFFSET), rand() % (480-GetHeight()));
}

const int Alien::MAX_OFFSCREEN_OFFSET 		= 640;
const int Alien::LOCK_MOTION_FRAME_COUNT 	= 100;
