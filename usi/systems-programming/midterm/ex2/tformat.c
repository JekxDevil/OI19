#include <ctype.h>
#include <string.h>

#include "tformat.h"
// NOTE: the result of the expression t++ is the value t, which is then incremented.
// NOTE: two '\n' means blank line

int myisspace(char c) {
    if (!isspace(c)) return 0;
    if (c == '\n') return 0;
    return 1;
}

void t_format(char * t, const struct t_opts * opt) {
    // All space characters at the beginning and at the end of a line are removed.
    // the end-of-line character (’\n’) is not considered a space character.
    // Empty lines at the beginning and at the end of the text are removed.
    // two or more consecutive space characters are replaced by a single space character (’ ’).
    char* modifier = t;
    int empty_line = 1;
    int insert_space = 0;
    for (const char* p = modifier; *p; ++p) {
        if (*p == '\n') {
            *modifier++ = '\n';     // keep newlines
            empty_line = 1;
            insert_space = 0;
        } else if (myisspace(*p)) {
            // if line isn't empty, remember to add space before next valid character
            if (!empty_line) {
                insert_space = 1;
            }
        } else {
            empty_line = 0;
            if (insert_space) {
                *modifier++ = ' ';
                insert_space = 0;
            }
            *modifier++ = *p;
        }
    }
    *modifier = 0;
    // string has been trimmed and left only with one spaces

    // now remove empty lines before
    // assumptions: no init spaces
    //modifier = t;
    //int started = 0;
    //for (const char* p = modifier; *p; p++) {
    //    if (*p != '\n' || started) {
    //        started = 1;
    //        *modifier++ = *p;
    //    }
    //}

    // now remove empty lines at the end
    //size_t len = strlen(t);
    //unsigned end_newline = 0;
    //for (modifier = t + len - 1; *modifier == '\n' && modifier != t; modifier--) {
    //    end_newline++;
    //}

    //if (end_newline > 1 && modifier != t) {
    //    *(modifier + 2) = 0;
    //}

}
