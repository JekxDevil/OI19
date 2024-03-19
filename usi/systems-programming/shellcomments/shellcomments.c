// Author: Jeferson Morales Mariciano
#include <stdio.h>

int main(void)
{
    int letter;         // retrieve chars
    int in_comment = 0; // flag signaling letters belong to comment
    while ((letter = getchar()) != EOF)
    {
        if (letter == '#' && !in_comment) // start a comment (without being already in one)
        {
            in_comment = 1;
        }
        else if (letter == '\n' && in_comment) // stop a comment if we are on one
        {
            in_comment = 0;
            putchar(letter);
        }
        else if (in_comment) // print comment letters
        {
            putchar(letter);
        }
    }
    return 0;
}
