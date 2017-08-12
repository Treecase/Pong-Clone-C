
#include <SDL2/SDL.h>

#include "consts.h"
#include "ball.h"


void ball_setpos (Ball* b, int x, int y) {
    b->x = (x <= SCREEN_WIDTH) ? x : b->x;
    b->y = (y <= SCREEN_HEIGHT) ? y : b->y;
}

int ball_getx (Ball* b) { return b->x; }
int ball_gety (Ball* b) { return b->y; }

void ball_setsize (Ball* b, int w, int h) {
    b->w = w;
    b->h = h;
}

int ball_getw (Ball* b) { return b->w; }
int ball_geth (Ball* b) { return b->h; }

void ball_draw (Ball* b) {
    SDL_Rect r = { b->x - b->w/2, b->y - b->h/2, b->w, b->h };

    unsigned char red, green, blue, alpha;
    SDL_GetRenderDrawColor (b->ren, &red, &green, &blue, &alpha);

    SDL_SetRenderDrawColor (b->ren, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect (b->ren, &r);

    SDL_SetRenderDrawColor (b->ren, red, green, blue, alpha);

}

void newball (Ball* ball, SDL_Renderer* ren, int x, int y, int w, int h) {

    ball->setpos = ball_setpos;
    ball->getx = ball_getx;
    ball->gety = ball_gety;

    ball->setsize = ball_setsize;
    ball->getw = ball_getw;
    ball->geth = ball_geth;

    ball->draw = ball_draw;

    ball->setpos (ball, x, y);
    ball->setsize (ball, w, h);

    ball->ren = ren;
}
