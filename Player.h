#include <SDL.h>
#include "Particle.h"
#include "Collision.h"

class cPlayer : public cCollision
{
    private:

          SDL_Rect box,box2;

          SDL_Surface *image;

    public:

          int hp,xVel,yVel,frame;

          cPlayer(const char *,int x,int y,int w,int h,int xvel,int health);

          SDL_Rect *getRect();

          SDL_Rect SetCamera(SDL_Rect cam);

          void Move(int *i);

          void Show(SDL_Rect camera);

          void ShowParticle(SDL_Rect camera);

          void Jump();

};
