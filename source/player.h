#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"

class Player : public wsp::Sprite {
	public:
		void update(u32 buttonsHeld, wsp::Sprite **enemies);
};

#endif
