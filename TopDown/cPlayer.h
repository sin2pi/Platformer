#ifndef CPLAYER_H_INCLUDED
#define CPLAYER_H_INCLUDED

#include "cCollision.h"

extern SDL_Surface *screen;
extern int move[4];

class cPlayer : public cCollision
{
    public:

           cPlayer(int x,int y,int w,int h,SDL_Rect *player);

           ~cPlayer();

           void PlayerCollision(SDL_Rect *player,SDL_Rect *solid,int playerSpeed,int type);

           void Movement(SDL_Rect *, int speed);

           void Show(SDL_Surface *,SDL_Rect *);
};

#endif // CPLAYER_H_INCLUDED
