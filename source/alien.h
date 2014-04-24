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
};

#endif
