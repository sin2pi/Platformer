#include "Enemy.h"

extern int gravity;
extern SDL_Rect camera;
extern Particle *particles[ 40 ];

cEnemy::cEnemy(const char *filename,int x,int y,int w,int h,int xvel,int yvel,int health)
{
    image = SDL_LoadBMP(filename);
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xVel = xvel;
    yVel = yvel;
    hp = health;
    e = 2;
    frame = 0;
    for( int p = 0; p < 40; p++ )
    {
        particles[ p ] = new Particle( x, y );
    }
}

SDL_Rect *cEnemy::getRect()
{
    return &box;
}

void cEnemy::ShowParticle(SDL_Rect camera)
{
    //Go through particles
    for( int p = 0; p < 40; p++ )
    {
        //Delete and replace dead particles
        if( particles[ p ]->is_dead() == true )
        {
            delete particles[ p ];

            particles[ p ] = new Particle( box.x - camera.x, box.y - camera.y );
        }
    }

    //Show particles
    for( int p = 0; p < 40; p++ )
    {
        particles[ p ]->show();
    }
}

void cEnemy::Show(SDL_Rect camera)
{
    frame ++;
    if(frame >= 2)
    frame = 0;
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,255,255));
    SDL_Rect rect;
    rect.x = box.x - camera.x;
    rect.y = box.y - camera.y;
    SDL_Rect clip[2];
    clip[0] = {0,0,40,40};
    clip[1] = {40,0,40,40};
    SDL_BlitSurface(image,&clip[frame],SDL_GetVideoSurface(),&rect);
}

void cEnemy::Movement(int x1,int x2)
{

    if(box.x != x1 && e == 2)
    b = 1;
    if(b == 1)
     {
          if (x1  < box.x){
             box.x -= xVel;
             }
          if (x1 > box.x){
             box.x += xVel;
             }
     }
     if(box.x == x1)
     {
       e = 1;
       b = 2;
     }
    if(e == 1)
     {
          if (x2  < box.x){
             box.x -= xVel;
             }
          if (x2 > box.x){
             box.x += xVel;
             }
     }
     if(box.x == x2)
     {
       e = 2;
     }

}

