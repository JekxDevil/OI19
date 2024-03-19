//ABOUT BUFFERS
#include <stdlib.h>
#include "bufile.h"

struct bufile {
    char * begin;
    char * end;
};

BUFILE * bufopen(char * begin, char * end) {
    struct bufile * this = malloc(sizeof(BUFILE));
    if (!this) return 0;
    // remember pointers passed already have objects
    this->begin = begin;
    this->end = end;
    return this;
}

void bufclose(BUFILE * buf) {
    free(buf);
}

char * bufgets(char * s, int size, BUFILE * buf) {
    int i = 0;
    int finished = 0;
    if (buf->begin == buf->end) return 0;
    for (i = 0; (i < size - 1) && !finished; i++) {
        s[i] = *(buf->begin);   // save the character
        buf->begin += 1;        // move the pointer to the next one
        if (s[i] == '\n' || buf->begin == buf->end) {
            finished = 1;
        }
    }
    s[i] = 0;
    return s;   // return the pointer
}
