#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#define BARP1X 20
#define WINDOW_WIDTH 640
#define BARP2X (WINDOW_WIDTH - (20 + BAR_WIDTH))
#define BAR_WIDTH 16
#define HUD_Y 50

extern SDL_Renderer *mainRenderer;

class Menu
{
public:

  Menu(SDL_Texture *tTexture, SDL_Texture *o1Texture, SDL_Texture *o2Texture, SDL_Texture *o3Texture, SDL_Texture *oQuitTexture, SDL_Rect *tRect, SDL_Rect *o1Rect, SDL_Rect *o2Rect, SDL_Rect *o3Rect, SDL_Rect *oQuitRect);
  
  void renderMenu();

  void incrementOption();
  void decrementOption();

  int getOptionSelect();



private:
  int optionSelect = 0;
  SDL_Texture *titleTexture;
  SDL_Texture *option1Texture;
  SDL_Texture *option2Texture;
  SDL_Texture *option3Texture;
  SDL_Texture *optionQuitTexture;

  SDL_Rect *titleRect;
  SDL_Rect *option1Rect;
  SDL_Rect *option2Rect;
  SDL_Rect *option3Rect;
  SDL_Rect *optionQuitRect;

};
#endif
