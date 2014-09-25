#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED
#include "../engine.h"

typedef struct _TTerrain {
    GLfloat* vertex_buffer_data;
    GLfloat* uv_buffer_data;
    GLfloat* normal_buffer_data;
    GLuint* texture;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
} TTerrain;

struct _TTerrain* tterrain_init(GLfloat* vertex_buffer_data, GLfloat* uv_buffer_data, GLuint* tex);
GLvoid tterrain_draw(struct _TTerrain*);


#endif // TERRAIN_H_INCLUDED
