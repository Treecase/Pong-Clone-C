
#ifndef CONSTS_H
#define CONSTS_H



const static int WIDTH  = 640;
const static int HEIGHT = 480;
/* why are these extern? */
extern int GAME_SPEED;

/* directions (why?) */
enum {
    LEFT = 1,
    RIGHT,
    TOP,
    BOTTOM
};


#endif

