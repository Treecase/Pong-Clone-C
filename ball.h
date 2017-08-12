
#ifndef BALL_H
#define BALL_H


typedef struct Ball {

    int x, y;
    int w, h;

    SDL_Renderer* ren;

    void(*setpos)(struct Ball*, int, int);
    int(*getx)(struct Ball*);
    int(*gety)(struct Ball*);

    void(*setsize)(struct Ball*, int, int);
    int(*getw)(struct Ball*);
    int(*geth)(struct Ball*);

    void(*draw)(struct Ball*);

} Ball;


void ball_setpos (Ball*, int, int);
int ball_getx (Ball*);
int ball_gety (Ball*);

void ball_setsize (Ball*, int, int);
int ball_getw (Ball*);
int ball_geth (Ball*);

void ball_draw (Ball*);

void newball (Ball*, SDL_Renderer*, int, int, int, int);


#endif
