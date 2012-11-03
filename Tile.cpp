#include "Tile.h"

extern SDL_Rect camera;

cTile::cTile()
{

}

void cTile::LoadMap(const char *filename)
{
    LoadCounterX = 0;
    LoadCounterY = 0;
    ifstream openfile (filename);
    if(openfile.is_open());
    {
        while(!openfile.eof())
        {
            if(once == false)
            {
                openfile >> mapSizeX >> mapSizeY;
                once = true;
            }
            openfile >> map[LoadCounterX][LoadCounterY];
            LoadCounterX ++;
            if(LoadCounterX >= mapSizeX)
            {
                LoadCounterX = 0;
                LoadCounterY ++;
            }
        }
    }
}

void cTile::ShowMap(SDL_Surface *tiles[])
{
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
		    SDL_Rect rect;
		    rect.x = i*30 - camera.x;
		    rect.y = j*30 - camera.y;
            SDL_BlitSurface(tiles[map[i][j]],NULL,SDL_GetVideoSurface(),&rect);
		}
	}
}
