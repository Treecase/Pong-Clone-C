
#include <SDL2/SDL.h>

#include "bumper.h"



/* render the bumper */
void draw_bumper (Bumper b) {

    SDL_Rect r = { b.x, b.y, b.w, b.h };

    SDL_SetRenderDrawColor (b.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect (b.renderer, &r);
}

