#include "alien.h"

Alien::Alien(wsp::Image *img) {
	SetImage(img);
	resetMotion();
	resetPosition();
}

void Alien::update() {
	Move(motionX, motionY);
	if(GetY() < 0) SetY(0);
	else if(GetY() > 480-GetHeight()) SetY(480-GetHeight());
	
	if(--lockMotionFrames == 0) resetMotion();
	if(GetX() < 0) resetPosition();
}

void Alien::resetMotion() {
	motionX = -2;
	motionY = rand()%10 - 5;	
	lockMotionFrames = 100;
}

void Alien::resetPosition() {
	SetPosition(640 + (rand()%500), rand() % (480-GetHeight()));
}
