
#ifndef BALL_H
#define BALL_H


#include "bumper.h"


typedef struct Bumper Bumper;


/* Ball:
    pong ball */
typedef struct Ball {

    double  x,y;
    int     w,h;
    double  dx,dy;
    Bumper *last_hit;
} Ball;


void draw_ball (Ball ball);
int ball_checkcollisions (Ball, Bumper);
void ball_bounce (Ball *, Bumper);


#endif

