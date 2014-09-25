#include "square_alg.h"
#include "engine.h"

#define DIMS_SCALE_FACTOR 1.0
#define HEIGHT_SCALE_FACTOR 2.0

float** fill_vd_array(int size, int* hei);
GLvoid passive_mouse_routine(int x, int y);
GLvoid keyboard_routine(unsigned char key, int x, int y);
float** vd_array;
float* terrain_vd_array;

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("13");

    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    //glutMouseFunc(My_mouse_routine);

    glutPassiveMotionFunc(passive_mouse_routine);

    glutKeyboardFunc(keyboard_routine);

    int size = SQUARE_SIZE;
    int* hei;

    hei = (int *) calloc(size*size, sizeof(int));

    generateHeights(size, hei);
    float** vd_array;
    printf(" filling terrain array\n");
    vd_array = fill_vd_array(size, hei);

    //printf("2 x %f y %f bigN %f \n", vd_array[0][2], vd_array[2][2], vd_array[4][2]);
    init(vd_array, terrain_vd_array, size);
    glutMainLoop();

    return 0;
}

GLvoid passive_mouse_routine(int x, int y){
    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

GLvoid keyboard_routine(unsigned char key, int x, int y){
    //printf("%c", key);
    switch (key) {
    case 'w':
        cameraForward(1);
        break;
    case 'a':
        cameraStrafeLeft(1);
        break;
    case 's':
        cameraBack(1);
        break;
    case 'd':
        cameraStrafeRight(1);
        break;
    case 'q':
        cameraRotate(-0.5, 0);
        break;
    case 'e':
        cameraRotate(0.5, 0);
        break;
    case 'r':
        terrain->texture = &texture1;
        break;
    case 't':
        terrain->texture = &texture2;
        break;
    case 'y':
        terrain->texture = &texture3;
        break;
    case 'x':
        exit(0);
        break;
    default:
        break;
    }
};


float** fill_vd_array(int size, int* hei) {
    int i, vd_array_size, x, y, bigN, k, l;
    GLfloat arr[size][size];

    //converting heights to float array of heights
    for (k = 0; k < size; k++){
        for (l = 0; l < size; l++){
            arr[k][l] = (float)(*(hei + l + size*k))/HEIGHT_SCALE_FACTOR;
            //printf(" %d ",*(hei + k + size*l));
        }
        //printf("\n");
    }

    for (k = 0; k < size; k++){
        for (l =0; l < size; l++){
            //printf(" %f ",arr[k][l]);
        }
        //printf("\n");
    }


    // setup vertex data array
    GLfloat* vbd;
    vd_array_size = 2*(size - 1)*(size - 1);

    float **vd_array;
    vd_array = malloc(vd_array_size*sizeof(float*));
    terrain_vd_array = malloc(vd_array_size*9*sizeof(float));
    //filling vertex data array
    for (i = 0; i < vd_array_size; i++){
        vd_array[i] = malloc(sizeof(float* [9]));

        bigN = (i/2);
        x = bigN % (size - 1);
        y = bigN /(size - 1);
        //printf("x %d y %d bigN %d \n", x, y, bigN);
        vd_array[i] = malloc(sizeof(float [9]));
        if ((i%2) == 0) {
            vd_array[i][0] = (float)x/DIMS_SCALE_FACTOR;
            vd_array[i][2] = (float)(y + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][1] = (float)arr[x][y+1];
            vd_array[i][3] = (float)x/DIMS_SCALE_FACTOR;
            vd_array[i][5] = (float)y/DIMS_SCALE_FACTOR;
            vd_array[i][4] = (float)arr[x][y];
            vd_array[i][6] = (float)(x + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][8] = (float)y/DIMS_SCALE_FACTOR;
            vd_array[i][7] = (float)arr[x+1][y];

            terrain_vd_array[i*9] = ((float)x)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+2] = ((float)(y + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+1] = (float)arr[x][y+1];
            terrain_vd_array[i*9+3] = ((float)x)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+5] = ((float)y)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+4] = (float)arr[x][y];
            terrain_vd_array[i*9+6] = ((float)(x + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+8] = ((float)y)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+7] = (float)arr[x+1][y];
        } else {
            vd_array[i][0] = (float)(x + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][2] = (float)y/DIMS_SCALE_FACTOR;
            vd_array[i][1] = (float)arr[x+1][y];
            vd_array[i][3] = (float)(x + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][5] = (float)(y + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][4] = (float)arr[x+1][y+1];
            vd_array[i][6] = (float)x/DIMS_SCALE_FACTOR;
            vd_array[i][8] = (float)(y + 1)/DIMS_SCALE_FACTOR;
            vd_array[i][7] = (float)arr[x][y+1];

            terrain_vd_array[i*9] = ((float)(x + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+2] = ((float)y)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+1] = (float)arr[x+1][y];
            terrain_vd_array[i*9+3] = ((float)(x + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+5] = ((float)(y + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+4] = (float)arr[x+1][y+1];
            terrain_vd_array[i*9+6] = ((float)x)/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+8] = ((float)(y + 1))/DIMS_SCALE_FACTOR;
            terrain_vd_array[i*9+7] = (float)arr[x][y+1];
        }
    }
    //printf(" 1 x %f y %f bigN %f \n", vd_array[0][0], vd_array[0][1], vd_array[0][2]);
    //printf("x %f y %f bigN %f \n", arr[0][1], arr[1][1], arr[0][2]);

    return vd_array;
}




