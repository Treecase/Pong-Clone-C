
#include <SDL2/SDL.h>

#include "consts.h"
#include "bumper.h"


void bumper_setpos (Bumper* b, int x, int y) {
    b->x = (x <= SCREEN_WIDTH) ? x : b->x;
    b->y = (y <= SCREEN_HEIGHT) ? y : b->y;
}

int bumper_getx (Bumper* b) { return b->x; }
int bumper_gety (Bumper* b) { return b->y; }

void bumper_setsize (Bumper* b, int width, int height) {
    b->w = width;
    b->h = height;
}

int bumper_getw (Bumper* b) { return b->w; }
int bumper_geth (Bumper* b) { return b->h; }

void bumper_draw (Bumper* b) {
    // set the rectangle variables
    SDL_Rect r = { b->x - b->w/2, b->y - b->h/2, b->w, b->h };

    // save the previous draw colour
    unsigned char red, green, blue, alpha;
    SDL_GetRenderDrawColor (b->renderer, &red, &green, &blue, &alpha);

    // set the draw colour to red
    SDL_SetRenderDrawColor (b->renderer, 0xFF, 0x00, 0x00, 0xFF);

    // fill the rect
    SDL_RenderFillRect (b->renderer, &r);

    // set the draw colour back to the original
    SDL_SetRenderDrawColor (b->renderer, red, green, blue, alpha);
}

// create a new bumper
void newbumper (Bumper* bump, SDL_Renderer* ren, int x, int y, int width, int height) {

    bump->setpos = bumper_setpos;
    bump->getx = bumper_getx;
    bump->gety = bumper_gety;

    bump->setsize = bumper_setsize;
    bump->getw = bumper_getw;
    bump->geth = bumper_geth;

    bump->setpos (bump, x, y);
    bump->setsize (bump, width, height);

    bump->draw = bumper_draw;

    bump->renderer = ren;
}
