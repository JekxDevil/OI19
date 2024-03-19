#include <stdio.h>
// the program reads input from argv
int main(int argc, char *argv[])
{
    int n = atoi(argv[1]); // cast the input to an integer
    if (n < 0)             // check if number is non negative, as requested in assignment
    {
        printf("The number must be positive.");
        return 0;
    }

    int side = n * 2 - 1; // side length of the diamond
    int spaces = n - 1;   // # spaces in the current row
    int hashtags = 1;     // # hashtags in the current row
    // double for loop to print the diamond (O(n^2) iterations)
    // outer cycle referring rows
    for (int i = 0; i < side; i++)
    {
        // spaces and hashtags counters that will reach during the loops # of spaces and hashtags in the current row
        int counter_space = 0;
        int counter_hashtag = 0;
        // inner cycle referring each position in the row (print character)
        for (int j = 0; j < side; j++)
        {
            if (counter_space < spaces)
            {
                counter_space++;
                printf(" ");
            }
            else
            {
                if (counter_hashtag < hashtags)
                {
                    counter_hashtag++;
                    printf("#");
                } // otherwise leave empty, do not print spaces because tests won't pass
            }
        }
        printf("\n");

        // update counters for the next row
        // growing spaces and hashtags # as we reach the middle of the diamond, then decreasing
        if (i < n - 1)
        {
            spaces--;
            hashtags += 2;
        }
        else
        {
            spaces++;
            hashtags -= 2;
        }
    }
    return 0;
}
