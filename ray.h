#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct {
    point orig;
    vec3 dir;
} ray;

//Constructor
static inline ray ray_create(point origin, vec3 direction){
    ray r;
    r.orig = origin;
    r.dir = direction;
    return r;
}

static inline point ray_getorig(const ray* r){
    return r->orig;
}

static inline vec3 ray_getdir(const ray* r){
    return r->dir;
}

//compute point at parameter t
static inline point ray_at(const ray *r, double t){
    return vec3_add_assign(r->orig, vec3_mul_assign(r->dir, t));
}

#endif
