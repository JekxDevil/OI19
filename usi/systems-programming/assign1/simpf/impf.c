/*
b stands for compressed byte format
p stands for uncompressed byte format
compressed stream is a sequence of variable length blocks of bytes determined by the first byte of the block b(i)
if b(i) <= 128 then [b(i+1),b(i+b(i+1))] are directly copied as uncompressed bytes [p(j), p(j+b(i)-1)]
if b(i) > 128 then b(i+1) is repeated b(i)-127 times as uncompressed bytes [p(j), p(j+b(i)-128)]
*/
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_UNCOMPRESSION 128
#define GRAY_SCALE 1
#define RGB 3
#define BYTE 8

const char* FLIP = "flip";
const char* ROTATE = "rotate";
const char* CROP = "crop";

// image pixels
uint16_t w;
uint16_t h;
// bytes per pixel (1 gray scale or 3 RGB)
int8_t d;

void* flip(const char* d);
void* rotate(const int* x);
void* crop(const int* x0, const int* y0, const int* x1, const int* y1);
void* frame(const int* l, const int* c);

int main(int argc, char* argv[]) {
    // read from input
    printf("reading from input %s\n", argv[1]);
    FILE* fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return EXIT_FAILURE;
    };

    // read image dimensions
    // convert endiannes from little endian reading to big endian stored
    uint8_t buffer[2];
    int r = fread(buffer, sizeof(uint8_t), 2, fin);
    w = (buffer[0] << BYTE) | buffer[1];
    r += fread(buffer, sizeof(uint8_t), 2, fin);
    h = (buffer[0] << BYTE) | buffer[1];
    r += fread(&d, sizeof(int8_t), 1, fin);
    if (r != 5) {
        fprintf(stderr, "Error reading input file\n");
        return EXIT_FAILURE;
    };
    printf("r=%d\n", r);

    printf("w=%" PRIu16 " h=%" PRIu16 " d=%" PRId8 "\n", w, h, d);

    // following bytes representing image pixels starting from top left to right
    // so b5 ... b whd-1
    // crash at 00 cood: 0B0 06
    const long long int size = (long long int)w * (long long int)h * (long long int)d;
    uint8_t pixels[size];
    memset(pixels, 0, size);
    int index = 0;
    uint8_t len = 0;
    for (long long int counter = 0; counter < size;) {
        if (len == 0) {
            if (fread(&len, sizeof(uint8_t), 1, fin) != 1) {
                fprintf(stderr, "Error reading input file\n");
                return EXIT_FAILURE;
            };
            printf("len=%" PRIu8 "\n", len);
        };

        if (len <= MAX_UNCOMPRESSION) {
            // copy len bytes

            printf("\nPIXELS: %d\n", len);
            for (int i = 0; i < len; i++) {
                uint8_t b;
                if (fread(&b, sizeof(uint8_t), 1, fin) != 1) {
                    fprintf(stderr, "Error reading input file\n");
                    return EXIT_FAILURE;
                };
                pixels[index++] = b;
                printf("%" PRIu8 " ", b);
            };

            counter += len;
        } else {
            // repeat len-MAX_UNCOMPRESSION times
            uint8_t b;
            if (fread(&b, sizeof(uint8_t), 1, fin) != 1) {
                fprintf(stderr, "Error reading input file\n");
                return EXIT_FAILURE;
            };

            printf("\nPIXELS: %d\n", len - MAX_UNCOMPRESSION + 1);
            for (int i = 0; i <= len - MAX_UNCOMPRESSION; i++) {
                pixels[index++] = b;
                printf("%" PRIu8 " ", b);
            };

            counter += len - MAX_UNCOMPRESSION + 1;
        };
        printf("\nPIXELS\n");
        len = 0;
    };
    printf("bytes read: %d\n", index - 1);
    fclose(fin);

    // apply transformations
    const char* transformation = argv[3];

    // write in output file
    FILE* fout = fopen(argv[2], "w");
    if (fout == NULL) {
        fprintf(stderr, "Error opening output file\n");
        return EXIT_FAILURE;
    };
    // stuff

    fclose(fout);
    return EXIT_SUCCESS;
}

/*
        switch (d) {
            case GRAY_SCALE:
                // read 1 byte

                break;
            case RGB:
                // read 3 bytes
                break;
            default:
                fprintf(stderr, "Error while decompression\n");
                return EXIT_FAILURE;
        }
*/