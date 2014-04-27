#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "shot.h"

class Player : public wsp::Sprite {
	public:
		void update(u32 buttonsHeld, u32 buttonsPressed, wsp::Sprite **enemies);
		void setShots(Shot **shots);
	private:
		Shot **shots;
};

#endif
