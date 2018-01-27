
#include <SDL2/SDL.h>

#include "ball.h"



/* render the ball */
void draw_ball (Ball b) {

    SDL_Rect r = { b.x, b.y, b.w, b.h };

    SDL_SetRenderDrawColor (b.ren, 255, 255, 255, 255);
    SDL_RenderFillRect (b.ren, &r);
}

/* ball_checkcollisions: check for collisions b/t
    ball and bumper*/
int ball_checkcollisions (Ball ball, Bumper bump) {

    if (((ball.x >= bump.x && ball.x <= bump.x + bump.w)
      || (ball.x+ball.w >= bump.x && ball.x + ball.w <= bump.x + bump.w))
     && ((ball.y >= bump.y && ball.y <= bump.y + bump.h)
      || (ball.y+ball.h >= bump.y && ball.y + ball.h <= bump.y + bump.h)))
        return 1;
    return 0;
}

