#ifndef SHOT_H
#define SHOT_H

#include "global.h"

class Shot : public wsp::Sprite {
	public:
		Shot(wsp::Image *img, int x, int y);
		void update();
		bool isFired();
		void fire(int x, int y, short direction);
		void remove();
	private:
		bool fired;
		short direction;
};

#endif
