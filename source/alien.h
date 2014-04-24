#ifndef ALIEN_H
#define ALIEN_H

#include "global.h"

class Alien : public wsp::Sprite {
	public:
		void update();
		Alien(wsp::Image *img);
	private:
		unsigned int lockMotionFrames;
		short motionX;
		short motionY;
		void resetMotion();
		void resetPosition();
		
		static const int MAX_OFFSCREEN_OFFSET;
		static const int LOCK_MOTION_FRAME_COUNT;
};

#endif
