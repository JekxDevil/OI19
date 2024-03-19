int not_less_than(const char *s1, const char *s2)
{
    // while strings are equal and not at the end, keep shifting chars
    while (*s1 == *s2 && *s2 != 0)
    {
        ++s1;
        ++s2;
    }
    // state if previus char violates the order (to keep swapping in main loop)
    return *s1 > *s2;
}

void insertion_sort(const char *S[], unsigned int n)
{
    for (unsigned int i = 1; i < n; ++i)
        // keep swapping if not in order
        for (unsigned int j = i; j > 0 && not_less_than(S[j - 1], S[j]); --j)
        {
            // swap
            const char *tmp = S[j];
            S[j] = S[j - 1];
            S[j - 1] = tmp;
        }
}

void sort_strings(const char *input, char *output, unsigned int n)
{
    const char *sequence[1000]; // 1 thousand strings
    const char *reader = input; // buffer reader
    for (unsigned int i = 0; i < n; i++)
    {
        sequence[i] = reader;
        while (*reader)
            reader++;
        reader++;
    }

    insertion_sort(sequence, n);

    char *writer = output; // buffer writer
    for (unsigned int i = 0; i < n; i++)
    {
        reader = sequence[i];
        do
        {
            *writer = *reader;
            writer++;
            reader++;
        } while (*(writer - 1));
    }
}