#ifndef CLASS_TILE
#define CLASS_TILE

#include <fstream>
#include <SDL.h>

using namespace std;

class cTile
{
    private:

    public:

          int mapSizeX,mapSizeY;
          int map[200][200];
          int LoadCounterX,LoadCounterY;

          bool once;

          cTile();

          void LoadMap(const char* filename);

          void ShowMap(SDL_Surface *tiles[]);
};

#endif
