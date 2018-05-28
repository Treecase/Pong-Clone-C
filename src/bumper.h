
#ifndef BUMPER_H
#define BUMPER_H

typedef struct Ball Ball;


/* Bumper:
    pong bumper */
typedef struct Bumper {

    double x, y;
    int w, h;
    int xreflect, yreflect;
} Bumper;

void draw_bumper (Bumper bump);
void bumper_ai (Bumper b, Ball *ball);


#endif

