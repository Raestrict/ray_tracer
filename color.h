#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <stdio.h>

//#define vec3 = color;
//typedef vec3 = color;
//
//for clarity within a color context
typedef vec3 color;

static inline void write_color(FILE *out, const color *pixel_color){
    //Extract normalized channels
    double r = vec3_x(pixel_color);
    double g = vec3_y(pixel_color);
    double b = vec3_z(pixel_color);

    //Convert to 0-255 integers (use 255.999 to avoid 1.0 -> 256)
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif //COLOR_H
