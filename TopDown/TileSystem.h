#ifndef TILESYSTEM_H_INCLUDED
#define TILESYSTEM_H_INCLUDED

#include <SDL/SDL.h>
#include <fstream>
#include "Globals.h"
#include "cCollision.h"

using namespace std;

class cTile : public cCollision
{
    public:

    cTile();
    ~cTile();

    int mapSizeX,mapSizeY;
    int map[100][100];
    int LoadCounterX,LoadCounterY;

    bool once;

    void LoadMap(const char *filename);
    void RenderMap(SDL_Surface *screen,SDL_Surface *tiles[]);
    void SetCollisionMap(SDL_Rect *rect,int *i, int playerSpeed);

};

#endif // TILESYSTEM_H_INCLUDED
