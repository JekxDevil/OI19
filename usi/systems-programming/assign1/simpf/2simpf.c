// IMPORTS
#include <stddef.h>  // standard library for default macros i.e. NULL
#include <stdio.h>   // standard library for input/output
#include <stdlib.h>  // used for dynamic memory allocation, i.e. malloc
#include <string.h>  // used for string comparison and memcpy

// global variables for the management of the image
int *matrix;
int width, height, color, size;

void openINPUT(const char *);

void horizontalFlip() {
    int *array = malloc(size * sizeof(int));    // initialize an array of length [size * 4byte]
    memcpy(array, matrix, size * sizeof(int));  // copy the matrix in the array

    // for all the height dimension of the img
    for (int i = 0; i < height; i++) {
        int LEFT = i * width * color;
        int RIGHT = (i + 1) * width * color - 1;

        // for all the width dimension of the img
        while (LEFT < RIGHT) {
            // if color is RGB then swap the pixel that has a diffrent size
            if (color == 3) {
                // swap the pixel of the image
                array[LEFT + 2] = matrix[RIGHT];
                array[LEFT + 1] = matrix[RIGHT - 1];
                array[LEFT] = matrix[RIGHT - 2];

                array[RIGHT - 2] = matrix[LEFT];
                array[RIGHT - 1] = matrix[LEFT + 1];
                array[RIGHT] = matrix[LEFT + 2];
            } else {
                array[LEFT] = matrix[RIGHT];
                array[RIGHT] = matrix[LEFT];
            }

            // move the pointer to the next pixel
            LEFT += color;
            RIGHT -= color;
        }
    }

    // copy the array in the matrix
    memcpy(matrix, array, size * sizeof(int));
    free(array);
}

void verticalFlip() {
    // copy the matrix in the array
    int *array = malloc(size * sizeof(int));
    memcpy(array, matrix, size * sizeof(int));

    // for all the height dimension of the img
    for (int i = 0; i < height / 2; i++) {
        int posUp = i * width * color;
        int posDown = (height - 1 - i) * width * color;

        memcpy(&array[posUp], &matrix[posDown], width * color * sizeof(int));  // copy the pixel of the image in the array
        memcpy(&array[posDown], &matrix[posUp], width * color * sizeof(int));
    }

    // copy the array in the matrix
    memcpy(matrix, array, size * sizeof(int));
    free(array);
}

void flip(char *d) {
    if (d[0] == 'h')  // if the char is h then call the horizontalFlip function
        horizontalFlip();
    else  // else call the verticalFlip function
        verticalFlip();
}

void rotate(int deg) {
    deg = deg % 4;
    if (deg == 0) {
        return;
    }

    if (deg == 2) {
        horizontalFlip();
        verticalFlip();
        return;
    }
    if (deg == 3) {
        horizontalFlip();
        verticalFlip();
    }

    if (color == 1) {
        int *array = malloc(size * sizeof(int));  // initialize an array of length [size * 4byte]

        for (int i = 0; i < height; i++)  // for all the  dimension of the img
            for (int j = 0; j < width; j++)
                array[(j * height) + i] = matrix[(i * width) + j];  // copy the pixel of the image in the array

        memcpy(matrix, array, size * sizeof(int));

        // swap the width and the height
        int w = width;
        width = height;
        height = w;
        verticalFlip();
        return;
    }

    int *array = malloc(size * sizeof(int));
    memcpy(array, matrix, size * sizeof(int));

    int pos = 0;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int pos2 = (j * width + i) * color;
            for (int k = 0; k < color; k++) {
                array[pos++] = matrix[pos2++];
            }
        }
    }

    memcpy(matrix, array, size * sizeof(int));

    free(array);

    int w = width;

    width = height;
    height = w;

    verticalFlip();
}

void crop(int x0, int y0, int x1, int y1) {
    int nSize = (x1 - x0 + 1) * color * (y1 - y0 + 1);
    int array[nSize];

    int count = 0;
    int countM = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width * color; j++) {
            if (i >= y0 && i <= y1 && j >= x0 * color && j < (x1 + 1) * color) {
                array[count++] = matrix[countM];
            }
            countM++;
        }
    }

    for (int i = 0; i < nSize; i++) {
        matrix[i] = array[i];
    }

    width = x1 - x0 + 1;
    height = y1 - y0 + 1;
    size = nSize;
}

void frame(int l, int col) {
    int NewHeight = height + 2 * l;
    int NewWidth = width * color + 2 * l * color;
    int NewSize = NewHeight * NewWidth;
    int array[NewSize];

    int count = 0;
    for (int i = 0; i < NewHeight; i++) {
        for (int j = 0; j < NewWidth; j++) {
            if (i >= l && i < height + l && j >= l * color && j < width * color + l * color) {
                array[i * NewWidth + j] = matrix[count++];
            } else {
                array[i * NewWidth + j] = col;
            }
        }
    }

    matrix = realloc(matrix, sizeof(int) * NewSize);

    memcpy(matrix, array, NewSize * sizeof(int));

    size = NewSize;
    height = NewHeight;
    width = width + l * 2;
}

void compressInput() {
    int *compress;
    int sizeOut;

    compress = malloc(width * height * color * sizeof(int) * 2);

    sizeOut = 0;

    for (int i = 0; i < size; i++) {
        int tempo = 1;
        int init = i;
        while (matrix[i] == matrix[i + 1] && tempo < 128) {
            i++;
            tempo++;
        }

        if (tempo > 1) {
            compress[sizeOut++] = 127 + (tempo);
            compress[sizeOut++] = matrix[init];
        } else {
            tempo = 0;
            init = i;
            while (matrix[i] != matrix[i + 1] && tempo < 129 && i < size - 1) {
                ++i;
                ++tempo;
            }
            if (i != size - 1) {
                --i;
                --tempo;
            }
            compress[sizeOut++] = tempo;
            for (int j = 0; j <= tempo; j++) {
                compress[sizeOut++] = matrix[init + j];
            }
        }
    }

    matrix = realloc(matrix, sizeof(int) * sizeOut);
    size = sizeOut;
    memcpy(matrix, compress, sizeOut * sizeof(int));
    free(compress);
}

int main(int argc, char *argv[]) {
    openINPUT(argv[1]);  // open input file

    int i = 3;
    if (!strcmp(argv[i], "flip")) {
        flip(argv[i + 1]);  // FLIP HORIZONTAL OR VERTICAL
    } else if (!strcmp(argv[i], "rotate")) {
        rotate(atoi(argv[i + 1]));  // ROTATE 90, 180, 270 DEGREES
    } else if (!strcmp(argv[i], "crop")) {
        crop(atoi(argv[i + 1]), atoi(argv[i + 2]), atoi(argv[i + 3]), atoi(argv[i + 4]));  // CROP IMAGE
    } else if (!strcmp(argv[i], "frame")) {
        int l = atoi(argv[i + 1]);
        int c = atoi(argv[i + 2]);
        frame(l, c);  // ADD FRAME
    }

    compressInput();      // COMPRESS IMAGE
    closeInput(argv[2]);  // SAVE IMAGE
    free(matrix);         // FREE MEMORY
    return EXIT_SUCCESS;
}

//#region INPUT/OUTPUT
//  open the file and decompress it and assign the value of the img
void openINPUT(const char *NAME) {
    FILE *fp = fopen(NAME, "r");

    // assign the width, height, color and size of the image
    // create a matrix of size width * height * color
    width = (fgetc(fp) << 8) + fgetc(fp);
    height = (fgetc(fp) << 8) + fgetc(fp);
    color = fgetc(fp);
    size = width * height * color;
    if ((matrix = malloc(size * sizeof(int))) == NULL) {
        printf("Error: Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    int position = 0;

    // read the file and decompress it
    for (int ch = fgetc(fp); ch != EOF && position < size; ch = fgetc(fp)) {
        if (ch <= 128) {
            for (int i = 0; i <= ch; i++) {
                int v = fgetc(fp);
                matrix[position++] = v;
            }
        } else {
            int v = fgetc(fp);
            int times = ch - 127;
            for (int i = 0; i < times; i++) {
                matrix[position++] = v;
            }
        }
    }
    fclose(fp);
}

void closeInput(char *NAME) {
    FILE *fp = fopen(NAME, "w+");
    if (fp == NULL)
        return;

    int w1 = width / 256;
    int w2 = width - (w1 * 256);
    int h1 = height / 256;
    int h2 = height - (h1 * 256);
    int d = color;

    fputc(w1, fp);
    fputc(w2, fp);
    fputc(h1, fp);
    fputc(h2, fp);
    fputc(d, fp);
    for (int i = 0; i < size; i++) {
        fputc(matrix[i], fp);
    }
    fclose(fp);
}
//#endregion