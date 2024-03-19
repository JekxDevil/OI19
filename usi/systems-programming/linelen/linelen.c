#include <stdio.h>
#include <stdlib.h>
#define SEPARATOR '\n'
// lines are separated by \n
// remember infinity is -1
// add 3 '...' if line longer than 60 characters
// here 60 characters pos 59 max.
// line[60] = '\0';
int main(int argc, char *argv[])
{
    // non negative decimal ints
    int min = 0;
    int max = -1;
    // set the limits
    char line[60 + 1];
    // read lines on the standard input
    if (argc > 2)
        max = atoi(argv[2]);
    if (argc > 1)
        min = atoi(argv[1]);

    int len = 0;
    int i = 0;
    for (int c = getchar(); c != EOF; c = getchar())
    {
        // distinguish between lines
        if (c == SEPARATOR)
        {
            if (len >= min && (len <= max || max == -1))
            {
                line[i] = '\0';
                printf("%s", line);
                if (len > i)
                {
                    printf("...");
                }
                printf("\n");
            }
            len = 0;
            i = 0;
        }
        else
        { // add characters to the line
            if (i < 60)
            {
                line[i] = c;
                ++i;
            }
            len++;
        }
    }
}
