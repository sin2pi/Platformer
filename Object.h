#ifndef CHECKPOINT_H_INCLUDED
#define CHECKPOINT_H_INCLUDED

#include <SDL.h>
extern "C"
{
#include <Lua.h>
#include <lauxlib.h>
}
class cObject
{
    private:

          SDL_Rect box;

          SDL_Surface *image;

          const char *script;

    public:

          cObject(const char *,int x,int y,int w,int h,int xvel,const char*Script);

          ~cObject();

          void RunScript();

          SDL_Rect *getRect();

          void Show(SDL_Rect camera);

};

#endif // COLLISION_H_INCLUDED
