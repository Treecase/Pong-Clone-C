/*
 * Bumper functions
 *
 */

#include "bumper.h"
#include "graphics.h"



/* render the bumper */
inline void draw_bumper (Bumper b) {
    draw_rect (b.x,b.y, b.w,b.h);
}

