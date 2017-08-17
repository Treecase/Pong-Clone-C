
#ifndef BUMPER_H
#define BUMPER_H

#include <SDL2/SDL.h>


typedef struct Bumper {

    int x, y;
    int w, h;
    SDL_Renderer* renderer;

    void(*setpos)(struct Bumper*, int, int);
    int(*getx)(struct Bumper*);
    int(*gety)(struct Bumper*);

    void(*setsize)(struct Bumper*, int, int);
    int(*getw)(struct Bumper*);
    int(*geth)(struct Bumper*);

    void(*draw)(struct Bumper*);
} Bumper;


void bumper_setpos (Bumper*, int, int);

int bumper_getx (Bumper*);
int bumper_gety (Bumper*);

void bumper_setsize (Bumper*, int, int);

int bumper_getw (Bumper*);
int bumper_geth (Bumper*);

void bumper_draw (Bumper*);

void newbumper (Bumper*, SDL_Renderer*, int, int, int, int);


#endif
