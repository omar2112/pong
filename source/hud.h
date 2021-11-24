#ifndef HUD_H
#define HUD_H

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

/*
extern SDL_Texture* p1TextTexture;
extern SDL_Texture *p2TextTexture;
extern SDL_Rect *p1TextRect;
extern SDL_Rect *p2TextRect;
extern SDL_Rect hudRect;
extern SDL_Texture *scoreTexture;
extern SDL_Rect scoreArray[4];
extern SDL_Rect p1ScoreDestRect;
extern SDL_Rect p2ScoreDestRect;
*/

class Hud
{
public:
  
  Hud(SDL_Texture *texture1, SDL_Texture *texture2, SDL_Rect *rect1, SDL_Rect *rect2, const std::string &path);

  void renderHud();
  
  SDL_Texture* loadImage(std::string path);

  void scorePlayer1();

  void scorePlayer2();

  int checkScore(int ballPosition);
  
  int checkVictory();
  

  int getPlayer1Score();

  int getPlayer2Score();
  
  void resetScores();

  SDL_Rect scoreArray[4];
  SDL_Texture *p1TextTexture;
  SDL_Texture *p2TextTexture;
  SDL_Texture *scoreTexture;
  SDL_Rect *p1TextRect;
  SDL_Rect *p2TextRect;
  SDL_Rect hudRect = {0, 0, WINDOW_WIDTH, HUD_Y};
  SDL_Rect p1ScoreDestRect = {50, 0, 100, 50};
  SDL_Rect p2ScoreDestRect = {530, 0, 100, 50};
  

private:
  int player1Score = 0;
  int player2Score = 0;


  
};
#endif
