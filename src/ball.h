
#ifndef BALL_H
#define BALL_H


#include "bumper.h"


typedef struct Bumper Bumper;


typedef struct Ball {

    int x, y;
    int w, h;
    double dx, dy;
    Bumper *last_hit;

    SDL_Renderer *ren;
} Ball;


void draw_ball (Ball ball);
int ball_checkcollisions (Ball, Bumper);


#endif

