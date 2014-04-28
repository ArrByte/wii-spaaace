#include "player.h"

void Player::update(u32 buttonsHeld, u32 buttonsPressed, wsp::Sprite **enemies) {
	if(buttonsHeld & WPAD_BUTTON_RIGHT && !CollidesWith(bounds.top.GetRectangle())) {
		Move(0, -5);
	} else if(buttonsHeld & WPAD_BUTTON_LEFT && !CollidesWith(bounds.bottom.GetRectangle())) {
		Move(0, 5);
	}

	if(buttonsHeld & WPAD_BUTTON_UP && !CollidesWith(bounds.left.GetRectangle())) {
		Move(-2, 0);
	} else if(buttonsHeld & WPAD_BUTTON_DOWN && !CollidesWith(bounds.right.GetRectangle())) {
		Move(2, 0);
	}

	if(buttonsPressed & WPAD_BUTTON_2) {
		int i;
		for(i=0;i<numShots;i++) {
			if(shots[i]->isFired() == false) {
				shots[i]->fire(GetX() + GetWidth(), GetY() + (GetHeight()/2) - 10, 5);
				break;
			}
		}
	}
	
	int i=0;
	for(i=0;i<NUM_ALIENS;i++) {
		if(CollidesWith(enemies[i])) {
			// TODO: Mark player "dead", play explosion anim&sound, respawn in a neat way
			SetPosition(100, 100);
			break;
		}
	}	
}

void Player::setShots(Shot **shots, unsigned int numberOfShots) {
	this->shots = shots;
	numShots = numberOfShots;
}
