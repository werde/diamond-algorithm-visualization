#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED
#include "../engine.h"

typedef struct _TPolygon {
    GLfloat* vertex_buffer_data;
    GLfloat* uv_buffer_data;
    GLuint* texture;
    GLuint vertexbuffer;
    GLuint uvbuffer;
} TPolygon;

struct _TPolygon* tpolygon_init(GLfloat vertex_buffer_data[9], GLfloat uv_buffer_data[6], GLuint* tex);
GLvoid tpolygon_draw(struct _TPolygon*);

#endif // POLYGON_H_INCLUDED
