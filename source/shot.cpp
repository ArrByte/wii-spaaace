#include "shot.h"

Shot::Shot(wsp::Image *img, int x, int y) {
	SetImage(img);
	SetPosition(x, y);
	fired = false;
}

bool Shot::isFired() {
	return fired;
}

void Shot::fire(int x, int y, short direction) {
	fired = true;
	SetPosition(x, y);
	this->direction = direction;
}

void Shot::remove() {
	fired = false;
	SetPosition(-100, -100);
}

void Shot::update() {
	if(fired == false) return;	
	Move(direction, 0);
	
	if(GetX() < 0 || GetX() > 640) {
		fired = false;
		SetPosition(-100, -100);
	}
}

