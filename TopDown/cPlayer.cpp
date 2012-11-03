#include "cPlayer.h"

cPlayer::cPlayer(int x,int y,int w,int h,SDL_Rect *player)
{
    player->x = x;
    player->y = y;
    player->w = w;
    player->h = h;
}

cPlayer::~cPlayer(){}

void cPlayer::Movement(SDL_Rect *player,int speed)
{
    if(move[0])
    player->y -= speed;
    if(move[1])
    player->x -= speed;
    if(move[2])
    player->y += speed;
    if(move[3])
    player->x += speed;
}

void cPlayer::Show(SDL_Surface *playerS,SDL_Rect *playerR)
{
    SDL_BlitSurface(playerS,NULL,screen,playerR);
}

void cPlayer::PlayerCollision(SDL_Rect *player,SDL_Rect *solid,int playerSpeed,int type)
{
    if(type == 1) //if object is static
    {
        if(move[0] == 1)
        if(Collision(player,solid))
        player->y += playerSpeed;
        if(move[1] == 1)
        if(Collision(player,solid))
        player->x += playerSpeed;
        if(move[2] == 1)
        if(Collision(player,solid))
        player->y -= playerSpeed;
        if(move[3] == 1)
        if(Collision(player,solid))
        player->x -= playerSpeed;
    }
    if(type = 2) //if object is dynamic
    {
        if(move[0] == 1)
        if(Collision(player,solid))
        solid->y -= playerSpeed;
        if(move[1] == 1)
        if(Collision(player,solid))
        solid->x -= playerSpeed;
        if(move[2] == 1)
        if(Collision(player,solid))
        solid->y += playerSpeed;
        if(move[3] == 1)
        if(Collision(player,solid))
        solid->x += playerSpeed;
    }
}
