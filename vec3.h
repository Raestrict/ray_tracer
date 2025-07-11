#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
    double e[3];
} vec3;

//Constructors
static inline vec3 vec3_zero(void)
{
    return (vec3){ .e = { 0.0, 0.0, 0.0 }};
}
