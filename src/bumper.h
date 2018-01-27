
#ifndef BUMPER_H
#define BUMPER_H

#include <SDL2/SDL.h>

typedef struct Ball Ball;


typedef struct Bumper {

    int x, y;
    int w, h;
    int xreflect, yreflect;
    SDL_Renderer* renderer;

} Bumper;

void draw_bumper (Bumper bump);
void bumper_ai (Bumper b, Ball *ball);


#endif
