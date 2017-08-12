
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util.h"


int init() {
    int value = 0;

    if (SDL_Init (SDL_INIT_VIDEO)) {
        SDL_Log ("SDL_Init failed: %s\n", SDL_GetError());
        value = 1;
    }
    return value;
}

int cleanup (SDL_Renderer* r, SDL_Window* w) {

    SDL_DestroyRenderer (r);
    r = NULL;
    SDL_DestroyWindow (w);
    w = NULL;

    SDL_Quit();
}
