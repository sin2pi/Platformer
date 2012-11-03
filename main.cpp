#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Player.h"
#include "Collision.h"
#include "Tile.h"
#include "Enemy.h"
#include "Particle.h"
#include "LuaFuntions.h"
#include <lua.hpp>
#include <lauxlib.h>
#include "cBullet.h"
#include "Object.h"

using namespace std;

SDL_Surface *screen;
SDL_Surface *tiles[5];
SDL_Surface *red,*green,*blue,*shimmer;
SDL_Rect camera;

cPlayer player1("Images/player.bmp",120,200,30,50,1,100);
cEnemy enemy1("Images/enemy1.bmp",900,300,41,41,1,1,50);
cEnemy enemy2("Images/enemy1.bmp",400,300,41,41,1,1,50);
cEnemy enemy3("Images/enemy1.bmp",800,700,41,41,1,1,50);
cEnemy enemy4("Images/enemy1.bmp",2300,1000,41,41,1,1,50);


int gravity = 1;
bool running = true;
int i[2] = {0,0};
int last[2] = {0,0};
int Shoot[2] = {0,0};
bool direction[2] = {0,1};
int jumpVel = 3;
bool jumping;
bool jump ;
bool dJumping;
bool DoubleJump;
int CurrentLevel = 0;
int lives = 3;
bool once2 = false;
bool once1 = false;
bool once3 = false;
bool LoadStats = false;
bool SaveStats = false;
bool fire;
int bulletAmount = 20;

TTF_Font *font;
lua_State *L = lua_open();
Particle *particles[ 40 ];

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    screen = SDL_SetVideoMode(600,450,32,SDL_SWSURFACE);
    Uint32 color = SDL_MapRGB(screen->format,45,39,12);
    SDL_Color color1 = {0,0,0};
    SDL_Surface* bulletimage=SDL_LoadBMP("Images/bullet.bmp");
    SDL_Surface* death=SDL_LoadBMP("Images/death.bmp");
    SDL_Surface* background1 = SDL_LoadBMP("Images/background1.bmp");
    blue = SDL_LoadBMP("Images/red.bmp");
    red = SDL_LoadBMP("Images/red.bmp");
    green = SDL_LoadBMP("Images/red.bmp");
    font = TTF_OpenFont("Fonts/dalila.ttf",20);
    cObject health("Images/health.bmp",400,420,25,25,1,"Scripts/health.lua");
    cObject ammo("Images/ammo.bmp",1300,530,25,25,1,"Scripts/ammo.lua");
    SDL_SetColorKey(bulletimage,SDL_SRCCOLORKEY,SDL_MapRGB(bulletimage->format,255,0,255));
    SDL_SetColorKey(red,SDL_SRCCOLORKEY,SDL_MapRGB(red->format,0,255,255));
    SDL_SetColorKey(blue,SDL_SRCCOLORKEY,SDL_MapRGB(blue->format,0,255,255));
    SDL_SetColorKey(green,SDL_SRCCOLORKEY,SDL_MapRGB(green->format,0,255,255));
    cCollision col1;
    cCollision col2;
    cCollision col3;
    cTile map1;
    cTile map2;
    cTile map3;
    col2.LoadColMap("Maps/colmap2.txt");
    col1.LoadColMap("Maps/colmap1.txt");
    map1.LoadMap("Maps/map1.txt");
    map2.LoadMap("Maps/map2.txt");
    int jum = 100;
    int spx=5;
    int spy=5;
    lua_register(L,"BulletAmount",Bullet_Amount);
    lua_register(L,"PlayerHealth",Player_SetHealth);
    lua_register(L,"PlayerPosX",Player_SetPosX);
    lua_register(L,"PlayerPosY",Player_SetPosY);
    lua_register(L,"EnemyPosX",Enemy_SetPosX);
    lua_register(L,"EnemyPosY",Enemy_SetPosY);
    lua_register(L,"EnemyHealth",Enemy_SetHealth);
    lua_register(L,"PlayerXvel",Player_xVel);
    lua_register(L,"EnemyXvel",Enemy_xVel);
    lua_register(L,"LoadScript",Load_Script);
    lua_register(L,"LoadMusic",LoadMusic);

    //create vectors
    std::vector<cBullet> bullets;	//all the bullets
    std::vector<SDL_Rect*> EnemVec1;
    std::vector<SDL_Rect*> EnemVec2;
    std::vector<SDL_Rect*> EnemVec3;
    std::vector<SDL_Rect*> EnemVec4;
    //create rects & surfaces
    SDL_Rect healthRect = {40,40};
    SDL_Rect bulletRect = {40,70};
    SDL_Surface *healthSur,*bulletSur;

    //register functions
    SDL_Rect playerRect;
    int times = 1;
    SDL_Rect rect1;
    rect1.y = 0;
    while(running)
    {

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            i[0] = 1;
                            direction[0] = 1;
                            direction[1] = false;
                            break;
                        case SDLK_RIGHT:
                            i[1] = 1;
                            direction[1] = 1;
                            direction[0] = false;
                            break;
                        case SDLK_s:

                          if(direction[0])
                  		   {
                              spx=-1;
                  			  spy=0;
                  	  	  }else if(direction[1])
                  		  {
                  		  	  spx=1;
                  			  spy=0;
                  		  }
                  		  if(bulletAmount > 0){
                  		  bullets.push_back(cBullet(spx,spy,player1.getRect()->x - camera.x,player1.getRect()->y + 25 - camera.y,3,bulletimage));
                          bulletAmount --;
                  		  }
                        break;
                        case SDLK_SPACE:
                            if(jumping == false && jump == false){
                            jumping = true;
                            jump = true;
                            jum = 100;
                            }
                            break;
                       case SDLK_m:
                           if(jumping == true){
                            DoubleJump = true;
                            jumping = false;
                            jum = 100;
                            }
                           break;
                    }break;
                case SDL_KEYUP:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            i[0] = 0;
                            last[0] = 1;
                            last[1] = 0;
                            break;
                        case SDLK_RIGHT:
                            i[1] = 0;
                            last[1] = 1;
                            last[0] = 0;
                             break;
                    }break;
            }
        }

    camera.x = player1.SetCamera(camera).x;
    camera.y = player1.SetCamera(camera).y;
    //Render & logic
    if(col2.Collision(player1.getRect(),enemy1.getRect()))
    {
        enemy1.hp = 0;
        enemy1.getRect()->x = -100;
        jumping = true;
        jump = true;
        player1.hp += 5;
    }
    if(col2.EnemyCollision(player1.getRect(),enemy1.getRect()))
    {
        if(i[0])
        {
            enemy1.getRect()->x -= player1.xVel + enemy1.xVel;
            player1.hp --;
        }
        if(i[1])
        {
            enemy1.getRect()->x += player1.xVel + enemy1.xVel;
            player1.hp --;
        }
        if(last[0])
        {
            enemy1.getRect()->x -= player1.xVel + enemy1.xVel;
            player1.hp --;
        }
        if(last[1])
        {
            enemy1.getRect()->x += player1.xVel + enemy1.xVel;
            player1.hp --;
        }
    }
    if(col2.Collision(player1.getRect(),enemy2.getRect()))
    {
        enemy2.hp = 0;
        enemy2.getRect()->x = -100;
        jumping = true;
        jump = true;
        player1.hp += 5;
    }
    if(col2.EnemyCollision(player1.getRect(),enemy2.getRect()))
    {
        if(i[0])
        {
            enemy2.getRect()->x -= player1.xVel + enemy2.xVel;
            player1.hp --;
        }
        if(i[1])
        {
            enemy3.getRect()->x += player1.xVel + enemy3.xVel;
            player1.hp --;
        }
        if(last[0])
        {
            enemy2.getRect()->x -= player1.xVel + enemy2.xVel;
            player1.hp --;
        }
        if(last[1])
        {
            enemy2.getRect()->x += player1.xVel + enemy2.xVel;
            player1.hp --;
        }
    }
    if(col2.Collision(player1.getRect(),enemy3.getRect()))
    {
        enemy3.hp = 0;
        enemy3.getRect()->x = -100;
        jumping = true;
        jump = true;
        player1.hp += 5;
    }
    if(col2.EnemyCollision(player1.getRect(),enemy3.getRect()))
    {
        if(i[0])
        {
            enemy3.getRect()->x -= player1.xVel + enemy3.xVel;
            player1.hp --;
        }
        if(i[1])
        {
            enemy3.getRect()->x += player1.xVel + enemy3.xVel;
            player1.hp --;
        }
        if(last[0])
        {
            enemy3.getRect()->x -= player1.xVel + enemy3.xVel;
            player1.hp --;
        }
        if(last[1])
        {
            enemy3.getRect()->x += player1.xVel + enemy3.xVel;
            player1.hp --;
        }
    }
   if(col2.EnemyCollision(player1.getRect(),enemy4.getRect()))
    {
        if(i[0])
        {
            enemy4.getRect()->x -= player1.xVel + enemy4.xVel;
            player1.hp --;
        }
        if(i[1])
        {
            enemy4.getRect()->x += player1.xVel + enemy4.xVel;
            player1.hp --;
        }
        if(last[0])
        {
            enemy4.getRect()->x -= player1.xVel + enemy4.xVel;
            player1.hp --;
        }
        if(last[1])
        {
            enemy4.getRect()->x += player1.xVel + enemy4.xVel;
            player1.hp --;
        }
    }
    if(col2.Collision(player1.getRect(),enemy4.getRect()))
    {
        enemy4.hp = 0;
        enemy4.getRect()->x = -100;
        jumping = true;
        jump = true;
        player1.hp += 5;
    }
    enemy1.getRect()->y += gravity;
    enemy2.getRect()->y += gravity;
    enemy3.getRect()->y += gravity;
    enemy4.getRect()->y += gravity;
    if(jumping == true && jump == true)
    {
        jum -= jumpVel;
        player1.getRect()->y -= jumpVel;
        if(jum <= -20)
        {
            jum = 100;
            jump = false;
        }
    }
    if(jumping == false && DoubleJump == true)
    {
        jum -= jumpVel;
        player1.getRect()->y -= jumpVel;
        if(jum <= -20)
        {
            jum = 100;
            DoubleJump = false;
            jump = true;
        }
    }
    if(CurrentLevel == 0)
    {
        CurrentLevel ++;
    }

    /// Level 1
    if(CurrentLevel == 1)
    {
      if(once1 == false)
      {
          player1.getRect()->x = 200;
          player1.getRect()->y = 400;
          enemy1.hp = 5;
          enemy2.hp = 5;
          enemy3.hp = 5;
          enemy1.getRect()->x = 900;
          enemy1.getRect()->y = 300;
          enemy2.getRect()->x = 400;
          enemy2.getRect()->y = 300;
          enemy3.getRect()->x = 800;
          enemy3.getRect()->y = 700;
          enemy4.getRect()->x = 2300;
          enemy4.getRect()->y = 1000;
          tiles[0] = SDL_LoadBMP("Images/tile1.bmp");
          tiles[1] = SDL_LoadBMP("Images/tile3.bmp");
          tiles[2] = SDL_LoadBMP("Images/tile2.bmp");
          tiles[3] = SDL_LoadBMP("Images/tile1.bmp");
          once1 = true;
      }

      if(col1.EnemyCollision(player1.getRect(),health.getRect()))
      {
          health.RunScript();
          health.getRect()->x = -100;
      }
      if(col1.EnemyCollision(player1.getRect(),ammo.getRect()))
      {
          ammo.RunScript();
          ammo.getRect()->x = -100;
      }

      SDL_Rect rec2 = {enemy2.getRect()->x - camera.x,enemy2.getRect()->y - camera.y,41,41};
      SDL_Rect rec1 = {enemy1.getRect()->x - camera.x,enemy1.getRect()->y - camera.y,41,41};
      SDL_Rect rec3 = {enemy3.getRect()->x - camera.x,enemy3.getRect()->y - camera.y,41,41};
      SDL_Rect rec4 = {enemy4.getRect()->x - camera.x,enemy4.getRect()->y - camera.y,41,41};

      EnemVec1.push_back(&rec1);
      EnemVec2.push_back(&rec2);
      EnemVec3.push_back(&rec3);
      EnemVec4.push_back(&rec4);

      col1.SetColMap(enemy1.getRect(),true,1);
      col1.SetColMap(enemy2.getRect(),true,1);
      col1.SetColMap(enemy3.getRect(),true,1);
      col1.SetColMap(enemy4.getRect(),true,1);
      col1.SetColMap(player1.getRect(),false,1);

      map1.ShowMap(tiles);

      if(enemy1.hp > 1)
      {
          enemy1.Movement(900,1000);
          enemy1.Show(camera);
      }
      if(enemy2.hp > 1)
      {
          enemy2.Movement(270,330);
          enemy2.Show(camera);
      }
      if(enemy3.hp > 0)
      {
          enemy3.Movement(900,1000);
          enemy3.Show(camera);
      }
      if(enemy4.hp > 0)
      {
          enemy4.Movement(2300,2400);
          enemy4.Show(camera);
      }

    if(player1.hp > 0)
      {
          player1.Move(i);
          for(int i=0;i<bullets.size();i++)
          {
          	  int enem1 = bullets[i].update(EnemVec1);
          	  int enem2 = bullets[i].update(EnemVec2);
          	  int enem3 = bullets[i].update(EnemVec3);
          	  int enem4 = bullets[i].update(EnemVec4);
        	  if(enem1 == -2 )
        	  {
        		 //out of the screen
                bullets.erase(bullets.begin()+i);
        	  }
              if(enem1 >= 0)
        	  {
        	      enemy1.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy1.ShowParticle(camera);
        	      if(enemy1.hp <= 1)
        	      enemy1.getRect()->x = -100;
        	  }
              if(enem2 >= 0)
        	  {
        	      enemy2.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy2.ShowParticle(camera);
        	      if(enemy2.hp <= 1)
        	      enemy2.getRect()->x = -100;
        	  }
              if(enem3 >= 0)
        	  {
        	      enemy3.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy3.ShowParticle(camera);
        	      if(enemy3.hp <= 1)
        	      enemy3.getRect()->x = -100;
        	  }
              if(enem4 >= 0)
        	  {
        	      enemy4.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy4.ShowParticle(camera);
        	      if(enemy4.hp <= 1)
        	      enemy4.getRect()->x = -100;
        	  }
            bullets[i].show();
        }
        player1.Show(camera);

      }

      health.Show(camera);
      ammo.Show(camera);


      if(col2.EnemyCollision(player1.getRect(),enemy2.getRect()) || col2.EnemyCollision(player1.getRect(),enemy1.getRect()) || col2.EnemyCollision(player1.getRect(),enemy3.getRect()) || col2.EnemyCollision(player1.getRect(),enemy4.getRect()))
      {
         player1.ShowParticle(camera);
      }
    }

    ///Level 2
    if(CurrentLevel == 2)
    {
      if(once2 == false)
      {
          player1.getRect()->x = 100;
          player1.getRect()->y = 320;
          enemy1.hp = 5;
          enemy2.hp = 5;
          enemy3.hp = 5;
          enemy1.getRect()->x = 900;
          enemy1.getRect()->y = 300;
          enemy2.getRect()->x = 400;
          enemy2.getRect()->y = 300;
          enemy3.getRect()->x = 800;
          enemy3.getRect()->y = 700;
          enemy4.getRect()->x = 2300;
          enemy4.getRect()->y = 1000;
          tiles[0] = SDL_LoadBMP("Images/tile1.bmp");
          tiles[1] = SDL_LoadBMP("Images/tile3.bmp");
          tiles[2] = SDL_LoadBMP("Images/tile2.bmp");
          tiles[3] = SDL_LoadBMP("Images/tile1.bmp");
          once2 = true;
      }

      SDL_Rect rec2 = {enemy2.getRect()->x - camera.x,enemy2.getRect()->y - camera.y,41,41};
      SDL_Rect rec1 = {enemy1.getRect()->x - camera.x,enemy1.getRect()->y - camera.y,41,41};
      SDL_Rect rec3 = {enemy3.getRect()->x - camera.x,enemy3.getRect()->y - camera.y,41,41};
      SDL_Rect rec4 = {enemy4.getRect()->x - camera.x,enemy4.getRect()->y - camera.y,41,41};

      EnemVec1.push_back(&rec1);
      EnemVec2.push_back(&rec2);
      EnemVec3.push_back(&rec3);
      EnemVec4.push_back(&rec4);

      col2.SetColMap(enemy1.getRect(),true,1);
      col2.SetColMap(enemy2.getRect(),true,1);
      col2.SetColMap(enemy3.getRect(),true,1);
      col2.SetColMap(enemy4.getRect(),true,1);
      col2.SetColMap(player1.getRect(),false,1);

      map2.ShowMap(tiles);

      if(enemy1.hp > 1)
      {
          enemy1.Movement(900,1000);
          enemy1.Show(camera);
      }
      if(enemy2.hp > 1)
      {
          enemy2.Movement(270,330);
          enemy2.Show(camera);
      }
      if(enemy3.hp > 0)
      {
          enemy3.Movement(900,1000);
          enemy3.Show(camera);
      }
      if(enemy4.hp > 0)
      {
          enemy4.Movement(2300,2400);
          enemy4.Show(camera);
      }
      if(player1.hp > 0)
      {
          player1.Move(i);
          for(int i=0;i<bullets.size();i++)
          {
          	  int enem1 = bullets[i].update(EnemVec1);
          	  int enem2 = bullets[i].update(EnemVec2);
          	  int enem3 = bullets[i].update(EnemVec3);
          	  int enem4 = bullets[i].update(EnemVec4);
        	  if(enem1 == -2 )
        	  {
        		 //out of the screen
                bullets.erase(bullets.begin()+i);
        	  }
              if(enem1 >= 0)
        	  {
        	      enemy1.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy1.ShowParticle(camera);
        	      if(enemy1.hp <= 1)
        	      enemy1.getRect()->x = -100;
        	  }
              if(enem2 >= 0)
        	  {
        	      enemy2.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy2.ShowParticle(camera);
        	      if(enemy2.hp <= 1)
        	      enemy2.getRect()->x = -100;
        	  }
              if(enem3 >= 0)
        	  {
        	      enemy3.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy3.ShowParticle(camera);
        	      if(enemy3.hp <= 1)
        	      enemy3.getRect()->x = -100;
        	  }
              if(enem4 >= 0)
        	  {
        	      enemy4.hp --;
        	      bullets.erase(bullets.begin()+i);
        	      enemy4.ShowParticle(camera);
        	      if(enemy4.hp <= 1)
        	      enemy4.getRect()->x = -100;
        	  }
        	  bullets[i].show();
        }
          player1.Show(camera);
      }
      if(col2.EnemyCollision(player1.getRect(),enemy2.getRect()) || col2.EnemyCollision(player1.getRect(),enemy1.getRect()) || col2.EnemyCollision(player1.getRect(),enemy3.getRect()) || col2.EnemyCollision(player1.getRect(),enemy4.getRect()))
      {
         player1.ShowParticle(camera);
      }
    }

    char c[5];
    char d[5];
    sprintf(c,"HP: %d",player1.hp);
    healthSur = TTF_RenderText_Solid(font,c,color1);
    sprintf(d,"Bullets: %d",bulletAmount);
    bulletSur = TTF_RenderText_Solid(font,d,color1);
    SDL_BlitSurface(bulletSur,NULL,screen,&bulletRect);
    SDL_BlitSurface(healthSur,NULL,screen,&healthRect);
    SDL_FreeSurface(healthSur);
    SDL_FreeSurface(bulletSur);

    if(player1.hp < 20)
    {
        SDL_SetAlpha(death,SDL_SRCALPHA,200);
        SDL_BlitSurface(death,NULL,screen,NULL);
    }

    SDL_Flip(screen);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
