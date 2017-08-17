
#ifndef BALL_H
#define BALL_H

#include "bumper.h"


typedef struct Ball {

    int x, y;
    int w, h;
    int deltax, deltay;

    SDL_Renderer* ren;

    void(*setpos)(struct Ball*, int, int);
    int(*getx)(struct Ball*);
    int(*gety)(struct Ball*);

    void(*setsize)(struct Ball*, int, int);
    int(*getw)(struct Ball*);
    int(*geth)(struct Ball*);

    void(*draw)(struct Ball*);
    int(*checkcollisions)(struct Ball*, Bumper*);
    void(*movement)(struct Ball*);

} Ball;

void newball (Ball*, SDL_Renderer*, int, int, int, int);


#endif
