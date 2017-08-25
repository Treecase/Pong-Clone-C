
#include <SDL2/SDL.h>

#include "consts.h"
#include "bumper.h"
#include "ball.h"


// set x/y coords of bumper
void bumper_setpos (Bumper* b, int x, int y) {
    b->x = x;
    b->y = y;
}

// get x/y coords of bumper
int bumper_getx (Bumper* b) { return b->x; }
int bumper_gety (Bumper* b) { return b->y; }

// set width/height of bumper
void bumper_setsize (Bumper* b, int width, int height) {
    b->w = width;
    b->h = height;
}

// get the width/height of bumper
int bumper_getw (Bumper* b) { return b->w; }
int bumper_geth (Bumper* b) { return b->h; }

// set the x/y reflect of bumper
void bumper_setreflect (Bumper* b, int xreflect, int yreflect) {
    b->xreflect = xreflect;
    b->yreflect = yreflect;
}

// get the x/y reflect of bumper
int bumper_getxreflect (Bumper* b) { return b->xreflect; }
int bumper_getyreflect (Bumper* b) { return b->yreflect; }

// render the bumper
void bumper_draw (Bumper* b) {

    // set the rectangle to draw
    SDL_Rect r = { b->x - b->w/2, b->y - b->h/2, b->w, b->h };

    // store the previous draw color
    unsigned char red, green, blue, alpha;
    SDL_GetRenderDrawColor (b->renderer, &red, &green, &blue, &alpha);

    // set the draw color of bumper + render bumper
    SDL_SetRenderDrawColor (b->renderer, 255, 255, 255, 255);
    SDL_RenderFillRect (b->renderer, &r);

/*    // draw box around bumper (!!~~NOTE: FOR DEBUG~~!!)
    SDL_SetRenderDrawColor (b->renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect (b->renderer, &r);*/

    // reset the draw color
    SDL_SetRenderDrawColor (b->renderer, red, green, blue, alpha);
}

// main loop of the bumper
void bumper_ai (Bumper* b, Ball* ball, int middle, int offset, int delay) {

    static int count = 0;
    count = (count >= GAME_SPEED + delay) ? 0 : count + 1;
    if (count != 0) return;

    if (b->y < ball->gety (ball)) {
        b->setpos (b, b->x, middle + 1 + offset);
    }
    else if (b->y > ball->gety (ball)) {
        b->setpos (b, b->x, middle - 1 + offset);
    }
}

// initialize a new bumper
void newbumper (Bumper* bump, SDL_Renderer* ren, int x, int y, int width, int height, int xreflect, int yreflect) {

    // set methods
    // coord functions
    bump->setpos = bumper_setpos;
    bump->getx = bumper_getx;
    bump->gety = bumper_gety;

    // size functions
    bump->setsize = bumper_setsize;
    bump->getw = bumper_getw;
    bump->geth = bumper_geth;

    // reflect functions
    bump->setreflect = bumper_setreflect;
    bump->getxreflect = bumper_getxreflect;
    bump->getyreflect = bumper_getyreflect;

    // main loop functions
    bump->draw = bumper_draw;
    bump->ai = bumper_ai;


    // initialize bumper's variables
    bump->setpos (bump, x, y);
    bump->setsize (bump, width, height);
    bump->setreflect (bump, xreflect, yreflect);
    bump->renderer = ren;
}
