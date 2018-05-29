/*
 * Pong clone in C using SDL2
 *
 */

#include "ball.h"
#include "bumper.h"
#include "consts.h"
#include "util.h"
#include "graphics.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

long double millis(void);

/* defined in graphics.c */
extern unsigned  SCALE;
extern unsigned  WIDTH;
extern unsigned HEIGHT;

int DIFFICULTY = 15;



/* pong */
int main (int argc, char* argv[]) {

    /* declare variables */
    int leftscore, rightscore;

    Bumper enemy, player;
    Ball ball;


    /* arg handling */
    for (int i = 1; i < argc; ++i) {
        /* -d: set difficulty */
        if (!strcmp (argv[i], "-d") && i+1 < argc)
            DIFFICULTY = atoi (argv[++i]);
        /* -s: set scaling */
        else if (!strcmp (argv[i], "-s") && i+1 < argc)
            SCALE = atoi (argv[++i]);
        /* -w: set window size */
        else if (!strcmp (argv[i], "-c") && i+2 < argc) {
             WIDTH = atoi (argv[++i]);
            HEIGHT = atoi (argv[++i]);
        }
        /* -h: print help */
        else if (!strcmp (argv[i], "-h"))
            return print_usage (argv[0]);
        /* invalid arg */
        else
            return print_usage (argv[0]);
    }

    /* init */
    init_graphics();

    /* init vars */
    leftscore = rightscore = 0;

    player = (Bumper){ .x=1,       .y=HEIGHT/2 - 5/2, .w=1, .h=5 };
    enemy  = (Bumper){ .x=WIDTH-1, .y=HEIGHT/2 - 5/2, .w=1, .h=5 };
    ball   = (Ball  ){ .x=WIDTH/2, .y=HEIGHT/2, .w=1, .h=1, .dx=0.1, .dy=0 };


    /* main loop */
    long double lastframe = millis();
    int update_screen = 0;
    int quit = 0;
    while (!quit) {

        if (get_input (&player) == -1)
            quit = 1;
        
        if (millis() - lastframe >= 0.005)
            update_screen = 1;

        if (update_screen) {

            bumper_ai (&enemy, ball);

            /*  ball went out on the right (or went out of bounds in y)
                (ie player got a point) */
            if (ball.x >= WIDTH
             || ball.y >= HEIGHT+50 || ball.y < -50) {
                leftscore++;
                ball.dx *= -1;
                ball.dy  = 0;
                ball.x   =  WIDTH / 2;
                ball.y   = HEIGHT / 2;

                ball.last_hit = NULL;
            }
            /*  ball went out on the left
                (ie enemy got a point) */
            if (ball.x < 0) {
                rightscore++;
                ball.dx *= -1;
                ball.dy  = 0;
                ball.x   =  WIDTH / 2;
                ball.y   = HEIGHT / 2;

                ball.last_hit = NULL;
            }
            /*  ball went out in y */
            if (ball.y >= HEIGHT || ball.y + ball.h < 0) {
                ball.dy *= -1;
                ball.last_hit = NULL;
            }

            /* bounce the ball off of bumpers */
            ball_bounce (&ball, enemy);
            ball_bounce (&ball, player);

            ball.x += ball.dx;
            ball.y += ball.dy / DIFFICULTY;

            if (leftscore > 9 || rightscore > 9)
                quit = 1;


            /* draw to screen */
            draw_number (2,1,       leftscore);
            draw_number (WIDTH-6,1, rightscore);

            draw_bumper (player);
            draw_bumper (enemy);
            draw_ball (ball);

            draw_frame();

            /* delay stuff */
            lastframe = millis();
            update_screen = 0;
        }
    }
    return EXIT_SUCCESS;
}

/* millis: get clock time in milliseconds */
long double millis(void) {
    struct timespec tp;
    clock_gettime (CLOCK_MONOTONIC, &tp);
    return (tp.tv_sec) + (tp.tv_nsec / 1000000000.0);
}

