#include <stdio.h>
#include <ctype.h>

void print_score(int p);
void print_sequence_while(int n);
void print_sequence_dowhile(int n);
void print_sequence_for(int n);
void labels();
void wc_labels();
void anima();
void anima_reverse();

int main(void)
{
    anima();
    return 0;
}

void print_score(int p)
{
    if (p < 0)
    {
        printf("Something is wrong: your score is negative!\n");
        return;
    }
    printf("You have %d point", p);
    if (p != 1)
        printf("s");
    printf("\nThat is ");
    switch (p)
    {
    case 0:
    case 1:
        printf("a bit low");
        break;
    case 2:
        printf("okay");
        break;
    case 4:
        printf("very ");
    case 3:
        printf("good");
        break;
    case 5:
        printf("excellent!");
    }
    printf("\n");
}

void print_sequence_while(int n)
{
    if (n < 0)
    {
        printf("Something is wrong: your number is negative!\n");
        return;
    }

    int i = 1;
    while (i <= n)
    {
        printf("%d", i);
        if (i != n)
        {
            printf(" ");
        }
        i++;
    }
}

void print_sequence_dowhile(int n)
{
    if (n < 0)
    {
        printf("Something is wrong: your number is negative!\n");
        return;
    }

    int i = 1;
    do
    {
        printf("%d", i);
        if (i != n)
        {
            printf(" ");
        }
    } while (++i <= n);
}

void print_sequence_for(int n)
{
    if (n < 0)
    {
        printf("Something is wrong: your number is negative!\n");
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%d", i);
        if (i != n)
        {
            printf(" ");
        }
    }
}

void labels()
{
    printf("entering labels.\n");
    int i = 0;

simple_label:
    printf("This is a simple label\n");
    i++;
    if (i < 3)
    {
        goto simple_label;
    }
}

void wc_labels()
{
    int c;
    int n = 0;

space:
    c = getchar();
    if (c == EOF)
    {
        goto end;
    }
    if (isspace(c))
    {
        goto space;
    }

    ++n;
word:
    c = getchar();
    if (c == EOF)
    {
        goto end;
    }
    if (isspace(c))
    {
        goto space;
    }
    goto word;

end:
    printf("%d\n", n);
}

void anima()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case ' ':
            putchar('\n');
            break;
        case '\n':
            putchar('\n');
            putchar('\n');
            break;
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            putchar(c);
            putchar('s');
        default:
            putchar(c);
        }
    }
}

void anima_reverse()
{
    int c;
    while ((c = getchar()) != EOF)
    {
    point_switch:
        switch (c)
        {
        case '\n':
            // supposing always 1 space between words
            if ((c = getchar()) == '\n')
            {
                putchar('\n');
            }
            else
            {
                putchar(' ');
                goto point_switch;
            }
            break;
        case 's':
            int next = getchar();
            if (next == 'a' || next == 'e' || next == 'i' || next == 'o' || next == 'u')
            {
                putchar(next);
            }
            else
            {
                putchar(c);
                c = next;
                goto point_switch;
            }
        default:
            putchar(c);
        }
    }
}