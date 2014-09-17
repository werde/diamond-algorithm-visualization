#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "../engine.h"
struct Camera {
    vec4 pos;
    vec4 focus;
    vec4 side; //perpendicular to focus
    GLfloat yaw;
    GLfloat pitch;
    GLvoid (*focusMove)(GLfloat,GLfloat);
    GLvoid (*rotate)(GLvoid);
} Camera;

GLvoid cameraInit(GLvoid);

GLvoid cameraFocusMove(GLfloat forward, GLfloat side);
GLvoid cameraForward(GLfloat forward);
GLvoid cameraBack(GLfloat back);
GLvoid cameraStrafeLeft(GLfloat left);
GLvoid cameraStrafeRight(GLfloat right);
GLvoid cameraRotate(GLfloat yaw, GLfloat pitch);
#endif // CAMERA_H_INCLUDED
