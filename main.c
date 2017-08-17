/*
 * Pong clone in C using SDL2
 *
 * TODO ADD BALL MOVEMENT
 * TODO ADD BALL BOUNCES
 * TODO ADD SCORING
 *
 */

#include <stdio.h>
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

    // create the player's bumper (renderer, x, y, width, heightff)
    Bumper playerbumper;
    newbumper (&playerbumper, ren, 50, SCREEN_HEIGHT/2, 25, 75);

    Bumper enemybumper;
    newbumper (&enemybumper, ren, SCREEN_WIDTH-50, SCREEN_HEIGHT/2, 25, 75);

    // create the game ball
    Ball ball;
    newball (&ball, ren, 97, 76, 15, 15);

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
                playerbumper.setpos (&playerbumper, 50, y);
                break; }
            }
        }

        ball.movement (&ball);

        ball.checkcollisions (&ball, &playerbumper);
        ball.checkcollisions (&ball, &enemybumper);

        // set draw color to white
        SDL_SetRenderDrawColor (ren, 0xFF, 0xFF, 0xFF, 0xFF);
        // clear the screen
        SDL_RenderClear (ren);

        // draw game entities
        playerbumper.draw (&playerbumper);
        enemybumper.draw (&enemybumper);
        ball.draw (&ball);

        // render window
        SDL_RenderPresent (ren);
    }

    cleanup (ren, win);

    return 0;
}
