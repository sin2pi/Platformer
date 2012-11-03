#ifndef CBULLET_H
#define CBULLET_H
#include <SDL/SDL.h>
#include <vector>
#include "cCollision.h"

class cBullet{
	int speedx,speedy;
	int posx,posy;
	int strength;
	SDL_Surface* img;
	public:
		cBullet(int spx,int spy,int px,int py,int str,SDL_Surface* i);
		int update(const std::vector<SDL_Rect>& objects);
		void show();
		int getStrength();
};
#endif
