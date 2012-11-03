#include "Particle.h"

extern SDL_Surface *red,*green,*blue,*shimmer,*screen;

Particle::Particle( int X, int Y )
{
    //Set offsets
    x = X - 5 + ( rand() % 25 );
    y = Y - 5 + ( rand() % 25 );

    //Initialize animation
    frame = rand() % 5;

    //Set type
    switch( rand() % 3 )
    {
        case 0: type = red; break;
        case 1: type = green; break;
        case 2: type = blue; break;
    }
}

void Particle::show()
{
    //Show image
    SDL_Rect rect {x,y};
    SDL_BlitSurface(type,NULL,screen,&rect);

    //Show shimmer
    if( frame % 2 == 0 )
    {
        SDL_BlitSurface(shimmer,NULL,screen,&rect);
    }

    //Animate
    frame++;
}

bool Particle::is_dead()
{
    if( frame > 10 )
    {
        return true;
    }

    return false;
}
