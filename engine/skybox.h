#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED
#include "../engine.h"
GLvoid skyboxLoad(GLvoid);
struct Skybox {
    GLuint top;
    GLuint bottom;
    GLuint left;
    GLuint right;
    GLuint front;
    GLuint back;
    GLfloat* vertices;
    GLfloat* texCoords;
    GLuint vertexBuffer;
    GLuint UVbuffer;
    GLvoid (*drawSkybox)(GLvoid);
} Skybox;


#endif // SKYBOX_H_INCLUDED
