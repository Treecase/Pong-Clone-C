
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "util.h"
#include "consts.h"


SDL_Texture* numbers[10];



// initialize libs
int init (SDL_Renderer *ren) {
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

/* initialize the number images */
void init_scores (SDL_Renderer *ren) {

    char tex_name[11];
    SDL_Surface* s;

    for (int i = 0; i < 10; ++i) {
        snprintf (tex_name, 11, "imgs/%i.png\0", i);
        s = IMG_Load (tex_name);
        if (!s)
            SDL_Log ("IMG_Load: %s\n", IMG_GetError());
        numbers[i] = SDL_CreateTextureFromSurface (ren, s);
        if (!numbers[i])
            SDL_Log ("SDL_CreateTextureSurface: %s\n", SDL_GetError());
    }
    SDL_FreeSurface (s);
}


/* cleanup number textures */
void tex_cleanup() {
    for (int i = 0; i < 10; ++i)
        SDL_DestroyTexture (numbers[i]);
}

/* draw a number (for the score) */
void drawnumber (SDL_Renderer* ren, int number, int side) {

    if (number > 9) {
        SDL_Log ("drawnumber: Warning - Number too large [%i]", number);
        return;
    }

    // create the rect for the texture to display
    SDL_Rect r;
    r.y = SCREEN_HEIGHT/16, r.w = 32, r.h = 64;
    if (side == LEFT)
        r.x = SCREEN_WIDTH/8;
    if (side == RIGHT)
        r.x = SCREEN_WIDTH - (SCREEN_WIDTH/8) - 32;

    // add the texture to the render
    SDL_RenderCopy (ren, numbers[number], NULL, &r);
}

