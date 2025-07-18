#include "SDL.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH 800
#define IMAGE_HEIGHT ((int)(IMAGE_WIDTH / ASPECT_RATIO))
#define VIEWPORT_HEIGHT 2.0
#define VIEWPORT_WIDTH ((int)(VIEWPORT_HEIGHT) * (double)(IMAGE_WIDTH / IMAGE_HEIGHT))

// always return black for now
color ray_color(const ray *r) { return vec3_make(0, 0, 0); }

int main(void) {
  printf("%d", IMAGE_HEIGHT);
  printf("%f", VIEWPORT_WIDTH);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *win =
      SDL_CreateWindow("Pixel test", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, IMAGE_WIDTH, IMAGE_HEIGHT, 0);
  if (!win) {
    SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  /* You can only lock + write the window surface if it's software-driven. */
  SDL_Surface *surf = SDL_GetWindowSurface(win);

  // File Image
  FILE *fptr;
  fptr = fopen("output.ppm", "w");

  if (fptr == NULL) {
    perror("Error opening file");
    return 1;
  }
  /*Renderig

  The header for a ppm file is as follows:
  P3
  IMAGE_WIDTH IMAGE_HEIGHT
  255 #max color
  */
  printf("%d", IMAGE_HEIGHT);
  printf("%f", VIEWPORT_WIDTH);

  // Make the camera information;
  double focal_length = 1.0;
  point camera_center = vec3_make(0, 0, 0);
  // Calculating the vectors for the viewport
  vec3 viewport_u = vec3_make(VIEWPORT_WIDTH, 0, 0);
  vec3 viewport_v = vec3_make(0, -VIEWPORT_HEIGHT, 0);

  // Calculate the horizontal and vertical data vectors from pixel to pixel.
  vec3 pixel_delta_u = vec3_div_assign(&viewport_u, IMAGE_WIDTH);
  vec3 pixel_delta_v = vec3_div_assign(&viewport_v, IMAGE_HEIGHT);

  vec3_div_assign(&viewport_u, 2);
  vec3_div_assign(&viewport_v, 2);

  vec3 temp = vec3_sub(camera_center, vec3_make(0, 0, focal_length));
  temp = vec3_sub(temp, viewport_u);
  temp = vec3_sub(temp, viewport_v);

  point viewport_upper_left = temp;

  // Calculate the location of the upper left pixel.
  //point viewport_upper_left = camera_center - vec3_make(0, 0, focal_length) - vec3_div_assign(&viewport_u, 2) - vec3_div_assign(&viewport_v, 2);

  fprintf(fptr, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

  for (int j = 0; j < IMAGE_HEIGHT; ++j) {
    for (int i = 0; i < IMAGE_WIDTH; i++) {
      color pixel_color = vec3_make(((double)(i)) / (IMAGE_WIDTH - 1),
                                    ((double)(j)) / (IMAGE_HEIGHT - 1), 0.0);
      write_color(fptr, &pixel_color);
      /*double r = (double)i / (IMAGE_WIDTH - 1);
      double g = (double)j / (IMAGE_HEIGHT - 1);
      double b = 0.0;

      int ir = (int)(255.999 * r);
      int ig = (int)(255.999 * g);
      int ib = (int)(255.999 * b);

      fprintf(fptr, "%d %d %d\n", ir, ig, ib);*/

      printf("\rScanlines remaining: %d / %d", j + 1, IMAGE_HEIGHT);
      // fflush(stdout);
    }
  }
  printf("\nRendering done!\n");
  // Always fclose when you are done writing to a file.
  fclose(fptr);

  /* Main loop */
  int running = 1;
  SDL_Event e;
  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        running = 0;
    }

    /* Fill pixels: here we draw a gradient */
    Uint32 *pixels = (Uint32 *)surf->pixels;
    int pitch = surf->pitch / 4; // pitch in pixels, not bytes
    for (int y = 0; y < surf->h; y++) {
      for (int x = 0; x < surf->w; x++) {
        /* ARGB8888: A=0xFF, R=x%256, G=y%256, B=0 */
        pixels[y * pitch + x] =
            0xFF000000 | ((x & 0xFF) << 16) | ((y & 0xFF) << 8);
      }
    }

    /* Copy your new pixels to the window and show them */
    SDL_UpdateWindowSurface(win);
    SDL_Delay(16); // ~60 FPS
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
