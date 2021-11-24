#ifndef BALL_H
#define BALL_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#define WINDOW_HEIGHT 480
#define HUD_Y 50


extern Mix_Chunk *paddleBounce;
extern Mix_Chunk *wallBounce;

class Ball
{
public:
  int ballVelX = 1;
  int ballVelY = 0;
  int ballDirX = -2;
  int ballDirY = 0;
  static const int BALL_WIDTH = 10;
  static const int BALL_HEIGHT = 10;
  SDL_Rect ballRect;
  SDL_Surface *ballSurface;

  Ball(SDL_Window *window);

  void moveBall(SDL_Rect bar1Rect, SDL_Rect bar2Rect);

  void renderBall(SDL_Renderer *renderer);

  int getBallLocation();
  int getBallYPos();

  void resetBall();
private:

};
#endif
