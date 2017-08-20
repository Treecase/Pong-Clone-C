
#include <SDL2/SDL.h>

#include "bumper.h"
#include "consts.h"
#include "ball.h"


// set the x/y coords of the ball
void ball_setpos (Ball* b, int x, int y) {
    b->x = (x <= SCREEN_WIDTH) ? x : b->x;
    b->y = (y <= SCREEN_HEIGHT) ? y : b->y;
}

// get the x/y coords of the ball
int ball_getx (Ball* b) { return b->x; }
int ball_gety (Ball* b) { return b->y; }

// set the width/height of the ball
void ball_setsize (Ball* b, int w, int h) {
    b->w = w;
    b->h = h;
}

// get the width/height of the ball
int ball_getw (Ball* b) { return b->w; }
int ball_geth (Ball* b) { return b->h; }

// render the ball
void ball_draw (Ball* b) {

    // the rect to draw
    SDL_Rect r = { b->x - b->w/2, b->y - b->h/2, b->w, b->h };

    // store the previous draw color
    unsigned char red, green, blue, alpha;
    SDL_GetRenderDrawColor (b->ren, &red, &green, &blue, &alpha);

    // set the draw color to ball color + render balll
    SDL_SetRenderDrawColor (b->ren, 0, 0, 255, 255);
    SDL_RenderFillRect (b->ren, &r);

    // reset the draw color to the one before
    SDL_SetRenderDrawColor (b->ren, red, green, blue, alpha);
}



// checks if ball is colliding with bumper
// returns 1 if it is, 0 otherwise
int ball_checkcollisions (Ball* b, Bumper* bumperlist, int listsize) {

    for (int i = 0; i < listsize; i++) {

        // bumper variables
        int bumperx = bumperlist[i].getx (&bumperlist[i]), bumpery = bumperlist[i].gety (&bumperlist[i]);
        int bumperw = bumperlist[i].getw (&bumperlist[i]), bumperh = bumperlist[i].geth (&bumperlist[i]);

        // ball variables
        int x = b->getx (b), y = b->gety (b);
        int w = b->getw (b), h = b->geth (b);

        // bools
        int xbound = 0, ybound = 0;

        // check if the ball is within the x constraints of the bumper
        if ((x - w/2 >= bumperx - bumperw/2 && x - w/2 <= bumperx + bumperw/2) || (x + w/2 >= bumperx - bumperw/2 && x + w/2 <= bumperx + bumperw/2)) {
            xbound = 1;
        }
        // check if the ball is within the y constraints of the bumper
        if ((y - h/2 >= bumpery - bumperh/2 && y - h/2 <= bumpery + bumperh/2) || (y + h/2 >= bumpery - bumperh/2 && y + h/2 <= bumpery + bumperh/2)) {
            ybound = 1;
        }

        // reverse movement direction if there is a collision with a new bumper
        int lastcollidedinlist = 1;
        for (int n = 0; n < listsize; n++) {
            if (b->lastcollided == &bumperlist[n]) {
                lastcollidedinlist = 0;
                break;
            }
        }
        if (xbound && ybound && lastcollidedinlist) {
            b->lastcollided = &bumperlist[i];
            SDL_Log ("ball->lastcollided = %p\n", b->lastcollided);
            // change the ball's direction
            b->deltax = bumperlist[i].getxreflect (&bumperlist[i]);
            b->deltay = bumperlist[i].getyreflect (&bumperlist[i]);
            b->xdirection = -b->xdirection;
        }
    }
}


/*
// checks if ball is colliding with bumper
// returns 1 if it is, 0 otherwise
int ball_checkcollisions (Ball* b, Bumper* bumper) {

    // bumper variables
    int bumperx = bumper->getx (bumper), bumpery = bumper->gety (bumper);
    int bumperw = bumper->getw (bumper), bumperh = bumper->geth (bumper);

    // ball variables
    int x = b->getx (b), y = b->gety (b);
    int w = b->getw (b), h = b->geth (b);

    // bools
    int xbound = 0, ybound = 0;

    // check if the ball is within the x constraints of the bumper
    if ((x - w/2 >= bumperx - bumperw/2 && x - w/2 <= bumperx + bumperw/2) || (x + w/2 >= bumperx - bumperw/2 && x + w/2 <= bumperx + bumperw/2)) {
        xbound = 1;
    }
    // check if the ball is within the y constraints of the bumper
    if ((y - h/2 >= bumpery - bumperh/2 && y - h/2 <= bumpery + bumperh/2) || (y + h/2 >= bumpery - bumperh/2 && y + h/2 <= bumpery + bumperh/2)) {
        ybound = 1;
    }

    // reverse movement direction if there is a collision with a new bumper
    if (xbound && ybound && b->lastcollided != bumper) {
        b->lastcollided = bumper;
        SDL_Log ("ball->lastcollided = %p\n", b->lastcollided);
        // change the ball's direction
        b->deltax = bumper->getxreflect (bumper);
        b->deltay = bumper->getyreflect (bumper);
        b->xdirection = -b->xdirection;

        return 1;
    }
    else return 0;
}*/

// ball motion
void ball_movement (Ball* b) {

    // throttle movement speed
    static int count = 0;
    count = (count >= 8) ? 0 : count + 1;
    if (count != 0) return;

    // new coords
    int newx = b->x, newy = b->y;

    // ball bounces off of screen edges
    if (b->x >= SCREEN_WIDTH || b->x <= 0) {
        b->xdirection = -b->xdirection;
        b->lastcollided = NULL;
    }
    if (b->y >= SCREEN_HEIGHT || b->y <= 0) {
        b->ydirection = -b->ydirection;
        b->lastcollided = NULL;
    }

    // set new position
    newx = b->x + (b->deltax * b->xdirection);
    newy = b->y + (b->deltay * b->ydirection);

    // set ball's location
    b->setpos (b, newx, newy);
}

// initialize a new ball
void newball (Ball* ball, SDL_Renderer* ren, int x, int y, int w, int h) {

    // set methods
    // coord functions
    ball->setpos = ball_setpos;
    ball->getx = ball_getx;
    ball->gety = ball_gety;

    // size functions
    ball->setsize = ball_setsize;
    ball->getw = ball_getw;
    ball->geth = ball_geth;

    // main loop functions
    ball->draw = ball_draw;
    ball->checkcollisions = ball_checkcollisions;
    ball->movement = ball_movement;

    // initialize the ball's values
    ball->setpos (ball, x, y);
    ball->setsize (ball, w, h);
    ball->deltax = 1, ball->deltay = 1;
    ball->xdirection = 1, ball->ydirection = 1;
    ball->ren = ren;
}
