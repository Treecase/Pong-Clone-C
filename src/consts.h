
#ifndef CONSTS_H
#define CONSTS_H


#include <SDL2/SDL.h>



extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer *ren;
extern int GAME_SPEED;

enum {
    LEFT = 1,
    RIGHT,
    TOP,
    BOTTOM
};


#endif

