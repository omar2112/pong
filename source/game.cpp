#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

Game::Game(SDL_Texture* ready1, SDL_Texture* ready2, SDL_Texture* ready3, SDL_Texture* go, SDL_Texture* p1scores, SDL_Texture* p2scores, SDL_Texture* p1wins, SDL_Texture* p2wins, SDL_Rect* ready1rec, SDL_Rect* ready2rec, SDL_Rect* ready3rec, SDL_Rect* gorec, SDL_Rect* p1scoresrec, SDL_Rect* p2scoresrec, SDL_Rect* p1winsrec, SDL_Rect* p2winsrec)
  {
    Ready1Tex = ready1;
    Ready2Tex = ready2;
    Ready3Tex = ready3;
    GoTex = go;
    Player1ScoresTex = p1scores;
    Player2ScoresTex = p2scores;
    Player1WinsTex = p1wins;
    Player2WinsTex = p2wins;
    Ready1Rect = ready1rec;
    Ready2Rect = ready2rec;
    Ready3Rect = ready3rec;
    GoRect = gorec;
    Player1ScoresRect = p1scoresrec;
    Player2ScoresRect = p2scoresrec;
    Player1WinsRect = p1winsrec;
    Player2WinsRect = p2winsrec;

  }
  
void Game::animateCountdown()
  {
    Mix_PlayChannel(-1, countdownSound, 3);
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mainRenderer);
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderCopy(mainRenderer, Ready1Tex, NULL, Ready1Rect);
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(500);
    SDL_RenderCopy(mainRenderer, Ready2Tex, NULL, Ready2Rect);
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(500);
    SDL_RenderCopy(mainRenderer, Ready3Tex, NULL, Ready3Rect);
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(500);
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mainRenderer);
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    SDL_RenderCopy(mainRenderer, GoTex, NULL, GoRect);
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(500);
  }

void Game:: animateVictory(int playerNum)
  {
    
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mainRenderer);
    
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

    if (playerNum == 1) {
      SDL_RenderCopy(mainRenderer, Player1WinsTex, NULL, Player1WinsRect);
    } else if (playerNum == 2) {
      SDL_RenderCopy(mainRenderer, Player2WinsTex, NULL, Player2WinsRect);
    }
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(2500);
  }

void Game:: animateScore(int playerNum)
  { 
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);

    if (playerNum == 1) {
      SDL_RenderCopy(mainRenderer, Player1ScoresTex, NULL, Player1ScoresRect);
    } else if (playerNum == 2) {
      SDL_RenderCopy(mainRenderer, Player2ScoresTex, NULL, Player2ScoresRect);
    }
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(500);

  }
