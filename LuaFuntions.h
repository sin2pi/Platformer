#ifndef LUA_FUNCTIONS_H_INCLUDED
#define LUA_FUNCTIONS_H_INCLUDED

#include <lua.hpp>
#include <lauxlib.h>
#include <SDL_mixer.h>

extern cPlayer player1;
extern cEnemy enemy1;
extern cEnemy enemy2;
extern cEnemy enemy3;
extern int lives;
extern int bulletAmount;

int LoadMusic(lua_State *L)
{
    Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
    Mix_Music *music;
    music = Mix_LoadMUS(lua_tostring(L,-1));
    Mix_PlayMusic(music,-1);
    return 0;
}

int Load_Script(lua_State *L)
{
   luaL_dofile(L,lua_tostring(L,-1));
   return 0;
}

int Player_SetHealth(lua_State *L)
{
    player1.hp += (int)lua_tonumber(L,-1);
    return 0;
}

int Bullet_Amount(lua_State *L)
{
    bulletAmount += (int)lua_tonumber(L,-1);
    return 0;
}

int Player_SetPosX(lua_State *L)
{
    player1.getRect()->x = (int)lua_tonumber(L,-1);
    return 0;
}

int Player_SetPosY(lua_State *L)
{
    player1.getRect()->y = (int)lua_tonumber(L,-1);
    return 0;
}

int Player_lives(lua_State *L)
{
    lives = (int)lua_tonumber(L,-1);
    return 0;
}

int Enemy_SetPosX(lua_State *L)
{
    int arg = lua_gettop(L);

    if(arg == 2)
    {
        if(lua_isnumber(L, -arg) && lua_isnumber(L, -arg + 1))
        {
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy1.getRect()->x = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 2)
            {
                enemy2.getRect()->x = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 3)
            {
                enemy3.getRect()->x = (int)lua_tonumber(L,-arg + 1);
            }
        }
    }

}

int Enemy_SetPosY(lua_State *L)
{
    int arg = lua_gettop(L);

    if(arg == 2)
    {
        if(lua_isnumber(L, -arg) && lua_isnumber(L, -arg + 1))
        {
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy1.getRect()->y = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 2)
            {
                enemy2.getRect()->y = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 3)
            {
                enemy3.getRect()->y = (int)lua_tonumber(L,-arg + 1);
            }
        }
    }

}

int Enemy_SetHealth(lua_State *L)
{
    int arg = lua_gettop(L);

    if(arg == 2)
    {
        if(lua_isnumber(L, -arg) && lua_isnumber(L, -arg + 1))
        {
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy1.hp = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 2)
            {
                enemy2.hp = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 3)
            {
                enemy3.hp = (int)lua_tonumber(L,-arg + 1);
            }
        }
    }

}

int Enemy_xVel(lua_State *L)
{
    int arg;

    arg = lua_gettop(L);

    if(arg == 2)
    {
        if(lua_isnumber(L,-arg) && lua_isnumber(L,-arg + 1))
        {
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy1.xVel = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy2.xVel = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy3.xVel = (int)lua_tonumber(L,-arg + 1);
            }
        }
    }
}

int Enemy_yVel(lua_State *L)
{
    int arg;

    arg = lua_gettop(L);

    if(arg == 2)
    {
        if(lua_isnumber(L,-arg) && lua_isnumber(L,-arg + 1))
        {
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy1.yVel = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy2.yVel = (int)lua_tonumber(L,-arg + 1);
            }
            if(lua_tonumber(L,-arg) == 1)
            {
                enemy3.yVel = (int)lua_tonumber(L,-arg + 1);
            }
        }
    }
}

int Player_xVel(lua_State *L)
{
    player1.xVel = (int)lua_tonumber(L,-1);
    return 0;
}

#endif
