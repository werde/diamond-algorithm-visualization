#include "linearAlg.h"

static const double PI = 3.14159265358979323846;

mat4 multiplymat4(const mat4* m1, const mat4* m2) {
	mat4 out = IDENTITY_MATRIX;
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
		for (column = 0; column < 4; ++column)
			out.m[row_offset + column] =
				(m1->m[row_offset + 0] * m2->m[column + 0]) +
				(m1->m[row_offset + 1] * m2->m[column + 4]) +
				(m1->m[row_offset + 2] * m2->m[column + 8]) +
				(m1->m[row_offset + 3] * m2->m[column + 12]);

	return out;
}

vec4 mulmatvec4(const mat4* m, const vec4* v) {
	vec4 out;
	int i;
	for(i = 0; i < 4; ++i) {
		out.m[i] =
			(v->m[0] * m->m[i + 0]) +
			(v->m[1] * m->m[i + 4]) +
			(v->m[2] * m->m[i + 8]) +
			(v->m[3] * m->m[i + 12]);
	}

	return out;
}

void normalizevec4(vec4* v) {
	float sqr = v->m[0] * v->m[0] + v->m[1] * v->m[1] + v->m[2] * v->m[2];
	if(sqr == 1 || sqr == 0)
		return;
	float invrt = 1.f/sqrt(sqr);
	v->m[0] *= invrt;
	v->m[1] *= invrt;
	v->m[2] *= invrt;
}

float dotvec4(vec4 v1, vec4 v2) {
	return v1.m[0] * v2.m[0] + v1.m[1] * v2.m[1] + v1.m[2] * v2.m[2] + v1.m[3] * v2.m[3];
}

vec4 crossvec4(vec4 v1, vec4 v2) {
	vec4 out = {{0}};
	out.m[0] = v1.m[1]*v2.m[2] - v1.m[2]*v2.m[1];
	out.m[1] = v1.m[2]*v2.m[0] - v1.m[0]*v2.m[2];
	out.m[2] = v1.m[0]*v2.m[1] - v1.m[1]*v2.m[0];
	return out;
}

vec4 substractvec4(vec4 v1, vec4 v2){
    int i=0;
    vec4 out = {{0}};
    for (i=0;i<4;i++){
        out.m[i] = v1.m[i] - v2.m[i];
    }
    return out;
};

vec4 addvec4(vec4 v1, vec4 v2){
    int i=0;
    vec4 out = {{0}};
    for (i=0;i<4;i++){
        out.m[i] = v1.m[i] + v2.m[i];
    }
    return out;
};

void rotateX(const mat4* m, float angle) {
	mat4 rotation = IDENTITY_MATRIX;
	mat4 temp;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[5] = cosine;
	rotation.m[6] = -sine;
	rotation.m[9] = sine;
	rotation.m[10] = cosine;
    temp = multiplymat4(m, &rotation);
	memcpy(m->m, temp.m, sizeof(m->m));
}
void rotateY(const mat4* m, float angle) {
	mat4 rotation = IDENTITY_MATRIX;
	mat4 temp;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[8] = sine;
	rotation.m[2] = -sine;
	rotation.m[10] = cosine;
    temp = multiplymat4(m, &rotation);
	memcpy(m->m, temp.m, sizeof(m->m));
}
void rotateZ(const mat4* m, float angle) {
	mat4 rotation = IDENTITY_MATRIX;
	mat4 temp;
	float sine = (float)sin(angle);
	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;
	rotation.m[1] = -sine;
	rotation.m[4] = sine;
	rotation.m[5] = cosine;
    temp = multiplymat4(m, &rotation);
	memcpy(m->m, temp.m, sizeof(m->m));
}
void scale(const mat4* m, float x, float y, float z) {
	mat4 scale = IDENTITY_MATRIX;
    mat4 temp;
	scale.m[0] = x;
	scale.m[5] = y;
	scale.m[10] = z;
    temp = multiplymat4(m, &scale);
	memcpy(m->m, temp.m, sizeof(m->m));
}
void translate(const mat4* m, float x, float y, float z) {
	mat4 translation = IDENTITY_MATRIX;
    mat4 temp;
	translation.m[12] = x;
	translation.m[13] = y;
	translation.m[14] = z;
    temp = multiplymat4(m, &translation);
	memcpy(m->m, temp.m, sizeof(m->m));
}

mat4 perspective(float fovy, float aspect_ratio, float near_plane, float far_plane) {
	mat4 out = { { 0 } };

	const float
		y_scale = (float)(1/cos(fovy * PI / 360)),
		x_scale = y_scale / aspect_ratio,
		frustum_length = far_plane - near_plane;

	out.m[0] = x_scale;
	out.m[5] = y_scale;
	out.m[10] = -((far_plane + near_plane) / frustum_length);
	out.m[11] = -1;
	out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

	return out;
}

mat4 orthogonal(float left, float right, float bottom, float top) {
	mat4 out = IDENTITY_MATRIX;
	out.m[0] = 2 / (right - left);
	out.m[5] = 2 / (top - bottom);
	out.m[10] = -1;
	out.m[12] = - (right + left) / (right - left);
	out.m[13] = - (top + bottom) / (top - bottom);

	return out;
}

mat4 lookAt(vec4 pos, vec4 dir) {
	vec4 f = dir;
	normalizevec4(&f);
	vec4 u = {{0, 1, 0, 0}};
	vec4 s = crossvec4(f, u);
	normalizevec4(&s);
	u = crossvec4(s, f);

	mat4 out = IDENTITY_MATRIX;
	out.m[0] = s.x;
	out.m[4] = s.y;
	out.m[8] = s.z;

	out.m[1] = u.x;
	out.m[5] = u.y;
	out.m[9] = u.z;

	out.m[2] = -f.x;
	out.m[6] = -f.y;
	out.m[10] = -f.z;

	out.m[12] = -dotvec4(s, pos);
	out.m[13] = -dotvec4(u, pos);
	out.m[14] =  dotvec4(f, pos);
	return out;
}
