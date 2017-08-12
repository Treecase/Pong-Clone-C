
#ifndef BUMPER_H
#define BUMPER_H

#include <SDL2/SDL.h>


typedef struct bumper_struct {

    int x, y;
    int width, height;
    SDL_Rect* rect;
    SDL_Renderer* renderer;

    void(*setpos)(struct bumper_struct*, int, int);
    int(*getx)(struct bumper_struct*);
    int(*gety)(struct bumper_struct*);

    void(*setsize)(struct bumper_struct*, int, int);
    int(*getwidth)(struct bumper_struct*);
    int(*getheight)(struct bumper_struct*);

    void(*draw)(struct bumper_struct*);
} Bumper;


void bumper_setpos (Bumper*, int, int);

int bumper_getx (Bumper*);
int bumper_gety (Bumper*);

void bumper_setsize (Bumper*, int, int);

int bumper_getwidth (Bumper*);
int bumper_getheight (Bumper*);

void bumper_draw (Bumper*);

Bumper newbumper (SDL_Renderer*, int, int, int, int);


#endif
