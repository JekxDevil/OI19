/* Systems Programming - Assingment 1 - Jeferson Morales Mariciano */

/*
input:
- width: of the image, column. 2 Bytes
- height: of the image, rows. 2 Bytes
- color: of the image. 1 = grey scale, 3 = RGB. 1 Byte

implicit:
- size: of image. width * height * color
*/

#include <stddef.h>  // standard library for default macros e.g. NULL
#include <stdio.h>   // standard library for input/output
#include <stdlib.h>  // used for dynamic memory handling i.e. malloc, atoi
#include <string.h>  // used for string comparison and mem___() methods

#define FLIP "flip"
#define ROTATE "rotate"
#define CROP "crop"
#define FRAME "frame"

#define H 'h'
#define V 'v'
#define COMMAND 3

// TODO: FREE ALLOCATED MEMORY WHEN CRASHING

// integer pointer to the image bytes
u_int8_t *img_bytes;
u_int16_t width, height;
u_int8_t color;
u_int32_t size;

void reading_decompress(const char *const);
void compress();
void writing_compress();

void flip(const char *const);
void flip_horizontal();
void flip_vertical();

void rotate(const int);
void crop(const int, const int, const int, const int);
void frame(const int, const int);

int main(int argc, char *argv[]) {
    const char *const name_fin = argv[1];
    const char *const name_fout = argv[2];
    reading_decompress(name_fin);

    // apply transformation choosen by the image
    if (!strcmp(argv[COMMAND], FLIP)) {
        const char *const d = argv[COMMAND + 1];
        flip(d);
    } else if (!strcmp(argv[COMMAND], ROTATE)) {
        const int x = atoi(argv[COMMAND + 1]);
        rotate(x);
    } else if (!strcmp(argv[COMMAND], CROP)) {
        const int x0 = atoi(argv[COMMAND + 1]);
        const int y0 = atoi(argv[COMMAND + 2]);
        const int x1 = atoi(argv[COMMAND + 3]);
        const int y1 = atoi(argv[COMMAND + 4]);
        crop(x0, y0, x1, y1);
    } else if (!strcmp(argv[COMMAND], FRAME)) {
        const int l = atoi(argv[COMMAND + 1]);
        const int c = atoi(argv[COMMAND + 2]);
        frame(l, c);
    }

    // compress and save image, then free used memory
    compress();
    writing_compress(name_fout);
    free(img_bytes);
    return EXIT_SUCCESS;
};

/**
 * @brief Open, read and decompress of the iput file, retrieving image bytes
 *
 * @param filename
 */
void reading_decompress(const char *const filename) {
    FILE *const fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file");
        exit(EXIT_FAILURE);
    };

    // create a img of number of Bytes equal to size = width * height * color
    // Reading width, height, color and size image using bitshifting mechanism for endiannes conversion
    width = (fgetc(fp) << 8) + fgetc(fp);   // b0 b1
    height = (fgetc(fp) << 8) + fgetc(fp);  // b2 b3
    color = fgetc(fp);                      // b4
    size = width * height * color;

    img_bytes = malloc(size * sizeof(u_int8_t));
    if (img_bytes == NULL) {
        fprintf(stderr, "Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    // read the file and decompress it
    u_int8_t ch = fgetc(fp), position = 0;
    while (ch != EOF && position < size) {
        // if the byte is less or equal to 127 then  we do not need to decompress it
        if (ch <= 128) {
            // normal reading: next ch bytes assigned to img
            for (int i = 0; i <= ch; i++)
                img_bytes[position++] = fgetc(fp);  // assign the value of the byte get from the file to the img

        } else {
            // decompression part:
            int times = ch - 127;  // repeat number of times
            u_int8_t b = fgetc(fp);
            for (int i = 0; i < times; i++)  // loop to assign the byte to repeat to img 'times' times
                img_bytes[position++] = b;   // assign the value of the byte get from the file to the img
        }
        ch = fgetc(fp);  // get the next byte from the file
    }

    fclose(fp);
}

/**
 * @brief Compress the image
 *
 */
void compress() {
    u_int8_t *compress;
    int sizeOut;

    compress = malloc(width * height * color * sizeof(u_int8_t) * 2);
    if (compress == NULL) {
        fprintf(stderr, "Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    sizeOut = 0;
    for (int i = 0; i < size; i++) {
        u_int8_t tempo = 1;
        int st = i;
        while (img_bytes[i] == img_bytes[i + 1] && tempo < 128) {
            i++;
            tempo++;
        }

        if (tempo > 1) {
            compress[sizeOut++] = 127 + (tempo);
            compress[sizeOut++] = img_bytes[st];
        } else {
            tempo = 0;
            // if the pixel is not equal to the next pixel then increment tempo and increment i
            // until the pixel is equal to the next pixel or tempo is equal to 128
            // or we reach the end of the img
            while (img_bytes[i] != img_bytes[i + 1] && tempo < 129 && i < size - 1) {
                tempo++;
                i++;
            }

            // if i is not the last pixel of the img then decrement i and tempo
            if (i != size - 1) {
                tempo--;
                i--;
            }

            // assign the number of repetitions to the array at position sizeOut
            compress[sizeOut++] = tempo;

            // assign the pixel to the array at position sizeOut
            for (int i = 0; i <= tempo; i++)
                compress[sizeOut++] = img_bytes[st + i];
        }
    }

    // reallocate the img dynamic memory with the new size [sizeof(int) * sizeOut]
    img_bytes = realloc(img_bytes, sizeof(u_int8_t) * sizeOut);
    size = sizeOut;                                           // update the size of the img
    memcpy(img_bytes, compress, sizeOut * sizeof(u_int8_t));  // copy the array in the img
    free(compress);                                           // free the dynamic memory allocated to the array compress
}

/**
 * @brief Compress and write the image in the output file
 * Close output file
 * @param name_fout name of the output file
 */
void writing_compress(const char *const name_fout) {
    // open file in writing mode
    FILE *const fp = fopen(name_fout, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: fopen failed");
        exit(EXIT_FAILURE);
    }

    // write to the output file fp the header of ther file compressed
    // using the byte format: w1 w2 h1 h2 c1
    fprintf(fp, "%c%c%c%c%c", width >> 8, width, height >> 8, height, color);
    for (int i = 0; i < size; i++) fprintf(fp, "%c", img_bytes[i]);
    fclose(fp);
}

//#pragma region TRANSFORMATIONS

//#pragma region FLIP
/**
 * @brief Flip horizontally the image
 *
 */
void flip_horizontal() {
    u_int8_t *array = malloc(size * sizeof(u_int8_t));
    if (array == NULL) {
        printf("Error: memory not allocated.");
        exit(EXIT_FAILURE);
    }

    memcpy(array, img_bytes, size * sizeof(int));

    for (int i = 0; i < height; i++) {
        int l = i * width * color;
        int r = (i + 1) * width * color - 1;

        while (l < r) {
            if (color == 3) {
                array[l + 2] = img_bytes[r];
                array[l + 1] = img_bytes[r - 1];
                array[l] = img_bytes[r - 2];

                array[r - 2] = img_bytes[l];
                array[r - 1] = img_bytes[l + 1];
                array[r] = img_bytes[l + 2];
            } else {
                array[l] = img_bytes[r];
                array[r] = img_bytes[l];
            }

            l += color;
            r -= color;
        }
    }

    memcpy(img_bytes, array, size * sizeof(u_int8_t));
    free(array);
}

/**
 * @brief Flip vertically the image
 *
 */
void flip_vertical() {
    // copy the img in the array
    u_int8_t *array = malloc(size * sizeof(u_int8_t));
    if (array == NULL) {
        printf("Error: memory not allocated.");
        exit(EXIT_FAILURE);
    }

    // iterate until the middle of the height
    // posUp -> first position of i-th row
    // posDown -> first position of vertically specular i-th row
    // copy the rows in the vertically specular order from unchanged matrix to our building result temporary array matrix
    memcpy(array, img_bytes, size * sizeof(int));  // copy img_bytes to temp array
    for (int i = 0; i < height / 2; i++) {
        int posUp = i * width * color;
        int posDown = (height - 1 - i) * width * color;
        memcpy(&array[posUp], &img_bytes[posDown], width * color * sizeof(u_int8_t));
        memcpy(&array[posDown], &img_bytes[posUp], width * color * sizeof(u_int8_t));
    }

    memcpy(img_bytes, array, size * sizeof(u_int8_t));
    free(array);
}

/**
 * @brief Flip the image choosing between horizontally 'h' or vertically 'v' given by the parameter d
 *
 * @param d containing either 'h' or 'v'
 */
void flip(const char *const d) {
    switch ((*d)) {
        case H:
            flip_horizontal();
            break;
        case V:
            flip_vertical();
            break;
        default:
            fprintf(stderr, "Error: invalid parameter in flip function");
            exit(EXIT_FAILURE);
            break;
    };
};

/**
 * @brief Rotate the image counter-clockwise by 90x degress.
 *
 * @param x The values allowed are {1, 2, 3}, corresponding to {90, 180, 270}
 */
void rotate(const int x) {
    // To rotate of 180 degrees the images  is possible through horizontal and vertical flip sequentially
    if (x == 2) {
        flip_horizontal();  // horizontal flip of the image
        flip_vertical();    // vertical flip of the image
        return;
    }

    // TO rotate of 270 deg, use the horizontal flip and the vertical flip + the rotation of 90 deg
    if (x == 3) {
        flip_horizontal();  // horizontal flip of the image
        flip_vertical();    // vertical flip of the image
        // no return in this case because we need to rotate of 90 deg more then we will execute more code below
    }

    u_int8_t *const array = malloc(size * sizeof(u_int8_t));  // stialize an array of length [size * 4byte]
    if (array == NULL) {
        fprintf(stderr, "Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    int pos = 0;

    // rotating the image of 90 deg in clockwise direction
    // for all the width dimension of the img
    for (int i = 0; i < width; i++) {
        // for all the height dimension of the img
        for (int j = 0; j < height; j++) {
            // pos2 is the position of the pixel in the img that we need to copy in the array at position pos
            int pos2 = (j * width + i) * color;
            for (int k = 0; k < color; k++) {
                // the byte stored at pos2 of img is assigned to pos of array, which becomes the rotated image
                // then increments pos and pos2 using post-fixed operators
                array[pos++] = img_bytes[pos2++];
            }
        }
    }

    // copy the array in the img
    memcpy(img_bytes, array, size * sizeof(u_int8_t));
    // free dynamic memory allocated to the variable array serving as temporary result storage
    free(array);
    // swap the width and the height
    u_int8_t w = width;
    width = height;
    height = w;
    // the img has been rotated of 90 deg in clockwise direction
    // so we need to flip the image vertically to have the image rotated of 90 deg in counter-clockwise direction
    flip_vertical();
}

/**
 * @brief Crop the image by using given coordinates
 *
 * @param x0 top-left corner x coordinate
 * @param y0 top-left corner y coordinate
 * @param x1 bottom-right corner x coordinate
 * @param y1 bottom-right corner y coordinate
 */
void crop(const int x0, const int y0, const int x1, const int y1) {
    //  new size of image after crop: adding 1 to the width and the height because included extreme points
    int new_size = (x1 - x0 + 1) * color * (y1 - y0 + 1);
    u_int8_t array[new_size];
    int index = 0;

    // iterate through image matrix array to retrieve only the image pixels within the crop area
    for (int i = y0; i <= y1; i++)
        for (int j = x0 * color; j < (x1 + 1) * color; j++)
            array[index++] = img_bytes[i * width * color + j];

    // copy temporary array into the image array
    // when the frame operation is done, update: width, height, size of img_bytes
    memcpy(img_bytes, array, new_size * sizeof(u_int8_t));
    width = x1 - x0 + 1;
    height = y1 - y0 + 1;
    size = new_size;
};

/**
 * @brief Frame an image.
 *
 * @param l pixels to add around the image for the frame to take effect
 * @param col color of the frame
 */
void frame(const int l, const int col) {
    // new_height: 2 * l added to the height since adding l pixels to the top and the bottom
    // new_width: 2 * l follows same above logic + color because each pixel is either 1 or 3 bytes
    int new_height = height + 2 * l;
    int new_width = width * color + 2 * l * color;
    int new_size = new_height * new_width;
    u_int8_t array[new_size];

    // iterate through image matrix array to add the frame
    // if the is in a layered framed position, otherwise copy image bytes
    int index = 0;
    for (int i = 0; i < new_height; i++)
        for (int j = 0; j < new_width; j++)
            if (i >= l && i < height + l && j >= l * color && j < width * color + l * color)
                array[i * new_width + j] = img_bytes[index++];
            else
                array[i * new_width + j] = col;

    // use realloc to change the image to its new size, then copy the temp array in the image
    // when the frame operation is done, update: width, height, size of img_bytes
    img_bytes = realloc(img_bytes, sizeof(u_int8_t) * new_size);
    memcpy(img_bytes, array, new_size * sizeof(u_int8_t));
    width = width + l * 2;
    height = new_height;
    size = new_size;
};
