#include "player.h"

void Player::update(u32 buttonsHeld, wsp::Sprite **enemies) {
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

	if(buttonsHeld & WPAD_BUTTON_2) {
		//Shoot?
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
