#ifndef CBULLET_H
#define CBULLET_H
#include <SDL.h>
#include <vector>
#include "Collision.h"

class cBullet{
    public:
	int speedx,speedy;
	int posx,posy;
	int strength;
	SDL_Rect bull;
	SDL_Surface* img;
		cBullet(int spx,int spy,int px,int py,int str,SDL_Surface* i);
		int update(std::vector<SDL_Rect*>&objects);
		void show();
		int getStrength();
};
#endif
