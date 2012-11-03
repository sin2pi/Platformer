#include "Collision.h"

extern int gravity;
extern bool jumping;
extern bool DoubleJump;
extern bool jump;
extern bool dJumping;
extern int CurrentLevel;
extern bool once1;
extern bool once2;

cCollision::cCollision()
{

}

bool cCollision::Collision(SDL_Rect *rect1,SDL_Rect *rect2)
{
    if(rect1->y + 77 >= rect2->y + rect2->h)
    return false;
    if(rect1->y + rect1->h <= rect2->y)
    return false;
    if(rect1->x >= rect2->x + rect2->w)
    return false;
    if(rect1->x + rect1->w <= rect2->x)
    return false;
    return true;
}

bool cCollision::EnemyCollision(SDL_Rect *rect1,SDL_Rect *rect2)
{
    if(rect1->y >= rect2->y + rect2->h)
    return false;
    if(rect1->y + rect1->h <= rect2->y)
    return false;
    if(rect1->x >= rect2->x + rect2->w)
    return false;
    if(rect1->x + rect1->w <= rect2->x)
    return false;
    return true;
}

void cCollision::LoadColMap(const char *filename)
{
    LoadMap(filename);
}

void cCollision::SetColMap(SDL_Rect *rect,bool enemy,int playerSpeed)
{
   for(int l = 0; l < mapSizeX; l++)
    {
        for(int j = 0; j < mapSizeY; j++)
        {
            SDL_Rect col[map[l][j]];
            SDL_Rect next[map[l][j]];
            SDL_Rect back[map[l][j]];
            if(map[l][j] >= 1 && map[l][j] <= 6)
            {
                col[map[l][j]].x = l*30;
                col[map[l][j]].y = j*30;
                col[map[l][j]].w = 30;
                col[map[l][j]].h = 30;
            }
            if(map[l][j] == 9)
            {
                next[map[l][j]].x = l*30;
                next[map[l][j]].y = j*30;
                next[map[l][j]].w = 30;
                next[map[l][j]].h = 30;
            }
            // You can add other numbers for other functions
            if(enemy == false)
            {
               if(Collision(rect,&col[map[l][j]]))
               {
                  jump = false;
                  jumping = false;
                  DoubleJump = false;
                  rect->y -= gravity;
               }
               if(EnemyCollision(rect,&next[map[l][j]]))
               {
                   CurrentLevel ++;
               }
            }
            if(enemy == true)
            {

               if(EnemyCollision(rect,&col[map[l][j]]))
               {
                  rect->y -= gravity;
               }
            }

        }
    }

}
