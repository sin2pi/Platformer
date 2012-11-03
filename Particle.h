#ifndef particles_h
#define particles_h

#include <SDL.h>

class Particle
{
    private:
    //Offsets
    int x, y;

    //Current frame of animation
    int frame;

    //Type of particle
    SDL_Surface *type;

    public:
    //Constructor
    Particle( int X, int Y );

    //Shows the particle
    void show();

    //Checks if particle is dead
    bool is_dead();
};

#endif
