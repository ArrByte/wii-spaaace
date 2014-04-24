#include "player.h"

void Player::update(u32 buttonsHeld) {
	if(buttonsHeld & WPAD_BUTTON_RIGHT && !this->CollidesWith(bounds.top.GetRectangle())) {
		this->Move(0, -5);
	} else if(buttonsHeld & WPAD_BUTTON_LEFT 
			&& !this->CollidesWith(bounds.bottom.GetRectangle())) {
		this->Move(0, 5);
	}

	if(buttonsHeld & WPAD_BUTTON_UP && !this->CollidesWith(bounds.left.GetRectangle())) {
		this->Move(-2, 0);
	} else if(buttonsHeld & WPAD_BUTTON_DOWN 
			&& !this->CollidesWith(bounds.right.GetRectangle())) {
			this->Move(2, 0);
	}

	if(buttonsHeld & WPAD_BUTTON_2) {
		//Shoot?
	}
	
}
