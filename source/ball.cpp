#include "ball.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>

Ball::Ball(SDL_Window *window)
  {
    ballRect.x = 300;
    ballRect.y = 250;
    ballRect.w = BALL_WIDTH;
    ballRect.h = BALL_HEIGHT;
    this->ballSurface = SDL_GetWindowSurface(window);
  }


void Ball::moveBall(SDL_Rect bar1Rect, SDL_Rect bar2Rect)
  {
    
    if (SDL_HasIntersection(&ballRect, &bar1Rect)) {
      Mix_PlayChannel(-1, paddleBounce, 0);
      ballDirX = 2;
      if ((ballRect.y + (ballRect.h/2.0)) < (bar1Rect.y + 10)) {
	ballDirY = -1;
      } else if ((ballRect.y + ballRect.h/2.0) > (bar1Rect.y + 30)) {
	ballDirY = 1;
      } else if ((ballRect.y + ballRect.h/2.0) > (bar1Rect.y + 10) && (ballRect.y + ballRect.h/2.0) < (bar1Rect.h + 30)) {
	ballDirY = 0;
	printf("hit the middle");
      }
    }

    if (SDL_HasIntersection(&ballRect, &bar2Rect)) {
      Mix_PlayChannel(-1, paddleBounce, 0);
      ballDirX = -2;

      if ((ballRect.y + (ballRect.h/2.0)) < (bar2Rect.y + 10)) {
	ballDirY = -1;
      } else if ((ballRect.y + ballRect.h/2.0) > (bar2Rect.y + 30)) {
	ballDirY = 1;
      } else if ((ballRect.y + ballRect.h/2.0) > (bar2Rect.y + 10) && (ballRect.y + ballRect.h/2.0) < (bar2Rect.h + 30)) {
	ballDirY = 0;
	printf("hit the middle2");
      }
    }
    
 
    if (ballRect.y < HUD_Y || ballRect.y > WINDOW_HEIGHT) {
      Mix_PlayChannel(-1, wallBounce, 0);
      ballDirY = ballDirY * -1;
    }
    this->ballRect.x = this->ballRect.x + ballDirX;
    this->ballRect.y = this->ballRect.y + ballDirY;
    
    
  }

void Ball::renderBall(SDL_Renderer *renderer)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &this->ballRect);
    SDL_RenderFillRect(renderer, &this->ballRect);
  }

int Ball::getBallLocation()
  {
    return ballRect.x;
  }

int Ball::getBallYPos()
  {
    return ballRect.y;
  }

void Ball::resetBall()
  {
    ballRect.x = 300;
    ballRect.y = 250;
    ballDirX = -2;
    ballDirY = 0;
  }

