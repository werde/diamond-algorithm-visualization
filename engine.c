#include "engine.h"
#define VERTEX_SHADER "./engine/shaders/SimpleTransform.vertexshader"
#define FRAGMENT_SHADER "./engine/shaders/SingleColor.fragmentshader"

GLuint MatrixID, programID, vertexbuffer, uvbuffer;
GLuint ViewMatrixID, ModelMatrixID, CameraPosID;
mat4 projection, view, modelMat, MVP;
struct _TPolygon** polyArray;

	static const GLfloat g_uv_buffer_data[] = {
		 0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f,  1.0f,
    };

GLvoid init(float** vd_array, float* terrain_vd_array, int size){
    int i, k;
    float av_poly_height;
    int polyCount = 2*(size-1)*(size-1);
    cameraInit();

    polyArray = malloc(polyCount*sizeof(struct _TPolygon*));

    loadTexture("./res/img_jpg/grass_tex.jpg", &texture1);
    loadTexture("./res/img_jpg/snow_tex.jpg", &texture2);
    loadTexture("./res/img_jpg/water_tex.jpg", &texture3);
/*
    for (i = 0; i < polyCount; i++) {
        av_poly_height = (vd_array[i][2] + vd_array[i][5] + vd_array[i][8])/3;
        //printf("avpolyhe %f", av_poly_height);
        if (av_poly_height > 0) {
            polyArray[i]=tpolygon_init(vd_array[i], g_uv_buffer_data, &texture2);
        } else if (av_poly_height > 11) {
            polyArray[i]=tpolygon_init(vd_array[i], g_uv_buffer_data, &texture1);
        } else {
            polyArray[i]=tpolygon_init(vd_array[i], g_uv_buffer_data, &texture3);
        }
    }*/
    terrain = tterrain_init(terrain_vd_array, g_uv_buffer_data, &texture1);
    printf("initialized terrain\n");
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    programID = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);
    MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	CameraPosID = glGetUniformLocation(programID, "CameraPos");

    //set up matrices
    projection = perspective(45.0f, (float)4.0f / 3.0f, 0.1f, 1000.0f);
    view = lookAt(Camera.pos, Camera.focus);
    modelMat = IDENTITY_MATRIX;
    mat4 temp = multiplymat4(&modelMat, &view);
    MVP = multiplymat4(&temp, &projection);
};
GLvoid display(GLvoid){
    int i, polyCount;
    polyCount = 2*(SQUARE_SIZE - 1)*(SQUARE_SIZE - 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);
    updateMVP();

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(MVP.m[0]));
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &(modelMat.m[0]));
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &(view.m[0]));
    glUniform3f(CameraPosID, Camera.pos.m[0], Camera.pos.m[1], Camera.pos.m[2]);

/*
    for (i = 0; i < polyCount; i++) {
        //printf("drawing poly %d\n", i);
        tpolygon_draw(polyArray[i]);
    }
*/
    tterrain_draw(terrain);
    glutSwapBuffers();
};

GLvoid updateMVP() {
    //projection = perspective(45.0f, (float)4.0f / 3.0f, 0.1f, 1000.0f);

    GLfloat pitch, yaw;
    int x, y;
    x = mouse_x;
    y = mouse_y;
    yaw = 0.004f * (GLfloat) (x - 400);
    pitch = 0.004f * (GLfloat) (300 - y);
    cameraRotate(yaw, pitch);
    glutWarpPointer(400, 300);

	view = lookAt(Camera.pos, Camera.focus);
	//model = IDENTITY_MATRIX;

	mat4 temp = multiplymat4(&modelMat, &view);
    MVP = multiplymat4(&temp, &projection);
}

GLvoid loadTexture(char* path, GLuint* texture){


    *texture = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if( 0 == *texture )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    printf(" loaded texture: %s\n", path);
}
