#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
    double e[3];
} vec3;

//for geometric clarity
typedef vec3 point;

//Constructors
//Zero-init
static inline vec3 vec3_zero(void) {
    vec3 v;
    v.e[0] = 0.0;
    v.e[1] = 0.0;
    v.e[2] = 0.0;
    return v;
}

//Init with explicit components
static inline vec3 vec3_make(double e0, double e1, double e2) {
    vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

//Access individual components
static inline double vec3_x(const vec3 *v) {return v->e[0]; }
static inline double vec3_y(const vec3 *v) {return v->e[1]; }
static inline double vec3_z(const vec3 *v) {return v->e[2]; }

//Negation: return -v
static inline vec3 vec3_neg(const vec3 *v) {return vec3_make(-v->e[0], -v->e[1], -v->e[2]); }

//Read index
static inline double vec3_get(const vec3 *v, int i) { return v->e[i]; }

//Write index
static inline void vec3_set(vec3 *v, int i, double value) {
    v->e[i] = value;
}

// v += u
static inline vec3 vec3_add_assign(vec3 v, vec3 u){
   v.e[0] += u.e[0];
   v.e[1] += u.e[1];
   v.e[2] += u.e[2];
   return v;
}

// v *= u
static inline vec3 vec3_mul_assign(vec3 v, double t){
   return vec3_make(v.e[0] *= t,
   v.e[1] *= t,
   v.e[2] *= t);
}

// v /= t
static inline vec3 vec3_div_assign(vec3 *v, double t){
    //Multiply by reciprocal is often faster than dividing repeatedly.
    return vec3_mul_assign(*v, 1.0 / t);
} 

// |v|^2 = e[0]^2 + e[1]^2 + e[2]^2
static inline double vec3_length_squared(const vec3 *v) {
    return v->e[0]*v->e[0] + v->e[1]*v->e[1] + v->e[2]*v->e[2];
}

// |v| = sqrt(|v|^2)
static inline double vec3_length(const vec3 *v){
    return sqrt(vec3_length_squared(v));
}

//dot product
static inline double vec3_dot(const vec3 *u, const vec3 *v){
    return u->e[0]*v->e[0] + u->e[1]*v->e[1] + u->e[2]*v->e[2];
}

//something? 
static inline vec3 vec3_cross(const vec3 *u, const vec3 *v){
    return vec3_make(
            u->e[1]*v->e[2] - u->e[2]*v->e[1],
            u->e[2]*v->e[0] - u->e[0]*v->e[2],
            u->e[0]*v->e[1] - u->e[1]*v->e[0]);
}

static inline vec3 vec3_unit(vec3 *v){
    return vec3_div_assign(v, vec3_length(v));
}

#endif //VEC3_H
