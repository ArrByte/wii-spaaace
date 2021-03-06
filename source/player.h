#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "shot.h"

#define RESPAWN_TIME 30

class Player : public wsp::Sprite {
	public:
		Player();
		void update(u32 buttonsHeld, u32 buttonsPressed, wsp::Sprite **enemies);
		void setShots(Shot **shots, unsigned int numberOfShots, bool isOwn);
	private:
		Shot **ownShots;
		Shot **enemyShots;
		unsigned int numOwnShots, numEnemyShots;
		int respawningCountdown;
		
		void startRespawn();
		void stopRespawn();
};

#endif
