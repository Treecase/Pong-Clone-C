
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util.h"
#include "consts.h"


// initialize libs
int init() {
    int value = 1;

    if (SDL_Init (SDL_INIT_VIDEO)) {
        SDL_Log ("SDL_Init failed: %s\n", SDL_GetError());
        value = 0;
    }
    if (!IMG_Init (IMG_INIT_PNG)) {
        SDL_Log ("IMG_Init failed: %s\n", IMG_GetError());
        value = 0;
    }
    return value;
}

// destroy objects + shutdown libs
void cleanup (SDL_Renderer* r, SDL_Window* w) {

    SDL_DestroyRenderer (r);
    r = NULL;
    SDL_DestroyWindow (w);
    w = NULL;

    IMG_Quit();
    SDL_Quit();
}

// draw a number (for the score)
void drawnumber (SDL_Renderer* ren, int number, const int* side) {

    if (number > 9) {
        SDL_Log ("drawnumber: ERROR! Number too large [%i]", number);
        return;
    }

    // array of loaded textures
    static SDL_Texture* numbers[10];

    // free the texture array
    if (number == -1) {
        for (int i = 0; i < 10; i++)
            if (numbers[i]) SDL_DestroyTexture (numbers[i]);
    }

    // initialize texture array if not done already
    if (!numbers[9]) {
        char* imgs[10] = { "imgs/0.png", "imgs/1.png", "imgs/2.png", "imgs/3.png", "imgs/4.png", "imgs/5.png", "imgs/6.png", "imgs/7.png", "imgs/8.png", "imgs/9.png" };
        SDL_Surface* s;
        for (int i = 0; i < 10; i++) {
            s = IMG_Load (imgs[i]); if (!s) SDL_Log ("IMG_Load: %s\n", IMG_GetError());
            numbers[i] = SDL_CreateTextureFromSurface (ren, s);
            if (!numbers[i]) SDL_Log ("SDL_CreateTextureSurface: %s\n", SDL_GetError());
        }
        SDL_FreeSurface (s);
    }

    // create the rect for the texture to display
    SDL_Rect r;
    r.y = SCREEN_HEIGHT/16, r.w = 32, r.h = 64;
    if (*side == 1) r.x = SCREEN_WIDTH/8;
    if (*side == 2) r.x = SCREEN_WIDTH - (SCREEN_WIDTH/8) - 32;

    // add the texture to the render
    SDL_RenderCopy (ren, numbers[number], NULL, &r);
}
