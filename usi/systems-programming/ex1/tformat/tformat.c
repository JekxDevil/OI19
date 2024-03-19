/*
TRIM function
a line might be empty
two or more inner consecutive space characters are translated into one
*/
#include "tformat.h"
#include <ctype.h>  //isspace()
#include <stdlib.h>
#include <string.h>
#define NEWLINE '\n'

// returns a string with one spaces only
char * reduce_spaces(char * p) {
    char * result = malloc(strlen(p));      // result big at least as the param
    if (result == 0) return 0;              // if not valid, return null poiter
    memset(result, 0, strlen(p));           // set all memory as null pointer to end string
    int space_before = 0;                   // signal the string as spaces before
    char * tmp = p;                         // traversing pointer
    int index = 0;                          // index to write on the character at
    while (*tmp) {                          // while the loop doesn't meet null pointer end of string
        // space and started or not space and started, then copy
        if (isspace(*tmp)) {
            if (!space_before) {
                result[index++] = *tmp;
            }
        } else {
            result[index++] = *tmp;
        }
        tmp++;                              // goto next char
    }
    // for only space string, we return a space
    return result;
}

// return a string without spaces at start and end
char * trim_str(char * p) {
    char * result = malloc(strlen(p));      // result big at least as the param
    if (result == 0) return 0;              // if not valid, return null poiter
    memset(result, 0, strlen(p));           // set all memory as null pointer to end string
    int started = 0;                        // signal the string as characters besides space (started)
    char * tmp = p;                         // traversing pointer
    int index = 0;                          // index to write on the character at
    while (*tmp) {                          // while the loop doesn't meet null pointer end of string
        // space and started or not space and started, then copy
        if (isspace(*tmp) && started) {
            result[index++] = *tmp;
        } else if (!isspace(*tmp) && !started) {
            started = 1;
        }
        tmp++;                              // goto next char
    }
    // trim spaces at the end
    if (index >= 2) { // e.g. a_\0
        char * end = result + (index - 1);
        while (result != end && isspace(*end)) {
            *end = 0;
        }
    }
    // for only space string, we don't return anything
    return result;
}

void t_format(char* t, const struct t_opts* opt) {
    // reduce all the spaces
    char * reduced = reduce_spaces(t);
    if (reduced == 0) return;
    memset(t, 0, sizeof(strlen(t)));
    strcpy(t, reduced);
    free(reduced);

    char * trim = trim_str(t);
    if (trim == 0) return;
    memset(t, 0, sizeof(strlen(t)));
    strcpy(t, trim);
    free(trim);
}
