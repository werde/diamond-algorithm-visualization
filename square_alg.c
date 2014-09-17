#include "square_alg.h"

void generateHeights(int side, int *heights){
    srand(time(NULL));
    int hei[side][side], x, y, size;

    for (x = 0; x < side; x++) {
        for (y = 0; y < side; y++){
            hei[x][y] = 0;
        }
    }

    hei[0][0] = 100;
    hei[0][side-1] = 100;
    hei[side-1][0] = 200;
    hei[side-1][side-1] = 200;
    size = side;

    size -=1;

    while (size>=2) {
        //printf("size %d\n", size);
        //diamond_step();
        x =0;y=0;
        while (y != (side - 1)){
            while (x != (side - 1)) {
                hei[x + size/2][y + size/2] = (hei[x][y]+hei[x + size][y]+hei[x][y + size]+hei[x + size][y + size] + rand_to_char())/5;
                //printf("x : %d, y : %d, cx : %d, cy : %d\n", x, y, (x + size/2), (x + size/2));
                x += size;
            }
            y +=size;
            x = 0;
        }

        //square_step();
        x =0;y=0;
        while (y != (side - 1)){
            while (x != (side - 1)) {

                if (y == 0) {
                    hei[x+size/2][y] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x + size][y] + hei[x+size/2][side-size/2-1])/4;
                } else {
                    hei[x+size/2][y] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x + size][y] + hei[x+size/2][y - size/2])/4;
                }

                if ((x +size)== (side-1)) {
                    hei[x+size][y+size/2] = (hei[x + size/2][y + size/2] + hei[x+size][y] + hei[x + size][y+ size] + hei[0+size/2][y+size/2])/4;
                } else {
                    hei[x+size][y+size/2] = (hei[x + size/2][y + size/2] + hei[x+size][y] + hei[x + size][y+ size] + hei[x+size+size/2][y+size/2])/4;
                }

                if ((y+size) == (side-1)){
                    hei[x+size/2][y+size] = (hei[x + size/2][y + size/2] + hei[x+size][y+size] + hei[x][y+size]+hei[x+size/2][0+size/2])/4;
                } else {
                    hei[x+size/2][y+size] = (hei[x + size/2][y + size/2] + hei[x+size][y+size] + hei[x][y+size]+hei[x+size/2][y+size+size/2])/4;
                }

                if (x == 0) {
                    hei[x][y+size/2] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x][y+size] + hei[side - 1 - size/2][y+size/2])/4;
                } else {
                    hei[x][y+size/2] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x][y+size] + hei[x-size/2][y+size/2])/4;
                }

                x += size;
            }
            y +=size;
            x = 0;
        }
        size = size/2;
    }
    printHeights(hei, side);

    for (x = 0; x < side; x++) {
        for (y = 0; y < side; y++){
            *(heights + x + side*y) = hei[x][y];
        }
    }
};

void printHeights(int* hei, int side){
    int x, y;
    for (x = 0; x < side; x++) {
        for (y = 0; y < side; y++){
            printf(" %5d ", *(hei + x + side*y));
        }
        printf("\n");
    }
};

unsigned char rand_to_char(){
    unsigned char result, r2;

    //printf("%d", RAND_MAX);

    result = (unsigned char)(255.0 * ((float)rand())/(float)RAND_MAX);
    r2 = (unsigned char)(255.0 * ((float)rand())/(float)RAND_MAX);;

    //printf("\n%d %d", result, r2);

    return r2;
}
