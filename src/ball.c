/*
 * Ball functions
 *
 */

#include "ball.h"
#include "graphics.h"
#include "util.h"



/* render the ball */
inline void draw_ball (Ball b) {
    draw_rect (b.x, b.y, b.w, b.h);
}

/* ball_checkcollisions: check for collisions b/t
    ball and bumper*/
int ball_checkcollisions (Ball ball, Bumper bump) {

    int in_x, in_y;

    in_x = between (ball.x, bump.x, bump.x + bump.w) || between (ball.x + ball.w, bump.x, bump.x + bump.w);
    in_y = between (ball.y, bump.y, bump.y + bump.h) || between (ball.y + ball.h, bump.y, bump.y + bump.h);

    return in_x && in_y;
}

/* ball_bounce: bounce the ball off of bumpers */
void ball_bounce (Ball *ball, Bumper bump) {

    if (ball_checkcollisions (*ball, bump)) {
        ball->dx *= -1;
        ball->dy = ((ball->y+ball->h/2) - (bump.y+bump.h/2));
    }
}

