#ifndef LINEARALG_H_INCLUDED
#define LINEARALG_H_INCLUDED
#include <math.h>

typedef struct mat4 {
	float m[16];
} mat4;

/*
0 1 2 3
4 5 6 7
8 9 A B
C D E F
*/

typedef union vec4 {
	 float m[4];
	 struct {
	 	float x, y, z, w;
	 };
} vec4;

static const vec4 X_AXIS = {{1, 0, 0, 0}};
static const vec4 Y_AXIS = {{0, 1, 0, 0}};
static const vec4 Z_AXIS = {{0, 0, 1, 0}};
static const vec4 INV_X_AXIS = {{-1, 0, 0, 0}};
static const vec4 INV_Y_AXIS = {{0, -1, 0, 0}};
static const vec4 INV_Z_AXIS = {{0, 0, -1, 0}};

static const mat4 IDENTITY_MATRIX = {{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
}};

mat4 multiplymat4(const mat4* m1, const mat4* m2);
vec4 mulmatvec4(const mat4* m, const vec4* v);
void normalizevec4(vec4* v);
float dotvec4(vec4 v1, vec4 v2);
vec4 crossvec4(vec4 v1, vec4 v2);
vec4 substractvec4(vec4 v1, vec4 v2);
vec4 addvec4(vec4 v1, vec4 v2);
void rotateX(const mat4* m, float angle);
void rotateY(const mat4* m, float angle);
void rotateZ(const mat4* m, float angle);
void scale(const mat4* m, float x, float y, float z);
void translate(const mat4* m, float x, float y, float z);

mat4 perspective(float fovy, float aspect_ratio, float near_plane, float far_plane);
mat4 orthogonal(float left, float right, float bottom, float top);

mat4 lookAt(vec4 pos, vec4 dir);
#endif // MENU_H_INCLUDED
