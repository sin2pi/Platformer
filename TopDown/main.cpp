#include <SDL/SDL.h>
#include <vector>
#include "Globals.h"
#include "cPlayer.h"
#include "TileSystem.h"
#include "cCollision.h"
#include "cBullet.h"

SDL_Surface *screen;
SDL_Surface *player;

int move[4] = {0,0,0,0};
int Shoot[4] = {0,0,0,0};

bool running = true;

void BlitSurface(SDL_Surface *image,SDL_Surface *screen,int x,int y)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_BlitSurface(image,NULL,screen,&rect);
}

void Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(ScreenWidht,ScreenHeight,Bbs,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Top Down Shooter",NULL);
}

typedef struct Camera
{

    float x, y;

} Camera;


int main(int argc,char *argv[])
{
    Init();
    std::vector<cBullet> bullets;	//all the bullets
    std::vector<SDL_Rect> objects; //add enemy rects (or rects, which should stop a bullet) at the end of this vector
    //if you later create a class for the enemies, you should make the type that (but change in the bullet update function too
    //you can make different for enemies and tiles, which the bullet cannot go through
    cTile map;
    cTile colmap;
    Uint32 color = SDL_MapRGB(screen->format,45,39,12);
    SDL_Rect playerRect;
    Camera cam;
    cPlayer player1(50,50,60,60,&playerRect);
    player = SDL_LoadBMP("Images/player.bmp");
    SDL_Surface* tiles[2];
    SDL_Rect bulletRect[2];
    bulletRect[0].x = playerRect.x;
    bulletRect[0].y = playerRect.y;
    bulletRect[0].w = 10;
    bulletRect[0].h = 10;
    tiles[0] = SDL_LoadBMP("Images/tile2.bmp");
    tiles[1] = SDL_LoadBMP("Images/tile1.bmp");
    SDL_Surface* bulletimage=SDL_LoadBMP("Images/bullet.bmp");
    SDL_SetColorKey(bulletimage,SDL_SRCCOLORKEY,SDL_MapRGB(bulletimage->format,255,0,255));
    map.LoadMap("Maps/map.txt");
    colmap.LoadMap("Maps/colmap.txt");
    bool direction[4]={0,0,0,1};	//top,right,bottom,left, this is where the player looks
   	int spx=0;
    int spy=0;
    while(running)
    {
       SDL_Event event;
       while (SDL_PollEvent(&event))
       {
         switch(event.type)
          {
            case SDL_QUIT:
                 running = false;
                 break;
            case SDL_KEYDOWN:

              switch(event.key.keysym.sym)
                {
                  case SDLK_ESCAPE:
                       return 0;
                       break;
                  case SDLK_SPACE:
                  		//determine the speed (depending, where the player looks)
                  		if(direction[0])	//up
                  		{
                  			spx=0;
                  			spy=-10;
                  		}else if(direction[1]) //left
                  		{
                  			spx=10;
                  			spy=0;
                  		}else if(direction[2]) //down
                  		{
                   			spx=0;
                  			spy=10;                 			
                  		}else	//right
                  		{
                  			spx=-10;
                  			spy=0;                  		
                  		}
											bullets.push_back(cBullet(spx,spy,playerRect.x,playerRect.y,10,bulletimage));
                       break;
                  case SDLK_UP:
                       move[0] = 1;
                       direction[0]=1;
                       direction[1]=direction[2]=direction[3]=false;
                       break;
                  case SDLK_RIGHT:
                       move[3] = 1;
                       direction[1]=1;
                       direction[0]=direction[2]=direction[3]=false;
                       Shoot[0] = 1;
                       break;
                  case SDLK_DOWN:
                       move[2] = 1;
                       direction[2]=1;
                       direction[0]=direction[1]=direction[3]=false;
                       break;
                  case SDLK_LEFT:
                       direction[3]=1;
                       direction[1]=direction[2]=direction[0]=false;
                       move[1] = 1;
                       break;

                  }
                  break;

            case SDL_KEYUP:

                switch(event.key.keysym.sym)
                {
                  case SDLK_UP:
                       move[0] = 0;
                       break;
                  case SDLK_RIGHT:
                       move[3] = 0;
                       break;
                  case SDLK_DOWN:
                       move[2] = 0;
                       break;
                  case SDLK_LEFT:
                       move[1] = 0;
                       break;
                }
                break;
       }
    }

        cam.x = playerRect.x - screen->w/2;
        cam.y = playerRect.y - screen->h/2;
        map.RenderMap(screen,tiles);
        player1.Movement(&playerRect,1);
        colmap.SetCollisionMap(&playerRect,move,1);
        //BlitSurface(player,screen,playerRect.x - cam.x,playerRect.y - cam.y);
        player1.Show(player,&playerRect);
        SDL_FillRect(screen,&bulletRect[1],color);
        
        for(int i=0;i<bullets.size();i++)
        {
        	int j=bullets[i].update(objects);
        	if(j==-2)
        	{
        		//out of the screen
        		bullets.erase(bullets.begin()+i);
        	}else if(j>=0)
        	{
        		//bullet hit the ith object, here you could decrease the enemy's health
        		bullets.erase(bullets.begin()+i);
        	}
        	bullets[i].show();
        }
        
        SDL_Flip(screen);

    }
}
