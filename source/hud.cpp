#include "hud.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#define BARP1X 20
#define WINDOW_WIDTH 640
#define BARP2X (WINDOW_WIDTH - (20 + BAR_WIDTH))
#define BAR_WIDTH 16


Hud::Hud(SDL_Texture *texture1, SDL_Texture *texture2, SDL_Rect *rect1, SDL_Rect *rect2, const std::string &path)
  {
    p1TextTexture = texture1;
    p2TextTexture = texture2;
    p1TextRect = rect1;
    p2TextRect = rect2;
    scoreArray[0].x = 0;
    scoreArray[0].y = 0;
    scoreArray[0].w = 24;
    scoreArray[0].h = 8;
    scoreArray[1].x = 0;
    scoreArray[1].y = 8;
    scoreArray[1].w = 24;
    scoreArray[1].h = 8;
    scoreArray[2].x = 0;
    scoreArray[2].y = 16;
    scoreArray[2].w = 24;
    scoreArray[2].h = 8;
    scoreArray[3].x = 0;
    scoreArray[3].y = 24;              
    scoreArray[3].w = 24;
    scoreArray[3].h = 8;
    scoreTexture = loadImage(path);
  } 

void Hud::renderHud()
  {
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderCopy(mainRenderer, p1TextTexture, NULL, p1TextRect);
    SDL_RenderCopy(mainRenderer, p2TextTexture, NULL, p2TextRect);
    SDL_RenderDrawRect(mainRenderer, &hudRect);
    SDL_RenderCopy(mainRenderer, scoreTexture, &scoreArray[player1Score], &p1ScoreDestRect);
    SDL_RenderCopy(mainRenderer, scoreTexture, &scoreArray[player2Score], &p2ScoreDestRect);
  }

  
SDL_Texture* Hud::loadImage(std::string path)
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

void Hud::scorePlayer1()
  {
    player1Score++;
  }

void Hud::scorePlayer2()
  {
    player2Score++;
  }

int Hud::checkScore(int ballPosition)
{
  if (ballPosition < BARP1X) {
    return 2;
  } else if (ballPosition > BARP2X) {
    return 1;
  } else {
    return 0;
  }
}
  
int Hud::checkVictory()
  {
    if (player1Score > 2) {
      return 1;
    } else if (player2Score > 2) {
      return 2;
    } else {
      return 0;
    }
  }
  

int Hud::getPlayer1Score()
  {
    return player1Score;
  }

int Hud::getPlayer2Score()
  {
    return player2Score;
  }

void Hud::resetScores()
  {
    player1Score = 0;
    player2Score = 0;
  }
  
/*
private:

  int player1Score = 0;
  int player2Score = 0;
*/

