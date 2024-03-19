#include <stdio.h>
#include <string.h>

char closing(char start, const char * const filter) {
    for (unsigned i = 0; filter[i] != 0; i += 2)
        if (filter[i] == start)
            return filter[i+1];
    return 0;
}

// nice pattern !
int main (int argc, char * argv[]) {
    const char * filter = "()[]{}";
    if (argc == 2)
        filter = argv[1];

    char line[1001];
    memset(line, 0, sizeof line);
    char * p = line;
    for (char c = getchar(); c != EOF; c = getchar()) {
        if (c == '\n') {    // end of line
            *p = 0;
            printf("%s\n", line);
            p = line;
        } else if (p == line)     // just started to read the line
            *p++ = c;
        else if (closing(*(p - 1), filter) == c)
            p--;
        else
            *p++ = c;
    }
}