#include "TileSystem.h"

cTile::cTile(){}

cTile::~cTile(){}

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

void cTile::RenderMap(SDL_Surface *screen,SDL_Surface *tiles[])
{
    for(int i = 0; i < mapSizeX; i++)
	{
		for(int j = 0; j < mapSizeY; j++)
		{
            SDL_Rect rect;
            rect.x = i*TileWidht;
            rect.y = j*TileHeight;
            SDL_BlitSurface(tiles[map[i][j]],NULL,screen,&rect);
		}
	}
}

void cTile::SetCollisionMap(SDL_Rect *rect,int *i, int playerSpeed)
{
    for(int l = 0; l < mapSizeX; l++)
    {
        for(int j = 0; j < mapSizeY; j++)
        {
            SDL_Rect col[map[l][j]];
            if(map[l][j] == 1)
            {
                col[map[l][j]].x = l*32;
                col[map[l][j]].y = j*32;
                col[map[l][j]].w = 32;
                col[map[l][j]].h = 32;
            }

            if(i[0] == 1)
            if(Collision(rect,&col[map[l][j]]))
            rect->y += playerSpeed;
            if(i[1] == 1)
            if(Collision(rect,&col[map[l][j]]))
            rect->x += playerSpeed;
            if(i[2] == 1)
            if(Collision(rect,&col[map[l][j]]))
            rect->y -= playerSpeed;
            if(i[3] == 1)
            if(Collision(rect,&col[map[l][j]]))
            rect->x -= playerSpeed;
        }
    }

}
