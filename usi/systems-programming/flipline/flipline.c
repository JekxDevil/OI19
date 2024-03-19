// Author: Jeferson Morales Mariciano
#include <stdio.h>

int main(void)
{
    char line[1000]; // assumption: no line is longer than 1000 chars
    int index = 0;
    for (int c = getchar(); c != EOF; c = getchar()) // read until EOF
    {
        if (c == '\n') // if whole line read, print it and reset index
        {
            for (--index; index >= 0; index--)
                putchar(line[index]);
            index = 0;
            putchar('\n'); // new line should not be printed in reverse mode
        }
        else
            line[index++] = c; // store char in line and increment index
    }

    if (index > 1) // print also last line if it doesn't end with a newline
    {
        for (--index; index >= 0; index--)
            putchar(line[index]);
        index = 0;
    }
    return 0;
}