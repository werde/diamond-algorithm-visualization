#include "camera.h"

GLvoid cameraInit(){
    Camera.pitch = 0;
    Camera.yaw = 0;
    vec4 pos = {{0, 0.5, 0, 0}};
	vec4 focus = {{1, 0, -1, 0}};
    normalizevec4(&focus);
	Camera.pos = pos;
    Camera.focus = focus;
    Camera.side = crossvec4(Camera.focus, Y_AXIS);
    normalizevec4(&Camera.side);
    Camera.focusMove = cameraFocusMove;
}

GLvoid cameraForward(GLfloat forward) {
    Camera.pos.x += Camera.focus.x * forward;
    Camera.pos.y += Camera.focus.y * forward;
    Camera.pos.z += Camera.focus.z * forward;
}
GLvoid cameraBack(GLfloat back) {
    Camera.pos.x -= Camera.focus.x * back;
    Camera.pos.y -= Camera.focus.y * back;
    Camera.pos.z -= Camera.focus.z * back;
}
GLvoid cameraStrafeLeft(GLfloat left){
    Camera.pos.x -= Camera.side.x * left;
    Camera.pos.y -= Camera.side.y * left;
    Camera.pos.z -= Camera.side.z * left;
}
GLvoid cameraStrafeRight(GLfloat right){
    Camera.pos.x += Camera.side.x * right;
    Camera.pos.y += Camera.side.y * right;
    Camera.pos.z += Camera.side.z * right;
}

GLvoid cameraFocusMove(GLfloat forward, GLfloat side){
    Camera.pos.x += Camera.focus.x * forward + Camera.side.x * side;
    Camera.pos.y += Camera.focus.y * forward + Camera.side.y * side;
    Camera.pos.z += Camera.focus.z * forward + Camera.side.z * side;
};

GLvoid cameraRotate(GLfloat yaw, GLfloat pitch){
    Camera.pitch += pitch;
    Camera.yaw += yaw;
    const float hpi = 1.5707963;
    if(Camera.pitch > hpi) Camera.pitch = hpi;
    if(Camera.pitch < -hpi) Camera.pitch = -hpi;
    float cosp = cos(Camera.pitch);
    Camera.focus.x = cosp * sin(Camera.yaw);
    Camera.focus.y = sin(Camera.pitch);
    Camera.focus.z = -cosp * cos(Camera.yaw);
    Camera.side = crossvec4(Camera.focus, Y_AXIS);
    normalizevec4(&Camera.side);
};
