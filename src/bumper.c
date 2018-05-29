/*
 * Bumper functions
 *
 */

#include "bumper.h"
#include "ball.h"
#include "graphics.h"
#include "util.h"

#include <stdlib.h>

double ENEMYSPEED = 1.0;


/* render the bumper */
inline void draw_bumper (Bumper b) {
    draw_rect (b.x,b.y, b.w,b.h);
}

/* enemy bumper AI */
void bumper_ai (Bumper *bump, Ball ball) {

    if (ball.y < bump->y + (rand() % (bump->h/2)))
        bump->y -= ENEMYSPEED;
    else if (ball.y > (bump->y + bump->h) + (rand() % (bump->h/2)))
        bump->y += ENEMYSPEED;
}

