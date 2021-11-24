#include "menu.h"
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


Menu::Menu(SDL_Texture *tTexture, SDL_Texture *o1Texture, SDL_Texture *o2Texture, SDL_Texture *o3Texture, SDL_Texture *oQuitTexture, SDL_Rect *tRect, SDL_Rect *o1Rect, SDL_Rect *o2Rect, SDL_Rect *o3Rect, SDL_Rect *oQuitRect) {
    titleTexture = tTexture;
    option1Texture = o1Texture;
    option2Texture = o2Texture;
    option3Texture = o3Texture;
    optionQuitTexture = oQuitTexture;

    titleRect = tRect;
    option1Rect = o1Rect;
    option2Rect = o2Rect;
    option3Rect = o3Rect;
    optionQuitRect = oQuitRect;

  }
  
void Menu::renderMenu()
  {
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mainRenderer);
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderCopy(mainRenderer, titleTexture, NULL, titleRect);
    SDL_RenderCopy(mainRenderer, option1Texture, NULL, option1Rect);
    SDL_RenderCopy(mainRenderer, option2Texture, NULL, option2Rect);
    SDL_RenderCopy(mainRenderer, option3Texture, NULL, option3Rect);
    SDL_RenderCopy(mainRenderer, optionQuitTexture, NULL, optionQuitRect);

    if (optionSelect == 0) {
      SDL_RenderDrawRect(mainRenderer, option1Rect);
    } else if (optionSelect == 1) {
      SDL_RenderDrawRect(mainRenderer, option2Rect);
    } else if (optionSelect == 2) {
      SDL_RenderDrawRect(mainRenderer, option3Rect);
    } else if (optionSelect == 3) {
      SDL_RenderDrawRect(mainRenderer, optionQuitRect);
    }
    
  }

void Menu::incrementOption()
  {
    optionSelect++;
    if (optionSelect > 3) {
      optionSelect = 0;
    }
  }

void Menu::decrementOption()
  {
    optionSelect--;
    if (optionSelect < 0) {
      optionSelect = 3;
    }
  }

int Menu::getOptionSelect()
  {
    return optionSelect;
  }
