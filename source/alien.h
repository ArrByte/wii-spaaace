#ifndef ALIEN_H
#define ALIEN_H

#include "global.h"
#include "shot.h"

class Alien : public wsp::Sprite {
	public:
		void update();
		Alien(wsp::Image *img);
		void setShots(Shot **shots, unsigned int numberOfShots, bool isOwn);
	private:
		unsigned int lockMotionFrames;
		short motionX;
		short motionY;
		void resetMotion();
		void resetPosition();
		Shot **ownShots;
		Shot **enemyShots;
		unsigned int numOwnShots, numEnemyShots;
		
		static const int MAX_OFFSCREEN_OFFSET;
		static const int LOCK_MOTION_FRAME_COUNT;
};

#endif
