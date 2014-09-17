#ifndef SHADERS_H_INCLUDED
#define SHADERS_H_INCLUDED
#include "../engine.h"

GLuint LoadShaders(char * vertex_file_path, char * fragment_file_path);
char* getShaderString(char *path, int);
#endif // SHADERS_H_INCLUDED
