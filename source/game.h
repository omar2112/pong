#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


extern SDL_Renderer *mainRenderer;
extern Mix_Chunk *countdownSound; 

class Game
{
public:

  SDL_Texture* Ready1Tex;
  SDL_Texture* Ready2Tex;
  SDL_Texture* Ready3Tex;
  SDL_Texture* GoTex;
  SDL_Texture* Player1ScoresTex;
  SDL_Texture* Player2ScoresTex;
  SDL_Texture* Player1WinsTex;
  SDL_Texture* Player2WinsTex;

  SDL_Rect* Ready1Rect;
  SDL_Rect* Ready2Rect;
  SDL_Rect* Ready3Rect;
  SDL_Rect* GoRect;
  SDL_Rect* Player1ScoresRect;
  SDL_Rect* Player2ScoresRect;
  SDL_Rect* Player1WinsRect;
  SDL_Rect* Player2WinsRect;
 
  
  Game(SDL_Texture* ready1, SDL_Texture* ready2, SDL_Texture* ready3, SDL_Texture* go, SDL_Texture* p1scores, SDL_Texture* p2scores, SDL_Texture* p1wins, SDL_Texture* p2wins, SDL_Rect* ready1rec, SDL_Rect* ready2rec, SDL_Rect* ready3rec, SDL_Rect* gorec, SDL_Rect* p1scoresrec, SDL_Rect* p2scoresrec, SDL_Rect* p1winsrec, SDL_Rect* p2winsrec);
  
  void animateCountdown();
  
  void animateVictory(int playerNum);
  
  void animateScore(int playerNum);


private:

};

#endif
