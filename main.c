/*
 * Pong clone in C using SDL2
 *
 * TODO FINISH BALL MOVEMENT
 * TODO ADD SCORING
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ball.h"
#include "bumper.h"
#include "consts.h"
#include "util.h"


int main() {

    if (init()) return 1;

    SDL_Window* win = SDL_CreateWindow ("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* ren = SDL_CreateRenderer (win, -1, SDL_RENDERER_ACCELERATED);

    // create the player's bumper
    int bumpersections = 3;
    int size = 75/bumpersections;

    Bumper bumper[bumpersections];
    for (int i = 0; i < bumpersections; i++) {
        Bumper bump;
        // renderer, x, y, width, height, xreflect, yreflect
        newbumper (&bump, ren, 50, (SCREEN_HEIGHT/2) - (size) + (size * i), 25, size, 1, bumpersections/2 - i);
        bumper[i] = bump;
    }

    Bumper enemybumper;
    newbumper (&enemybumper, ren, SCREEN_WIDTH-50, SCREEN_HEIGHT/2, 25, 75, 1, 1);

    // create the game ball
    Ball ball;
    newball (&ball, ren, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 15, 15);

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent (&e)) {
            switch (e.type) {
                case SDL_QUIT:
                quit = 1;
                break;

                case SDL_MOUSEMOTION: {
                int x, y;
                SDL_GetMouseState (&x, &y);
                for (int i = 0; i < bumpersections; i++) {
                    bumper[i].setpos (&bumper[i], 50, (y - size) + (size * i));
                }
                break; }
            }
        }

        // check for collisions
        for (int i = 0; i < bumpersections; i++) {
            ball.checkcollisions (&ball, &bumper[i]);
        }
        ball.checkcollisions (&ball, &enemybumper);

        // move the ball
        ball.movement (&ball);

        // set draw color to white
        SDL_SetRenderDrawColor (ren, 0xFF, 0xFF, 0xFF, 0xFF);
        // clear the screen
        SDL_RenderClear (ren);

        // draw game entities
        for (int i = 0; i < bumpersections; i++) {
            bumper[i].draw (&bumper[i]);
        }
        enemybumper.draw (&enemybumper);
        ball.draw (&ball);

        // render window
        SDL_RenderPresent (ren);
    }

    cleanup (ren, win);

    return 0;
}
