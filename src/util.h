
#ifndef UTIL_H
#define UTIL_H


#include <SDL2/SDL.h>



int init();

void tex_cleanup();

void drawnumber (SDL_Renderer *, int, int);

void init_scores (SDL_Renderer *);


#endif
