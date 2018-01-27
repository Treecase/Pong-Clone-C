/*
 * Pong clone in C using SDL2
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ball.h"
#include "bumper.h"
#include "consts.h"
#include "util.h"


// define global variables
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



/* pong */
int main (int argc, char* argv[]) {


    /* init vars */
    int leftscore, rightscore;
    SDL_Window *win;
    SDL_Renderer *ren;
    Bumper enemy, player;
    Ball ball;

    double ENEMYSPEED = 1.0;
    int DIFFICULTY = 15;


    for (int i = 1; i < argc; ++i) {
        if (!strcmp (argv[i], "-d") && i+1 < argc)
            DIFFICULTY = atoi (argv[++i]);
        else if (!strcmp (argv[i], "-h"))
            return print_usage (argv[0]);
        else
            return print_usage (argv[0]);
    }

    /* libs init */
    if (!init())
        return 1;

    /* init vars */
    leftscore = rightscore = 0;

    win = SDL_CreateWindow ("Pong", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!win)
        SDL_Log ("Failed to create window: %s\n", SDL_GetError());

    ren = SDL_CreateRenderer (win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren)
        SDL_Log ("Failed to create renderer: %s\n", SDL_GetError());

    init_scores (ren);

    player.x = 50;
    player.y = SCREEN_HEIGHT/2;
    player.w = 15;
    player.h = 75;
    player.renderer = ren;

    enemy.x = SCREEN_WIDTH - 50;
    enemy.y = SCREEN_HEIGHT/2;
    enemy.w = 15;
    enemy.h = 75;
    enemy.renderer = ren;

    ball.x = SCREEN_WIDTH/2;
    ball.y = SCREEN_HEIGHT/2;
    ball.w = ball.h = 15;
    ball.dx = 1;
    ball.dy = 0;
    ball.ren = ren;


    // main loop
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        // event handling
        while (SDL_PollEvent (&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = 1;
                break;

            case SDL_MOUSEMOTION:
                player.y = e.motion.y - player.h/2;
                break;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                case 'q':
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                }
                break;
            }
        }

        SDL_SetRenderDrawColor (ren, 0, 0, 0, 255);
        SDL_RenderClear (ren);


        if (enemy.y != (ball.y - enemy.h/2) + ball.h/2)
            enemy.y -= ENEMYSPEED *
                (enemy.y - ball.y + enemy.h/2 - ball.h/2) / DIFFICULTY;


        if (ball.x >= SCREEN_WIDTH
         || ball.y >= SCREEN_HEIGHT+50 || ball.y < -50) {
            leftscore++;
            ball.dx = -ball.dx;
            ball.dy = 0;
            ball.x = SCREEN_WIDTH / 2;
            ball.y = SCREEN_HEIGHT / 2;
            ball.last_hit = NULL;
        }
        if (ball.x < 0) {
            rightscore++;
            ball.dx = -ball.dx;
            ball.dy = 0;
            ball.x = SCREEN_WIDTH / 2;
            ball.y = SCREEN_HEIGHT / 2;
            ball.last_hit = NULL;
        }
        if (ball.y >= SCREEN_HEIGHT || ball.y < 0
         || ball.y + ball.h >= SCREEN_HEIGHT || ball.y + ball.h < 0) {
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

            drawnumber (ren, leftscore, LEFT);
            drawnumber (ren, rightscore, RIGHT);

            SDL_RenderPresent (ren);
            SDL_Delay (3);
        }
    }

    tex_cleanup();
    SDL_DestroyRenderer (ren);
    SDL_DestroyWindow (win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
