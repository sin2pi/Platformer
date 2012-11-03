#include "cBullet.h"

cBullet::cBullet(int spx,int spy,int px,int py,int str,SDL_Surface* i)
{
	speedx=spx;
	speedy=spy;
	posx=px;
	posy=py;
	strength=str;
	img=i;
}

int cBullet::update(const std::vector<SDL_Rect>& objects)
{
	posx+=speedx;
	posy+=speedy;
	cCollision col;
	//if you implement scrolling, you should subtract the cam position from position, before do the comparition (see scrolling background tutorial
	//or sidescroller game tutorial)
	if(posx>SDL_GetVideoSurface()->w || posy>SDL_GetVideoSurface()->h || posx+img->w<0 || posy+img->h<0)
		return -2;	//out of screen
	SDL_Rect rec={posx,posy,img->w,img->h};
	for(int i=0;i<objects.size();i++)
		if(col.Collision(&objects[i],&rec))
			return i;	//the bullet hit the ith object (like enemy)
	return -1;	//hit noone
}

void cBullet::show()
{
	SDL_Rect rec={posx,posy};
	SDL_BlitSurface(img,NULL,SDL_GetVideoSurface(),&rec);
}

int cBullet::getStrength()
{
	return strength;
}
