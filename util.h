
#include <SDL2/SDL.h>


#ifndef UTIL_H
#define UTIL_H


int init();

void cleanup (SDL_Renderer*, SDL_Window*);

void drawnumber (SDL_Renderer*, int, const int*);


#endif
