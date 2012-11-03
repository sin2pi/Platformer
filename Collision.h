#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

#include <SDL.h>
#include "Tile.h"

class cCollision : public cTile
{
    public:

          cCollision();

          bool Collision(SDL_Rect *rect1,SDL_Rect *rect2);

          bool EnemyCollision(SDL_Rect *rect1,SDL_Rect *rect2);

          void SetColMap(SDL_Rect *rect,bool enemy,int xVel);

          void LoadColMap(const char *filename);
};

#endif // COLLISION_H_INCLUDED
