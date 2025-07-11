#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "SDL.h"

#define IMAGE_WIDTH 512
#define IMAGE_HEIGHT 512

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("SDL_Init: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "Pixel test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        IMAGE_WIDTH, IMAGE_HEIGHT,
        0
    );
    if (!win){
        SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /* You can only lock + write the window surface if it's software-driven. */
    SDL_Surface *surf = SDL_GetWindowSurface(win);

    //File Image
    FILE *fptr;
    fptr = fopen("output.ppm", "w");

    if (fptr == NULL){
        perror("Error opening file");
        return 1;
    }
    
    //Rendering
    //
    //The header for a ppm file is as follows: 
    //P3 #means colors are in ASCII
    //256 256 #height and width of the file
    //255 #max color
    fprintf(fptr, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    for (int j = 0; j < IMAGE_HEIGHT; ++j){
        for (int i = 0; i < IMAGE_WIDTH; i++){
            double r = (double)i / (IMAGE_WIDTH - 1);
            double g = (double)j / (IMAGE_HEIGHT - 1);
            double b = 0.0;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            fprintf(fptr, "%d %d %d\n", ir, ig, ib);

            printf("\rScanlines remaining: %d / %d", j+1, IMAGE_HEIGHT);
            fflush(stdout);
        }
    }
    printf("\nRendering done!\n");
    //Always fclose when you are done writing to a file.
    fclose(fptr);

      /* Main loop */
    int running = 1;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
        }

        /* Fill pixels: here we draw a gradient */
        Uint32 *pixels = (Uint32 *)surf->pixels;
        int pitch = surf->pitch / 4;  // pitch in pixels, not bytes
        for (int y = 0; y < surf->h; y++) {
            for (int x = 0; x < surf->w; x++) {
                /* ARGB8888: A=0xFF, R=x%256, G=y%256, B=0 */
                pixels[y * pitch + x] = 
                  0xFF000000 | ((x & 0xFF) << 16) | ((y & 0xFF) << 8);
            }
        }

        /* Copy your new pixels to the window and show them */
        SDL_UpdateWindowSurface(win);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
    
    return 0;
}
