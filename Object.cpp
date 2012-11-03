#include "Object.h"

extern lua_State *L;

cObject::cObject(const char *filename,int x,int y,int w,int h,int xvel,const char*Script)
{
    image = SDL_LoadBMP(filename);
    box.x = x;
    box.y = y;
    box.h = h;
    box.w = w;
    script = Script;
}

cObject::~cObject()
{
    SDL_FreeSurface(image);
}

SDL_Rect *cObject::getRect()
{
    return &box;
}

void cObject::RunScript()
{
    luaL_dofile(L,script);
}

void cObject::Show(SDL_Rect camera)
{
    SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,255,255));
    SDL_Rect rect = {box.x - camera.x, box.y - camera.y};
    SDL_BlitSurface(image,NULL,SDL_GetVideoSurface(),&rect);
}
