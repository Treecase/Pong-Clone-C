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



/* pong */
int main (int argc, char* argv[]) {

    /* declare variables */
    int leftscore, rightscore;

    Bumper enemy, player;
    Ball ball;

    /* what are these? */
    double ENEMYSPEED = 1.0;
    int DIFFICULTY = 15;


    /* arg handling */
    for (int i = 1; i < argc; ++i) {
        /* -d: set difficulty */
        if (!strcmp (argv[i], "-d") && i+1 < argc)
            DIFFICULTY = atoi (argv[++i]);
        /* -h: print help */
        else if (!strcmp (argv[i], "-h"))
            return print_usage (argv[0]);
        /* bad arg */
        else
            return print_usage (argv[0]);
    }

    /* init */
    init_graphics();

    /* init vars */
    leftscore = rightscore = 0;

    /* TODO get rid of this crap */
    player.x = 50;
    player.y = HEIGHT/2;
    player.w = 15;
    player.h = 75;

    enemy.x = WIDTH - 50;
    enemy.y = HEIGHT/2;
    enemy.w = 15;
    enemy.h = 75;

    ball.x = WIDTH/2;
    ball.y = HEIGHT/2;
    ball.w = ball.h = 15;
    ball.dx = 1;
    ball.dy = 0;


    /* main loop */
    int quit = 0;
    while (!quit) {

        int r;
        switch (r = get_input()) {
        case -1:
            quit = 1;
            break;

        default:
            player.y = r - player.h/2;
            break;
        }

        /* TODO get rid of _this_ crap, too */
        if (enemy.y != (ball.y - enemy.h/2) + ball.h/2)
            enemy.y -= ENEMYSPEED *
                (enemy.y - ball.y + enemy.h/2 - ball.h/2) / DIFFICULTY;


        if (ball.x >= WIDTH
         || ball.y >= HEIGHT+50 || ball.y < -50) {
            leftscore++;
            ball.dx = -ball.dx;
            ball.dy = 0;
            ball.x = WIDTH / 2;
            ball.y = HEIGHT / 2;
            ball.last_hit = NULL;
        }
        if (ball.x < 0) {
            rightscore++;
            ball.dx = -ball.dx;
            ball.dy = 0;
            ball.x = WIDTH / 2;
            ball.y = HEIGHT / 2;
            ball.last_hit = NULL;
        }
        if (ball.y >= HEIGHT || ball.y < 0
         || ball.y + ball.h >= HEIGHT || ball.y + ball.h < 0) {
            ball.dy = -ball.dy;
            ball.last_hit = NULL;
        }


        if (ball_checkcollisions (ball, enemy)) {
            ball.dx = -ball.dx;
            ball.dy = (ball.y - (enemy.y+enemy.h/2)) / DIFFICULTY;
        }
        if (ball_checkcollisions (ball, player)) {
            ball.dx = -ball.dx;
            ball.dy = (ball.y - (player.y+player.h/2)) / DIFFICULTY;
        }

        ball.x += ball.dx;
        ball.y += ball.dy;

        if (leftscore > 9 || rightscore > 9)
            quit = 1;


        if (!quit) {
            draw_bumper (player);
            draw_bumper (enemy);
            draw_ball (ball);

            draw_number (0,0,        leftscore);
            draw_number (WIDTH-64,0, rightscore);

            draw_frame();
        }
    }
    return EXIT_SUCCESS;
}

