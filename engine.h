#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#define SQUARE_SIZE 513
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <SOIL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "./engine/glm.h"
#include "./engine/linearAlg.h"
#include "./engine/shaders.h"
#include "./engine/camera.h"
#include "./engine/polygon.h"
#include "./engine/terrain.h"

GLvoid init(float** vd_array, float* terrain_vd_array, int size);
GLvoid display(GLvoid);
GLvoid updateMVP();
GLvoid loadTexture(char* path, GLuint* texture);

struct _TTerrain* terrain;
GLuint texture1, texture2, texture3, TextureID;
int mouse_x, mouse_y;
#endif // ENGINE_H_INCLUDED
