#include <stdio.h>
#include <ctype.h>
#define TRUE 255
#define FALSE 0
int main(void) {
    unsigned long long int num_words = 0;
    unsigned short int is_new_word = FALSE;
    for (unsigned int c = getchar(); c != EOF; c = getchar()) {
        if (isspace(c)) {
            if (is_new_word == TRUE) {
                is_new_word = FALSE;
                num_words++;
            }
        }
        else is_new_word = TRUE;
    }
    if (is_new_word == TRUE) num_words++;
    printf("%lld\n", num_words);
    return 0;
}
