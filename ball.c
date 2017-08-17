
#include <SDL2/SDL.h>

#include "bumper.h"
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

// checks if the ball is within the limits of the specified bumper
int ball_checkcollisions (Ball* b, Bumper* bumper) {
    int bumperx = bumper->getx (bumper), bumpery = bumper->gety (bumper);
    int bumperw = bumper->getw (bumper), bumperh = bumper->geth (bumper);

    int x = b->getx (b), y = b->gety (b);
    int w = b->getw (b), h = b->geth (b);

    int xbound = 0, ybound = 0;
    static int count = 0;

    if ((x - w/2 >= bumperx - bumperw/2 && x - w/2 <= bumperx + bumperw/2) || (x + w/2 >= bumperx - bumperw/2 && x + w/2 <= bumperx + bumperw/2)) {
        xbound = 1;
    }
    if ((y - h/2 >= bumpery - bumperh/2 && y - h/2 <= bumpery + bumperh/2) || (y + h/2 >= bumpery - bumperh/2 && y + h/2 <= bumpery + bumperh/2)) {
        ybound = 1;
    }

    if (xbound && ybound) {
        b->deltax = -b->deltax;
        return 1;
    }
    else return 0;
}

// ball motion
void ball_movement (Ball* b) {

    static int count = 0;
    int newx = b->x, newy = b->y;

    if (b->x >= SCREEN_WIDTH || b->x <= 0) b->deltax = -b->deltax;
//    if (b->y >= SCREEN_WIDTH || b->y <= 0) deltay = -deltay;

    if (count == 0) {
        newx = b->x + b->deltax;
//        newy = b->y + deltay;
    }

    count = (count >= 4) ? 0 : count + 1;

    b->setpos (b, newx, newy);
}

void newball (Ball* ball, SDL_Renderer* ren, int x, int y, int w, int h) {

    ball->setpos = ball_setpos;
    ball->getx = ball_getx;
    ball->gety = ball_gety;

    ball->setsize = ball_setsize;
    ball->getw = ball_getw;
    ball->geth = ball_geth;

    ball->draw = ball_draw;
    ball->checkcollisions = ball_checkcollisions;
    ball->movement = ball_movement;

    ball->setpos (ball, x, y);
    ball->setsize (ball, w, h);
    ball->deltax = 1;
    ball->deltay = 1;

    ball->ren = ren;
}
