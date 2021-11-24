#include "newbar.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BAR_WIDTH 16
#define BAR_HEIGHT 40
#define HUD_Y 50
#define BARP1X 20
#define BARP2X (WINDOW_WIDTH - (20 + BAR_WIDTH))

newBar::newBar(int x, int initY, const std::string &path)
  {
    barTexture = loadImage(path);
    initX = x;
    barRect.x = x;
    barRect.y = 240;
    barRect.w = BAR_WIDTH;
    barRect.h = BAR_HEIGHT;

  }

void newBar::rotateRight()
  {
    degrees += 10;
  }

void newBar::rotateLeft()
  {
    degrees -= 10;
  }

void newBar::renderBar()
  {
    SDL_RenderCopyEx(mainRenderer, barTexture, NULL, &barRect, degrees, NULL, flip);

  }

  
void newBar::moveBar(SDL_Event &event)
  {
    if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP) {
      barRect.y -= barVelY;
    } else if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN) {
      barRect.y += barVelY;
    }
    if (barRect.y <= HUD_Y) {
      barRect.y = HUD_Y;
    }
  }

void newBar::moveBarEvil(int ballPosY)
  {
    if (barRect.y < ballPosY) {
      barRect.y += barVelY;
    } else if (barRect.y > ballPosY) {
      barRect.y -= barVelY;
    }
    if (barRect.y <= HUD_Y) {
      barRect.y = HUD_Y;
    }
  }

void newBar::moveBarRandom()
  {
    int randomNum = rand() % 5;

    if (randomNum == 0) {

    } else if (randomNum == 3) {
       barRect.y -= barVelY;			  
    } else if (randomNum == 4) {
       barRect.y += barVelY;			  
    }

    if (barRect.y < HUD_Y) {
      barRect.y = HUD_Y;
    } else if (barRect.y > WINDOW_HEIGHT) {
      barRect.y = WINDOW_HEIGHT;
    }
      
  }

SDL_Texture* newBar::loadImage(std::string path)
  {
    SDL_Surface *tempSurface = IMG_Load(path.c_str());
    SDL_Texture *newTexture = NULL;
    if (tempSurface == NULL) {
      printf("error loading surface");
    } else {
      newTexture = SDL_CreateTextureFromSurface(mainRenderer, tempSurface);
      if (newTexture == NULL) {
	printf("error creating texture");
      }   
    }
    return newTexture;
  }

SDL_Rect newBar::getRect() {
    return barRect;
  }

void newBar::resetBar()
  {
    barRect.x = initX;
    barRect.y = 240;
  }

