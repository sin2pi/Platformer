#include <SDL.h>
#include "Particle.h"

class cEnemy
{
    private:

           SDL_Rect box;

           SDL_Surface *image;

    public:

           int xVel,yVel,frame;

           int hp,e,b;

           cEnemy(const char *,int x,int y,int w,int h,int xvel,int yvel,int health);

           SDL_Rect *getRect();

           SDL_Rect *GetRect();

           void ShowParticle(SDL_Rect camera);

           void Movement(int x, int y);

           void Show(SDL_Rect camera);

};
