#include "Player.h"

extern int gravity;
extern int i[2];
extern bool jumping;
extern int TOTAL_PARTICLES;
extern Particle *particles[ 20 ];

cPlayer::cPlayer(const char *filename,int x,int y,int w,int h,int xvel,int health)
{
    image = SDL_LoadBMP(filename);
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xVel = xvel;
    yVel = 1;
    hp = health;
    frame = 0;
    for( int p = 0; p < 20; p++ )
    {
        particles[ p ] = new Particle( x, y );
    }
}

SDL_Rect *cPlayer::getRect()
{
    return &box;
}

void cPlayer::ShowParticle(SDL_Rect camera)
{
    //Go through particles
    for( int p = 0; p < 20; p++ )
    {
        //Delete and replace dead particles
        if( particles[ p ]->is_dead() == true )
        {
            delete particles[ p ];

            particles[ p ] = new Particle( box.x - camera.x, box.y - camera.y );
        }
    }

    //Show particles
    for( int p = 0; p < 20; p++ )
    {
        particles[ p ]->show();
    }
}

SDL_Rect cPlayer::SetCamera(SDL_Rect cam)
{
    cam.x = ( box.x + box.w / 2 ) - 640 / 2;
    cam.y = ( box.y + box.h / 2 ) - 480 + 200;
    if( cam.x < 0)
    {
        cam.x = 0;
    }
    if(cam.x > 3200)
    {
        cam.x = 3200;
    }
    if( cam.y < 0)
    {
        cam.y = 0;
    }
    if(cam.y > 3200)
    {
        cam.y = 3200;
    }
    return cam;
}

void cPlayer::Move(int *i)
{
    box.y += gravity;
    if(i[0])
    box.x -= xVel;
    if(i[1])
    box.x += xVel;
}

void cPlayer::Show(SDL_Rect camera)
{
    if(i[1])
    {
       frame ++;
       if(frame >= 2)
       frame = 0;
    }
    if(i[0])
    {
        frame ++;
        if(frame >= 4)
        frame = 2;
    }
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,255,255));
    SDL_Rect rect = {box.x - camera.x, box.y - camera.y};
    SDL_Rect clip[4];
    clip[0] = {0,0,30,50};
    clip[1] = {30,0,30,50};
    clip[2] = {60,0,30,50};
    clip[3] = {90,0,30,50};
    SDL_BlitSurface(image,&clip[frame],SDL_GetVideoSurface(),&rect);

}
