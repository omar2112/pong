#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include "game.h"
#include "hud.h"
#include "ball.h"
#include "newbar.h"
#include "menu.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define BAR_WIDTH 16
#define BAR_HEIGHT 40
#define HUD_Y 50
#define BARP1X 20
#define BARP2X (WINDOW_WIDTH - (20 + BAR_WIDTH))

SDL_Window* mainWindow = NULL;
SDL_Renderer *mainRenderer = NULL;
SDL_Rect hudRect;

SDL_Surface *p1ScoreSurface = NULL;
SDL_Texture *p1ScoreTexture = NULL;
SDL_Surface *p2ScoreSurface = NULL;
SDL_Texture *p2ScoreTexture = NULL;

Mix_Music *menuMusic = NULL;
Mix_Music *mainGameMusic = NULL;
Mix_Chunk *menuSelect = NULL;
Mix_Chunk *wallBounce = NULL;
Mix_Chunk *paddleBounce = NULL;
Mix_Chunk *playerScore = NULL;
Mix_Chunk *playerVictory = NULL;
Mix_Chunk *countdownSound = NULL;

void renderGame(Ball* mainBall, newBar* barP1, newBar* barP2, Hud* mainHud)
{
    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mainRenderer);
    SDL_SetRenderDrawColor(mainRenderer, 255, 255, 255, 255);
    mainHud->renderHud();
    barP1->renderBar();
    barP2->renderBar();
    mainBall->moveBall(barP1->getRect(), barP2->getRect());
    mainBall->renderBall(mainRenderer);
    SDL_RenderPresent(mainRenderer);
}

void resetGame(Ball *mainBall, newBar* barP1, newBar* barP2)
{
  mainBall->resetBall();
  barP1->resetBar();
  barP2->resetBar();
}

void loadImage(std::string path)
{
  p1ScoreSurface = IMG_Load(path.c_str());

  if (p1ScoreSurface == NULL) {
    printf("error loading surface");
  } else {
    p1ScoreTexture = SDL_CreateTextureFromSurface(mainRenderer, p1ScoreSurface);
    if (p1ScoreTexture == NULL) {
      printf("error creating texture");
    }   
  }
}

int main(int argc, char *argv[])
{ 
  mainWindow = SDL_CreateWindow("SDL Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0);
  SDL_RenderClear(mainRenderer);
  SDL_RenderPresent(mainRenderer);
  bool quit = false;
  SDL_Event event;
  bool menuQuit = false;
  bool closeQuit = false;

  if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
  }
  TTF_Font *mainFont;
  TTF_Font *optionFont;
  SDL_Surface *option1Surface = NULL;
  SDL_Texture *option1Texture = NULL;
  SDL_Surface *option2Surface = NULL;
  SDL_Texture *option2Texture = NULL;

  SDL_Surface *option3Surface = NULL;
  SDL_Texture *option3Texture = NULL;
  
  SDL_Surface *optionQuitSurface = NULL;
  SDL_Texture *optionQuitTexture = NULL;

  SDL_Surface *p1Surface = NULL;
  SDL_Texture *p1Texture = NULL;

  SDL_Surface *p2Surface = NULL;
  SDL_Texture *p2Texture = NULL;

  SDL_Surface *newBarSurface = NULL;
  SDL_Texture *newBarTexture = NULL;




  if (SDL_Init(SDL_INIT_AUDIO ) < 0 ) {
    printf( "SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError() );
  }

   if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
     printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
   }


  mainGameMusic = Mix_LoadMUS("../sfx/annoyedcactus__8bit-music-for-game.wav");
  if (mainGameMusic == NULL) {
    printf("audio error");
  }

  menuMusic = Mix_LoadMUS("../sfx/joshuaempyre__arcade-music-loop.wav");
  if (menuMusic == NULL) {
    printf("audio error");
  }



  menuSelect = Mix_LoadWAV("../sfx/broumbroum__sf3-sfx-menu-select.wav");
  if (menuSelect == NULL) {
    printf("audio error");
  }

  wallBounce = Mix_LoadWAV("../sfx/dland__hint.wav");
  if (wallBounce == NULL) {
    printf("audio error");
  }

  paddleBounce = Mix_LoadWAV("../sfx/owlstorm__retro-video-game-sfx-bounce.wav");
  if (paddleBounce == NULL) {
    printf("audio error");
  }

  playerScore = Mix_LoadWAV("../sfx/gabrielaraujo__powerup-success.wav");
  if (playerScore == NULL) {
    printf("audio error");
  }

  playerVictory = Mix_LoadWAV("../sfx/xtrgamr__tones-of-victory.wav");
  if (playerVictory == NULL) {
    printf("audio error");
  }

  countdownSound = Mix_LoadWAV("../sfx/paep3nguin__beep-up.wav");
  if (countdownSound == NULL) {
    printf("audio error");
  }



  
  
  mainFont = TTF_OpenFont("../gfx/magnet.ttf", 80);
  
  if (!mainFont) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }
  optionFont = TTF_OpenFont("../gfx/magnet.ttf", 20);

  if (!optionFont) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
  }
  SDL_Color whiteColor = {255, 255, 255};
  SDL_Surface *textSurface = NULL;
  SDL_Texture *textTexture = NULL;

  if (!(textSurface = TTF_RenderText_Solid(mainFont, "PONG", whiteColor))) {

  } else {
    textTexture = SDL_CreateTextureFromSurface(mainRenderer, textSurface);
  }

  if (!(option1Surface = TTF_RenderText_Solid(optionFont, "1P Game Random", whiteColor))) {

  } else {
    option1Texture = SDL_CreateTextureFromSurface(mainRenderer, option1Surface);
  }

  

  if (!(option2Surface = TTF_RenderText_Solid(optionFont, "1P Game Evil", whiteColor))) {

  } else {
    option2Texture = SDL_CreateTextureFromSurface(mainRenderer, option2Surface);
  }

  if (!(option3Surface = TTF_RenderText_Solid(optionFont, "2P Game", whiteColor))) {

  } else {
    option3Texture = SDL_CreateTextureFromSurface(mainRenderer, option3Surface);
  }

  if (!(optionQuitSurface = TTF_RenderText_Solid(optionFont, "Quit", whiteColor))) {

  } else {
    optionQuitTexture = SDL_CreateTextureFromSurface(mainRenderer, optionQuitSurface);
  }


  if (!(p1Surface = TTF_RenderText_Solid(optionFont, "P1", whiteColor))) {

  } else {
    p1Texture = SDL_CreateTextureFromSurface(mainRenderer, p1Surface);
  }

  if (!(p2Surface = TTF_RenderText_Solid(optionFont, "P2", whiteColor))) {

  } else {
    p2Texture = SDL_CreateTextureFromSurface(mainRenderer, p2Surface);
  }
  
  SDL_Rect option1Rect = {200, 200, option1Surface->w, option1Surface->h};
  SDL_Rect option2Rect = {200, 250, option2Surface->w, option2Surface->h};
  SDL_Rect option3Rect = {200, 300, option3Surface->w, option3Surface->h};
  SDL_Rect optionQuitRect = {200, 350, optionQuitSurface->w, optionQuitSurface->h};
  SDL_Rect textRect = {200, 50, textSurface->w, textSurface->h};

  Menu mainMenu(textTexture, option1Texture, option2Texture, option3Texture, optionQuitTexture, &textRect, &option1Rect, &option2Rect, &option3Rect, &optionQuitRect);
   
  SDL_Rect p1Rect = {0, 0, p1Surface->w, p1Surface->h};
  SDL_Rect p2Rect = {480, 0, p2Surface->w, p2Surface->h};
  
  Hud mainHud(p1Texture, p2Texture, &p1Rect, &p2Rect, "../gfx/bo5.png");

  SDL_Surface* ready1 = NULL;
  SDL_Surface* ready2 = NULL;
  SDL_Surface* ready3 = NULL;
  SDL_Surface* go = NULL;
  SDL_Surface* p1scores = NULL;
  SDL_Surface* p2scores = NULL;
  SDL_Surface* p1wins = NULL;
  SDL_Surface* p2wins = NULL;

  SDL_Texture* ready1Tex = NULL;
  SDL_Texture* ready2Tex = NULL;
  SDL_Texture* ready3Tex = NULL;
  SDL_Texture* goTex = NULL;
  SDL_Texture* p1scoresTex = NULL;
  SDL_Texture* p2scoresTex = NULL;
  SDL_Texture* p1winsTex = NULL;
  SDL_Texture* p2winsTex = NULL;

  
  if (!(ready1 = TTF_RenderText_Solid(optionFont, "Ready.", whiteColor))) {

  } else {
    ready1Tex = SDL_CreateTextureFromSurface(mainRenderer, ready1);
  }

  if (!(ready2 = TTF_RenderText_Solid(optionFont, "Ready..", whiteColor))) {

  } else {
    ready2Tex = SDL_CreateTextureFromSurface(mainRenderer, ready2);
  }

  if (!(ready3 = TTF_RenderText_Solid(optionFont, "Ready...", whiteColor))) {

  } else {
    ready3Tex = SDL_CreateTextureFromSurface(mainRenderer, ready3);
  }

  if (!(go = TTF_RenderText_Solid(optionFont, "GO!", whiteColor))) {

  } else {
    goTex = SDL_CreateTextureFromSurface(mainRenderer, go);
  }

  if (!(p1scores = TTF_RenderText_Solid(optionFont, "P1 Scores!", whiteColor))) {

  } else {
    p1scoresTex = SDL_CreateTextureFromSurface(mainRenderer, p1scores);
  }

  if (!(p2scores = TTF_RenderText_Solid(optionFont, "P2 Scores!", whiteColor))) {

  } else {
    p2scoresTex = SDL_CreateTextureFromSurface(mainRenderer, p2scores);
  }

  if (!(p1wins = TTF_RenderText_Solid(optionFont, "P1 Wins!", whiteColor))) {

  } else {
    p1winsTex = SDL_CreateTextureFromSurface(mainRenderer, p1wins);
  }

  if (!(p2wins = TTF_RenderText_Solid(optionFont, "P2 Wins", whiteColor))) {

  } else {
    p2winsTex = SDL_CreateTextureFromSurface(mainRenderer, p2wins);
  }


  SDL_Rect ready1rec = {200, 300, ready1->w, ready1->h};
  SDL_Rect ready2rec = {200, 300, ready2->w, ready2->h};
  SDL_Rect ready3rec = {200, 300, ready3->w, ready3->h};
  SDL_Rect gorec = {200, 300, go->w, go->h};
  SDL_Rect p1scoresrec = {200, 300, p1scores->w, p1scores->h};
  SDL_Rect p2scoresrec = {200, 300, p2scores->w, p2scores->h};
  SDL_Rect p1winsrec = {200, 300, p1wins->w, p1wins->h};
  SDL_Rect p2winsrec = {200, 300, p2wins->w, p2wins->h};
  

  Game mainGame(ready1Tex, ready2Tex, ready3Tex, goTex, p1scoresTex, p2scoresTex, p1winsTex, p2winsTex, &ready1rec, &ready2rec, &ready3rec, &gorec, &p1scoresrec, &p2scoresrec, &p1winsrec, &p2winsrec);



  newBar barP1(BARP1X, 240, "../gfx/bar.png");
  newBar barP2(BARP2X, 240, "../gfx/bar.png");

  Ball mainBall(mainWindow);

  while (!closeQuit) {
    while (!menuQuit) {
      SDL_Delay(10);
      mainMenu.renderMenu();
      SDL_RenderPresent(mainRenderer);

      if (Mix_PlayingMusic() == 0) {
	Mix_PlayMusic(menuMusic, -1);
      }
    
      while (SDL_PollEvent(&event) != 0) {
	if (event.type == SDL_QUIT) {
	  menuQuit = true;
	} else if (event.type == SDL_KEYDOWN) {
	  switch(event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    menuQuit = true;
	    closeQuit = true;
	    quit = true;
	    break;
	  case SDLK_DOWN:
	    mainMenu.incrementOption();
	    Mix_PlayChannel(-1, menuSelect, 0);
	    break;
	  case SDLK_UP:
	    mainMenu.decrementOption();
	    Mix_PlayChannel(-1, menuSelect, 0);
	    break;
	  case SDLK_RETURN:
	    menuQuit = true;
	    if (mainMenu.getOptionSelect() == 3) {
	      quit = true;
	      closeQuit = true;
	    }
	    break;
	  }
	}
      }    
    }



    Mix_HaltMusic();
    if (!closeQuit) {
      mainHud.resetScores();
      mainGame.animateCountdown();
      resetGame(&mainBall, &barP1, &barP2);
    }
    while (!quit) {
      SDL_Delay(10);
      if (Mix_PlayingMusic() == 0) {
	Mix_PlayMusic(mainGameMusic, -1);
      }

      while (SDL_PollEvent(&event) != 0) {
	if (event.type == SDL_QUIT) {
	  quit = true;
	} else if (event.type == SDL_KEYDOWN) {
	  switch (event.key.keysym.sym) {
	  case SDLK_w:
	    barP1.moveBar(event);
	    break;
	  case SDLK_s:
	    barP1.moveBar(event);
	    break;
	  case SDLK_UP:
	    if (mainMenu.getOptionSelect() == 2) {
	      barP2.moveBar(event);
	    }
	    break;
	  case SDLK_DOWN:
	    if (mainMenu.getOptionSelect() == 2) {
	      barP2.moveBar(event);
	    }
	    break;
	  case SDLK_d:
	    barP1.rotateRight();
	    break;
	  case SDLK_a:
	    barP1.rotateLeft();
	    break;
	  case SDLK_RIGHT:
	    if (mainMenu.getOptionSelect() == 2) {
	      barP2.rotateRight();
	    }
	    break;
	  case SDLK_LEFT:
	    if (mainMenu.getOptionSelect() == 2) {
	      barP2.rotateLeft();
	    }
	    break;
	  
	  case SDLK_ESCAPE:
	    quit = true;
	    break;
	  default:
	    break;
	  }
	}
      }

      if (mainMenu.getOptionSelect() == 0) {
	barP2.moveBarRandom();
      } else if (mainMenu.getOptionSelect() == 1) {
	barP2.moveBarEvil(mainBall.getBallYPos());
      }
      
      renderGame(&mainBall, &barP1, &barP2, &mainHud);
      
      if (mainHud.checkScore(mainBall.getBallLocation()) == 1) {
	printf("%u", mainHud.getPlayer1Score());
	mainHud.scorePlayer1();
	mainHud.renderHud();
	printf("%u", mainHud.getPlayer1Score());
	SDL_RenderPresent(mainRenderer);
	Mix_PauseMusic();
	Mix_PlayChannel(-1, playerScore, 0);
	if (Mix_PausedMusic() == 1) {
	  Mix_ResumeMusic();
	}
	SDL_Delay(500);
	resetGame(&mainBall, &barP1, &barP2);

      } else if (mainHud.checkScore(mainBall.getBallLocation()) == 2) {
	printf("%u", mainHud.getPlayer2Score());
	mainHud.scorePlayer2();
	printf("%u", mainHud.getPlayer2Score());
	mainHud.renderHud();
       
        SDL_RenderPresent(mainRenderer);
	
	Mix_PauseMusic();
	Mix_PlayChannel(-1, playerScore, 0);	
	if (Mix_PausedMusic() == 1) {
	  Mix_ResumeMusic();
	}
	SDL_Delay(500);
	resetGame(&mainBall, &barP1, &barP2);
	

      }

      	if (mainHud.getPlayer1Score() > 2) {
	  Mix_HaltMusic();
	  Mix_PlayChannel(-1, playerVictory, 0);
	  mainGame.animateVictory(1);
	  quit = true;
	  mainHud.resetScores();
	}

	 if (mainHud.getPlayer2Score() > 2) {
	  Mix_HaltMusic();
	  Mix_PlayChannel(-1, playerVictory, 0);
	  //SDL_Delay(2000);
	  mainGame.animateVictory(2);
	  quit = true;
	  mainHud.resetScores();
	} 

      
    } // while game quit
    //SDL_RenderClear(mainRenderer);
    Mix_HaltMusic();
    menuQuit = false;
    quit = false;
  } // while close quit



  Mix_FreeMusic(menuMusic);
  menuMusic = NULL;
  Mix_FreeMusic(mainGameMusic);
  mainGameMusic = NULL;
  Mix_FreeChunk(menuSelect);
  menuSelect = NULL;
  Mix_FreeChunk(wallBounce);
  wallBounce = NULL;
  Mix_FreeChunk(paddleBounce);
  paddleBounce = NULL;
  Mix_FreeChunk(playerScore);
  playerScore = NULL;
  Mix_FreeChunk(playerVictory);
  playerVictory = NULL;
  Mix_FreeChunk(countdownSound);
  countdownSound = NULL;
  
  SDL_DestroyWindow(mainWindow);
  SDL_DestroyRenderer(mainRenderer);
  mainWindow = NULL;
  mainRenderer = NULL;
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
  return 0;
}
