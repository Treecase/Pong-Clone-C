/*
 * Ball functions
 *
 */

#include "ball.h"
#include "graphics.h"



/* render the ball */
inline void draw_ball (Ball b) {
    draw_rect (b.x, b.y, b.w, b.h);
}

/* ball_checkcollisions: check for collisions b/t
    ball and bumper*/
int ball_checkcollisions (Ball ball, Bumper bump) {

    /* FIXME oh, no... */
    if (((ball.x >= bump.x && ball.x <= bump.x + bump.w)
      || (ball.x+ball.w >= bump.x && ball.x + ball.w <= bump.x + bump.w))
     && ((ball.y >= bump.y && ball.y <= bump.y + bump.h)
      || (ball.y+ball.h >= bump.y && ball.y + ball.h <= bump.y + bump.h)))
        return 1;
    return 0;
}

