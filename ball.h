
#ifndef BALL_H
#define BALL_H

#include "bumper.h"


typedef struct Ball {

    int x, y;
    int w, h;
    int deltax, deltay;
    int xdirection, ydirection;
    const int* lastcollided;

    SDL_Renderer* ren;

    void(*setpos)(struct Ball*, int, int);
    int(*getx)(struct Ball*);
    int(*gety)(struct Ball*);

    void(*setsize)(struct Ball*, int, int);
    int(*getw)(struct Ball*);
    int(*geth)(struct Ball*);

    void(*draw)(struct Ball*);
    int(*checkcollisions)(struct Ball*, Bumper*, int);
    void(*movement)(struct Ball*);

    int(*main)(struct Ball*, Bumper**, int, int);
} Ball;

void newball (Ball*, SDL_Renderer*, int, int, int, int);


#endif
