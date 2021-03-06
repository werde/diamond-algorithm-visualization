#include "square_alg.h"

void generateHeights(int side, int *heights){
    time_t now, later;
    double seconds;
    int hei[side][side], x, y, size, k;
    srand(time(NULL));

    time(&now);

    for (x = 0; x < side; x++) {
        for (y = 0; y < side; y++){
            hei[x][y] = 0;
        }
    }

    hei[0][0] = 0;
    hei[0][side-1] = 0;
    hei[side-1][0] = 0;
    hei[side-1][side-1] = 0;
    size = side - 1;
    k = 1;
    while (size>=2) {
        //printf("size %d\n", size);
        //diamond_step();
        x =0; y=0; k=side/(size);
        int test;
        test=rand_to_char() - 128;
        printf("random %d %d %d %d %d\n",test, test/k, k, side, size);
        while (y != (side - 1)){
            while (x != (side - 1)) {
                hei[x + size/2][y + size/2] = (hei[x][y]+hei[x + size][y]+hei[x][y + size]+hei[x + size][y + size])/4  +  ((rand_to_char()) - 128)/k;

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
                    hei[x+size/2][side-1] = hei[x+size/2][y];
                } else {
                    hei[x+size/2][y] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x + size][y] + hei[x+size/2][y - size/2])/4;
                }

                if ((x +size)== (side-1)) {
                    //hei[x+size][y+size/2] = (hei[x + size/2][y + size/2] + hei[x+size][y] + hei[x + size][y+ size] + hei[0+size/2][y+size/2])/4;
                } else {
                    //hei[x+size][y+size/2] = (hei[x + size/2][y + size/2] + hei[x+size][y] + hei[x + size][y+ size] + hei[x+size+size/2][y+size/2])/4;
                }

                if ((y+size) == (side-1)){
                    //hei[x+size/2][y+size] = (hei[x + size/2][y + size/2] + hei[x+size][y+size] + hei[x][y+size]+hei[x+size/2][0+size/2])/4;
                } else {
                    //hei[x+size/2][y+size] = (hei[x + size/2][y + size/2] + hei[x+size][y+size] + hei[x][y+size]+hei[x+size/2][y+size+size/2])/4;
                }

                if (x == 0) {
                    hei[x][y+size/2] = (hei[x + size/2][y + size/2] + hei[x][y] + hei[x][y+size] + hei[side - 1 - size/2][y+size/2])/4;
                    hei[side-1][y+size/2] = hei[x][y+size/2];
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
    //printHeights(hei, side);

    for (x = 0; x < side; x++) {
        for (y = 0; y < side; y++){
            *(heights + x + side*y) = hei[x][y];
        }
    }

    time(&later);
    seconds = difftime(later, now);
    printf("%.f generation time", seconds);
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

    //printf("\n rand %d %d", result, r2);

    return r2;
}
