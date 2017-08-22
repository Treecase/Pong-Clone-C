
#ifndef BUMPER_H
#define BUMPER_H

#include <SDL2/SDL.h>

typedef struct Ball Ball;


typedef struct Bumper {

    int x, y;
    int w, h;
    int xreflect, yreflect;
    SDL_Renderer* renderer;

    void(*setpos)(struct Bumper*, int, int);
    int(*getx)(struct Bumper*);
    int(*gety)(struct Bumper*);

    void(*setsize)(struct Bumper*, int, int);
    int(*getw)(struct Bumper*);
    int(*geth)(struct Bumper*);

    void(*setreflect)(struct Bumper*, int, int);
    int(*getxreflect)(struct Bumper*);
    int(*getyreflect)(struct Bumper*);

    void(*draw)(struct Bumper*);
    void(*ai)(struct Bumper*, Ball*, int, int);
} Bumper;

void newbumper (Bumper*, SDL_Renderer*, int, int, int, int, int, int);


#endif
