/*
 * Graphics functions
 *
 */

#include "util.h"
#include "graphics.h"
#include "consts.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



void load_number_imgs(void);
void free_number_imgs(void);
SDL_Texture *tex_from_img (const char *filename);


SDL_Window   *win = NULL;
SDL_Renderer *ren = NULL;
int graphics_init = 0;

SDL_Texture *number_img[10];



/* get_input:
    -- */
int get_input(void) {

    int y = 0;

    SDL_Event e;
    /* event handling */
    while (SDL_PollEvent (&e)) {
        switch (e.type) {
        case SDL_QUIT:
            return -1;
            break;

        case SDL_MOUSEMOTION:
            y = e.motion.y;
            break;

        case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case 'q':
            case SDLK_ESCAPE:
                return -1;
                break;
            }
            break;
        }
    }
    return y;
}

/* draw_frame:
    draw the frame to the screen */
void draw_frame(void) {

    SDL_RenderPresent (ren);
    SDL_SetRenderDrawColor (ren, 0x00,0x00,0x00,0x00);
    SDL_RenderClear (ren);
}

/* draw_number:
    draw a number to the screen */
void draw_number (int x, int y, int n) {

    SDL_Rect r;
    r.x = x;
    r.y = y;

    SDL_QueryTexture (number_img[n], NULL,NULL, &r.w,&r.h);
    r.w *= 10;
    r.h *= 10;

    SDL_RenderCopy (ren, number_img[n], NULL, &r);
}

/* load_number_imgs:
    load the number images */
void load_number_imgs(void) {

    char img_name[11];

    for (int i = 0; i < 10; ++i) {
        snprintf (img_name, 11, "imgs/%i.png", i);
        number_img[i] = tex_from_img (img_name);
    }
}

/* free_number_imgs:
    free the number images */
void free_number_imgs(void) {
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture (number_img[i]);
        number_img[i] = NULL;
    }
}

/* tex_from_img:
    create a texture from some image file */
SDL_Texture *tex_from_img (const char *filename) {

    SDL_Texture *tex = NULL;
    SDL_Surface *s   = NULL;

    s = IMG_Load (filename);
    if (!s)
        fatal ("IMG_Load: failed to load '%s': %s\n", filename, IMG_GetError());

    tex = SDL_CreateTextureFromSurface (ren, s);

    SDL_FreeSurface (s);
    s = NULL;

    return tex;
}

/* draw_rect:
    draw a rectangle to the screen */
void draw_rect (int x, int y, int w, int h) {

    SDL_Rect r = { x,y, w,h };

    SDL_SetRenderDrawColor (ren, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderFillRect (ren, &r);
}

/* init_graphics:
    exactly what you think */
void init_graphics(void) {

    if (!graphics_init) {
        /* init SDL stuff */
        if (SDL_Init (SDL_INIT_VIDEO))
            fatal ("failed to init SDL: %s\n", SDL_GetError());
        if (!IMG_Init (IMG_INIT_PNG))
            fatal ("failed to init SDL_image: %s\n", IMG_GetError());

        /* init window, etc. */
        win = SDL_CreateWindow ("Pong",
            SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
            WIDTH,HEIGHT,
            0);
        if (!win)
            fatal ("failed to create window: %s\n", SDL_GetError());

        ren = SDL_CreateRenderer (win, -1, SDL_RENDERER_ACCELERATED);
        if (!ren)
            fatal ("failed to create renderer: %s\n", SDL_GetError());

        load_number_imgs();

        /* for clean shutdown */
        atexit (shutdown_graphics);
        graphics_init = 1;
    }
}

/* shutdown_graphics:   
    exactly what you think */
void shutdown_graphics(void) {

    if (graphics_init) {

        free_number_imgs();

        SDL_DestroyRenderer (ren);
        ren = NULL;
        SDL_DestroyWindow (win);
        win = NULL;

        IMG_Quit();
        SDL_Quit();

        graphics_init = 0;
    }
}

