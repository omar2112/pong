#ifndef NEWBAR_H
#define NEWBAR_H
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

extern SDL_Renderer *mainRenderer;

class newBar
{
public:

  newBar(int x, int initY, const std::string &path);
  void rotateRight();
  void rotateLeft();
  void renderBar();

  
  void moveBar(SDL_Event &event);

  void moveBarEvil(int ballPosY);

  void moveBarRandom();

  SDL_Texture* loadImage(std::string path);

  SDL_Rect getRect();
  void resetBar();

private:

  SDL_Texture* barTexture;
  SDL_Rect barRect;
  double degrees = 0;
  int barVelY = 10;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  int initX;
};
#endif
